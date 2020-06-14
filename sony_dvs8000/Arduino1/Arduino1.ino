#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

byte arduinoMac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress arduinoIP(192, 168, 1, 165); // desired IP for Arduino
unsigned int arduinoPort = 8888;      // port of Arduino

IPAddress receiverIP(192, 168, 1, 160); // IP of udp packets receiver
unsigned int receiverPort = 8080;      // port to listen on my PC

EthernetUDP _Udp;

// TMP1
const int sel1A = 37;
const int sel1B = 36;
const int sel1C = 35;


// TMP2
const int sel2A = 33;
const int sel2B = 32;
const int sel2C = 31;

const int ver1 = 41;
const int ver2 = 40;

unsigned long previousMillis = 0 ;
unsigned long interval = 10L;

unsigned long previousMillis1 = 0 ;
unsigned long interval1 = 500L;

unsigned long previousMillis2 = 0 ;
unsigned long interval2 = 500L;

uint8_t _packetBuffer[96];

#define MAX_NUMBER_OF_LINES 8


byte led1[8];
byte led2[8];


void setup() {
  Ethernet.begin(arduinoMac, arduinoIP);
  _Udp.begin(arduinoPort);
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(sel1A, OUTPUT);
  pinMode(sel1B, OUTPUT);
  pinMode(sel1C, OUTPUT);
  pinMode(ver1, OUTPUT);


  pinMode(sel2A, OUTPUT);
  pinMode(sel2B, OUTPUT);
  pinMode(sel2C, OUTPUT);
  pinMode(ver2, OUTPUT);


  //////
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(29, OUTPUT);

  digitalWrite(22, LOW);
  digitalWrite(23, LOW);
  digitalWrite(24, LOW);
  digitalWrite(25, LOW);
  digitalWrite(26, LOW);
  digitalWrite(27, LOW);
  digitalWrite(28, LOW);
  digitalWrite(29, LOW);


  pinMode(49, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(47, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(43, OUTPUT);
  pinMode(42, OUTPUT);

  digitalWrite(49, LOW);
  digitalWrite(48, LOW);
  digitalWrite(47, LOW);
  digitalWrite(46, LOW);
  digitalWrite(45, LOW);
  digitalWrite(44, LOW);
  digitalWrite(43, LOW);
  digitalWrite(42, LOW);

  ///////////////
  digitalWrite(sel1A, LOW);
  digitalWrite(sel1B, LOW);
  digitalWrite(sel1C, LOW);
  digitalWrite(ver1, HIGH);


  digitalWrite(sel2A, LOW);
  digitalWrite(sel2B, LOW);
  digitalWrite(sel2C, LOW);
  digitalWrite(ver2, HIGH);


  ///////////////

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);


  pinMode(A8, INPUT);
  pinMode(A9, INPUT);
  pinMode(A10, INPUT);
  pinMode(A11, INPUT);
  pinMode(A12, INPUT);
  pinMode(A13, INPUT);
  pinMode(A14, INPUT);
  pinMode(A15, INPUT);


  // test();
}

void test() {
  led1[0] = 0xFF;

  led1[1] = 0xFF;

  led1[2] = 0xFF;

  led1[3] = 0xFF;;

  led1[4] = 0xFF;

  led1[5] = 0xFF;

  led1[6] = 0xFF;

  led1[7] = 0xFF;

}

void writeSignal(int i) {
  int j;
  if (i == 0) {
    digitalWrite(ver1, LOW);

    digitalWrite(sel1C, LOW);
    digitalWrite(sel1B, LOW);
    digitalWrite(sel1A, LOW);
    ////////////////////////

    for (j = 0; j < 8; j++) {
      digitalWrite(j + 22, led1[0] & (1 << j));
    }
    //////////////////////////

    digitalWrite(ver1, HIGH);

  } else if (i == 1) {
    digitalWrite(ver1, LOW);
    digitalWrite(sel1C, LOW);
    digitalWrite(sel1B, LOW);
    digitalWrite(sel1A, HIGH);

    ////////////////////////

    for (j = 0; j < 8; j++) {
      digitalWrite(j + 22, led1[1] & (1 << j));
    }
    //////////////////////////

    digitalWrite(ver1, HIGH);

  } else if (i == 2) {
    digitalWrite(ver1, LOW);
    digitalWrite(sel1C, LOW);
    digitalWrite(sel1B, HIGH);
    digitalWrite(sel1A, LOW);

    ////////////////////////

    for (j = 0; j < 8; j++) {
      digitalWrite(j + 22, led1[2] & (1 << j));
    }
    //////////////////////////

    digitalWrite(ver1, HIGH);

  } else if (i == 3) {
    digitalWrite(ver1, LOW);
    digitalWrite(sel1C, LOW);
    digitalWrite(sel1B, HIGH);
    digitalWrite(sel1A, HIGH);

    ////////////////////////

    for (j = 0; j < 8; j++) {
      digitalWrite(j + 22, led1[3] & (1 << j));
    }
    //////////////////////////

    digitalWrite(ver1, HIGH);

  } else if (i == 4) {
    digitalWrite(ver1, LOW);
    digitalWrite(sel1C, HIGH);
    digitalWrite(sel1B, LOW);
    digitalWrite(sel1A, LOW);

    ////////////////////////

    for (j = 0; j < 8; j++) {
      digitalWrite(j + 22, led1[4] & (1 << j));
    }
    //////////////////////////

    digitalWrite(ver1, HIGH);

  } else if (i == 5) {
    digitalWrite(ver1, LOW);
    digitalWrite(sel1C, HIGH);
    digitalWrite(sel1B, LOW);
    digitalWrite(sel1A, HIGH);

    //////////////////////////
    for (j = 0; j < 8; j++) {
      digitalWrite(j + 22, led1[5] & (1 << j));
    }
    //////////////////////////

    digitalWrite(ver1, HIGH);

  } else if (i == 6) {
    digitalWrite(ver1, LOW);
    digitalWrite(sel1C, HIGH);
    digitalWrite(sel1B, HIGH);
    digitalWrite(sel1A, LOW);


    for (j = 0; j < 8; j++) {
      digitalWrite(j + 22, led1[6] & (1 << j));
    }
    //////////////////////////

    digitalWrite(ver1, HIGH);

  } else if (i == 7) {
    digitalWrite(ver1, LOW);
    digitalWrite(sel1C, HIGH);
    digitalWrite(sel1B, HIGH);
    digitalWrite(sel1A, HIGH);

    ////////////////////////

    for (j = 0; j < 8; j++) {
      digitalWrite(j + 22, led1[7] & (1 << j));
    }
    //////////////////////////

    digitalWrite(ver1, HIGH);

  }
}



void writeSignal2(int i) {
  int j;
  if (i == 0) {
    digitalWrite(ver2, LOW);

    digitalWrite(sel2C, LOW);
    digitalWrite(sel2B, LOW);
    digitalWrite(sel2A, LOW);
    ////////////////////////

    for (j = 0; j < 8; j++) {
      digitalWrite(49 - j, led2[0] & (1 << j));
    }
    //////////////////////////

    digitalWrite(ver2, HIGH);

  } else if (i == 1) {
    digitalWrite(ver2, LOW);
    digitalWrite(sel2C, LOW);
    digitalWrite(sel2B, LOW);
    digitalWrite(sel2A, HIGH);

    ////////////////////////

    for (j = 0; j < 8; j++) {
      digitalWrite(49 - j, led2[1] & (1 << j));
    }
    //////////////////////////

    digitalWrite(ver2, HIGH);

  } else if (i == 2) {
    digitalWrite(ver2, LOW);
    digitalWrite(sel2C, LOW);
    digitalWrite(sel2B, HIGH);
    digitalWrite(sel2A, LOW);

    ////////////////////////

    for (j = 0; j < 8; j++) {
      digitalWrite(49 - j, led2[2] & (1 << j));
    }
    //////////////////////////

    digitalWrite(ver2, HIGH);

  } else if (i == 3) {
    digitalWrite(ver2, LOW);
    digitalWrite(sel2C, LOW);
    digitalWrite(sel2B, HIGH);
    digitalWrite(sel2A, HIGH);

    ////////////////////////

    for (j = 0; j < 8; j++) {
      digitalWrite(49 - j, led2[3] & (1 << j));
    }
    //////////////////////////

    digitalWrite(ver1, HIGH);

  } else if (i == 4) {
    digitalWrite(ver2, LOW);
    digitalWrite(sel2C, HIGH);
    digitalWrite(sel2B, LOW);
    digitalWrite(sel2A, LOW);

    ////////////////////////

    for (j = 0; j < 8; j++) {
      digitalWrite(49 - j, led2[4] & (1 << j));
    }
    //////////////////////////

    digitalWrite(ver2, HIGH);

  } else if (i == 5) {
    digitalWrite(ver2, LOW);
    digitalWrite(sel2C, HIGH);
    digitalWrite(sel2B, LOW);
    digitalWrite(sel2A, HIGH);

    //////////////////////////
    for (j = 0; j < 8; j++) {
      digitalWrite(49 - j, led2[5] & (1 << j));
    }
    //////////////////////////

    digitalWrite(ver2, HIGH);

  } else if (i == 6) {
    digitalWrite(ver2, LOW);
    digitalWrite(sel2C, HIGH);
    digitalWrite(sel2B, HIGH);
    digitalWrite(sel2A, LOW);


    for (j = 0; j < 8; j++) {
      digitalWrite(49 - j, led2[6] & (1 << j));
    }
    //////////////////////////

    digitalWrite(ver2, HIGH);

  } else if (i == 7) {
    digitalWrite(ver2, LOW);
    digitalWrite(sel2C, HIGH);
    digitalWrite(sel2B, HIGH);
    digitalWrite(sel2A, HIGH);

    ////////////////////////

    for (j = 0; j < 8; j++) {
      digitalWrite(49 - j, led2[7] & (1 << j));
    }
    //////////////////////////

    digitalWrite(ver2, HIGH);

  }
}

void readSignal(int col) {
  if (digitalRead(A0) == LOW) {
    /*Serial.print(col);
      Serial.println("0");*/
    envoiUDPServer(1, col, 0);
  } else if (digitalRead(A1) == LOW) {
    /*Serial.print(col);
      Serial.println("1");*/
    envoiUDPServer(1, col, 1);
  }
  else if (digitalRead(A2) == LOW) {
    /*Serial.print(col);
      Serial.println("2");*/
    envoiUDPServer(1, col, 2);
  }
  else if (digitalRead(A3) == LOW) {
    /*Serial.print(col);
      Serial.println("3");*/
    envoiUDPServer(1, col, 3);
  }
  else if (digitalRead(A4) == LOW) {
    /*Serial.print(col);
      Serial.println("4");*/
    envoiUDPServer(1, col, 4);
  }
  else if (digitalRead(A5) == LOW) {
    /* Serial.print(col);
      Serial.println("5");*/
    envoiUDPServer(1, col, 5);
  }
  else if (digitalRead(A6) == LOW) {
    /*Serial.print(col);
      Serial.print("6");*/
    envoiUDPServer(1, col, 6);
  }
  else if (digitalRead(A7) == LOW) {
    /* Serial.print(col);
      Serial.println("7");*/
    envoiUDPServer(1, col, 7);
  }

}

void readSignal2(int col) {
  if (digitalRead(A8) == LOW) {
    /*Serial.print(col);
      Serial.println("0");*/
    envoiUDPServer(2, col, 0);
  } else if (digitalRead(A9) == LOW) {
    /*Serial.print(col);
      Serial.println("1");*/
    envoiUDPServer(2, col, 1);
  }
  else if (digitalRead(A10) == LOW) {
    /*Serial.print(col);
      Serial.println("2");*/
    envoiUDPServer(2, col, 2);
  }
  else if (digitalRead(A11) == LOW) {
    /*Serial.print(col);
      Serial.println("3");*/
    envoiUDPServer(2, col, 3);
  }
  else if (digitalRead(A12) == LOW) {
    /*Serial.print(col);
      Serial.println("4");*/
    envoiUDPServer(2, col, 4);
  }
  else if (digitalRead(A13) == LOW) {
    /* Serial.print(col);
      Serial.println("5");*/
    envoiUDPServer(2, col, 5);
  }
  else if (digitalRead(A14) == LOW) {
    /*Serial.print(col);
      Serial.print("6");*/
    envoiUDPServer(2, col, 6);
  }
  else if (digitalRead(A15) == LOW) {
    /* Serial.print(col);
      Serial.println("7");*/
    envoiUDPServer(2, col, 7);
  }

}

void envoiUDPServer(int tmp, int col, int ligne) {
  _Udp.beginPacket(receiverIP, receiverPort); //start udp packet
  _Udp.print(tmp);
  _Udp.print(col);
  _Udp.print(ligne);
  _Udp.endPacket();
}

void recuperationLeds() {
  int packetSize = _Udp.parsePacket();
  if (packetSize)
  {
    _Udp.read(_packetBuffer, UDP_TX_PACKET_MAX_SIZE);

    uint8_t tmp = _packetBuffer[0];
    if (tmp == 1)
    {
      for (int i = 0; i < MAX_NUMBER_OF_LINES; i++)
      {
        led1[i] = _packetBuffer[1 + (2 * i)];
      }

    }
    else
    {
      for (int i = 0; i < MAX_NUMBER_OF_LINES; i++)
      {
        led2[i] = _packetBuffer[1 + (2 * i)];
      }
    }
  }
}

void loop() {


  if ( micros() - previousMillis >= interval) {
    previousMillis = millis();
    recuperationLeds();
  }


  if ( micros() - previousMillis1 >= interval1) {
    previousMillis1 = millis();

    writeSignal(0);
    readSignal(0);
    delay(1);
    writeSignal(1);
    readSignal(1);
    delay(1);
    writeSignal(2);
    readSignal(2);
    delay(1);
    writeSignal(3);
    readSignal(3);
    delay(1);
    writeSignal(4);
    readSignal(4);
    delay(1);
    writeSignal(5);
    readSignal(5);
    delay(1);
    writeSignal(6);
    readSignal(6);
    delay(1);
    writeSignal(7);
    readSignal(7);
    delay(1);
  }

  if ( millis() - previousMillis2 >= interval2) {
    previousMillis2 = millis();

    writeSignal2(0);
    readSignal2(0);
    delay(1);
    writeSignal2(1);
    readSignal2(1);
    delay(1);
    writeSignal2(2);
    readSignal2(2);
    delay(1);
    writeSignal2(3);
    readSignal2(3);
    delay(1);
    writeSignal2(4);
    readSignal2(4);
    delay(1);
    writeSignal2(5);
    readSignal2(5);
    delay(1);
    writeSignal2(6);
    readSignal2(6);
    delay(1);
    writeSignal2(7);
    readSignal2(7);
    delay(1);
  }

}
