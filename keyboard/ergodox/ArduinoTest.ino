/* LED Blink, Teensyduino Tutorial #1
   http://www.pjrc.com/teensy/tutorial.html
 
   This example code is in the public domain.
*/

// Teensy 2.0 has the LED on pin 11
// Teensy++ 2.0 has the LED on pin 6
// Teensy 3.0 has the LED on pin 13
//const int RedLedPin = 10;
//const int GreenLedPin = 11;
//const int BlueLedPin = 12;

// the setup() method runs once, when the sketch starts

void setup() {
  // initialize the digital pin as an output.
  //pinMode(RedLedPin, OUTPUT);
  //pinMode(GreenLedPin, OUTPUT);
  //pinMode(BlueLedPin, OUTPUT);
  //digitalWrite(RedLedPin, LOW);   // set the LED on
  //digitalWrite(GreenLedPin, LOW);   // set the LED on
  //digitalWrite(BlueLedPin, LOW);   // set the LED on
  //Serial.begin(9600);      // open the serial port at 9600 bps:
  
    for (int thisPin = 1; thisPin < 22; thisPin++)  {
      pinMode(thisPin, OUTPUT);
      digitalWrite(thisPin, LOW);
    }
    //digitalWrite( 12, HIGH);
}

// the loop() methor runs over and over again,
// as long as the board has power

int thisPin;
void loop() {

  delay(100);
//    for (thisPin = 1; thisPin < 22; thisPin++)  {
//      pinMode(thisPin, OUTPUT);
//      digitalWrite(thisPin, HIGH);
//      Serial.print("Turning on: ");
//      Serial.println(thisPin); 
//      delay(1000);                  // wait for a second
//      digitalWrite(thisPin, LOW);
//    }
//    
//    for (thisPin = 1; thisPin < 22; thisPin++)  {
//      pinMode(thisPin, OUTPUT);
//      digitalWrite(thisPin, LOW);
//    }
}

