
int blinkPin = 11;

void TimerOne_setPeriod(long OCRValue)
{
 TCCR1B = (1 << WGM12) | (1 << CS10); 

 TCCR1A = bit(COM1A0);                      //  or use TCCR1A = 0x40;            // Toggle mode 0C1A  
 OCR1A = OCRValue;                          // set the counter
}

void setup() {
  // put your setup code here, to run once:

 // Test en sortie

 // DDRA = B11111111;  // 1 == outputs, 0 == input
//  PORTA = 0xAA;


  DDRA = 0x00;

   pinMode(blinkPin, OUTPUT);                 // alternately use DDRB = 0xa0;      // turn on the timer ouput pin;
  TimerOne_setPeriod(6);                 // set up and start Timer1 to blink at the same rate as the blink sketch

   // setup_clk_out();
  
    // open the serial port at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:


    Serial.println(PINA, BIN);  // print as an ASCII-encoded binary
}
