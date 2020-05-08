#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>


byte arduinoMac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress arduinoIP(192, 168, 1, 178); // desired IP for Arduino
unsigned int arduinoPort = 8888;      // port of Arduino

IPAddress receiverIP(192, 168, 1, 22); // IP of udp packets receiver
unsigned int receiverPort = 8080;      // port to listen on my PC

EthernetUDP _Udp;

uint8_t _packetBuffer[96];
int touches[8][8];

#define MAX_NUMBER_OF_LINES 8
uint8_t ledPreview2ME[MAX_NUMBER_OF_LINES]; // N lignes, un bit par ligne
uint8_t ledColor[MAX_NUMBER_OF_LINES]; // couleurs

uint8_t ports[8] = {B00000000, B00000001, B00000010, B00000011, B00000100, B00000101, B00000110, B00000111};

void setup() {
  Ethernet.begin(arduinoMac, arduinoIP);
  _Udp.begin(arduinoPort);

  // 1 == outputs, 0 == input
  DDRF = B00000000;  // Code binaire des lignes TMP IC11
  DDRC = B00000111; // Code binaire des colonnes TMP IC11
  DDRA = B11111111;
  pinMode(41, OUTPUT);
  reset();
}

void lecture() {
  digitalWrite(41, LOW);
  for (int t = 0; t < 8; t++) {
    PORTC = ports[t];
    delayMicroseconds(50);
    for (int i = 0; i < 8; i++) {
      touches[t][i] = bitRead(PINF, i);
    }
  }
  if (PINF != 0) {
    for (int col = 0; col < 8; col++) {
      for (int ligne = 0; ligne < 8; ligne++)
      {
        if (touches[col][ligne] == 0) {
          envoiUDPServer(1, col, ligne);
        }
      }
    }
  } else {
    //Serial.println("no connect");
  }
}

void envoiUDPServer(int tmp, int col, int ligne) {
  _Udp.beginPacket(receiverIP, receiverPort); //start udp packet
  _Udp.print(tmp);
  _Udp.print(col);
  _Udp.print(ligne);
  _Udp.endPacket();
}

void loop() {
  lecture();
  delay(1);
  ecriture();
}

void ecriture(){

  int packetSize = _Udp.parsePacket();
  if (packetSize)
  {
    _Udp.read(_packetBuffer, UDP_TX_PACKET_MAX_SIZE);

    uint8_t cmd = _packetBuffer[0];

    if (cmd == 0)
    {
      // on change la config des lignes
      for (int i = 0; i < MAX_NUMBER_OF_LINES; i++)
      {
        ports[i] = _packetBuffer[1 + i];
      }
    }
    else
    {
      // sinon ce n'est pas une config mais un ordre d'allumage
      uint8_t line = _packetBuffer[0];
   
      for (int i = 0; i < MAX_NUMBER_OF_LINES; i++)
      {
        ledPreview2ME[i] = _packetBuffer[1 + (2 * i)];
        ledColor[i] = _packetBuffer[2 + (2 * i)];
      }
    }
  }
  /// fin UDP wait
  for (int i = 0; i < 8; i++)
  {
    PORTC = ports[i];
    leds(ledPreview2ME[i], ledColor[i]);
    delay(1);
  }  
}
void leds(uint8_t line, uint8_t color)
{

  uint8_t l;
  digitalWrite(41, LOW); //20
  for (int i = 0; i < 8; i++)
  {
    uint8_t c = bitRead(color, i);
    digitalWrite(21, c ? HIGH : LOW);
    bitWrite(l, i, bitRead(line,i));
  }
  PORTA = l;

  delayMicroseconds(80);
  //Vérouiller les leds
  digitalWrite(41, HIGH);//20
  delayMicroseconds(500);
}

void reset()
{
  for (int i = 0; i < MAX_NUMBER_OF_LINES; i++)
  {
    ledPreview2ME[i] = 0;
  }
}
