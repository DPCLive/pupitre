
/////////////////////////////////////////////////////////////////////////////////////
// DESREUMAUX Vincent - DPCLive
// 03/03/2020
// Version 1.0
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// D0-D7 Port A (0-7)
// A1-A8 Port C (0-7)
// A9-A11 Port L (0-2)
// CLK PWM 11
// WR Port G (0)
// RD Port G (1)
// Reset Port B (0)
/////////////////////////////////////////////////////////////////////////////////////


int blinkPin = 11;
int wr_pin = 41;
int rd_pin = 40;
int reset_pin = 53;

int test_input_pin = 7;

void TimerOne_setPeriod(long OCRValue)
{
 TCCR1B = (1 << WGM12) | (1 << CS10); 

 TCCR1A = bit(COM1A0);                      //  or use TCCR1A = 0x40;            // Toggle mode 0C1A  
 OCR1A = OCRValue;                          // set the counter
}

void Select_TMP(uint8_t a0)
{
    PORTL = 0x00; // A9..A11

/*
 * Sélection du TMP IC80
 * 
  A7..A11  : 0
  A6: 1
  A5: 0
  A4: 1 (C)74 HC138 numéro IC6
  A3: 1 (B)74 HC138 numéro IC6
  A2: 1 (A)74 HC138 numéro IC6
  A1: a0 du TMP (sélection du registre)
  A0: non connecté (on le met toujours à zéro)
  */  
    if (a0)
    {
      //  A7  ... A0
      PORTC = B01011110;
    }
    else
    {
      //  A7  ... A0
      PORTC = B01011100;
    }
}


void TM_SelectStatusWord()
{
  digitalWrite(rd_pin, LOW);  // 0
  digitalWrite(wr_pin, HIGH); // 1
  
  delayMicroseconds(1000);
  
  Select_TMP(1);
  
  delayMicroseconds(1000);
}

void TMP_WriteCommand()
{
  digitalWrite(rd_pin, HIGH);
  digitalWrite(wr_pin, LOW);
  
  delayMicroseconds(1000);
  
  Select_TMP(1);
  
  delayMicroseconds(1000);
}

void setup() {
  // put your setup code here, to run once:


  DDRC = B11111111;  // 1 == outputs, 0 == input
  DDRL = B11111111;  // 1 == outputs, 0 == input

  DDRA = 0;  // 1 == outputs, 0 == input

   pinMode(wr_pin, OUTPUT); 
   pinMode(rd_pin, OUTPUT); 
   pinMode(reset_pin, OUTPUT);

   pinMode(test_input_pin, INPUT);

   digitalWrite(reset_pin, HIGH);

  // PARAMETRAGE HORLOGE 
   pinMode(blinkPin, OUTPUT);                 // alternately use DDRB = 0xa0;      // turn on the timer ouput pin;
  TimerOne_setPeriod(6);                 // set up and start Timer1 to blink at the same rate as the blink sketch

    // open the serial port at 9600 bps:
  Serial.begin(9600);

  
}

void loop() {
  // put your main code here, to run repeatedly:

  //digitalWrite(reset_pin, LOW);
  delay(20);
  digitalWrite(reset_pin, HIGH);
  delay(20);

  TMP_SelectStatusWord();

  Serial.println(PINA, BIN);  // print as an ASCII-encoded binary

  /*if (digitalRead(test_input_pin) == HIGH)
  {
    Serial.println("5V ------------");
  }
  else
  {
    Serial.println("0V **********");
  }*/
  
  delay(200);
  
}
