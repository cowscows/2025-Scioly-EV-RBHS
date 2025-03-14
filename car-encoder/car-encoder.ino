#include <Encoder.h>  //make sure to download encoder library by some paul guy

const int forwardPin = 6;   //pin for going forward
const int backwardPin = 7;  //pin for going backward
const int buttonpin = 8;    //button pin for trigger
int buttonstate;            //button pressed or not?
Encoder myEnc(2, 3);        // Pin 2 for ENCA, Pin 3 for ENCB
long position = 0;          // Get the current position

// User-defined parameters
float target_distance = (200 / 15.708 * 440);
//(target distance in cm)/(circumference)*450 ticks per rotation
float brake_number = target_distance - 100;
void setup() {
  pinMode(forwardPin, OUTPUT);
  pinMode(backwardPin, OUTPUT);
  pinMode(buttonpin, INPUT_PULLUP);
  Serial.begin(9600);  //enc starts communicating with arduino
}

void loop() {
  int buttonstate = digitalRead(buttonpin);
  long position = myEnc.read();  // Read the current position from the encoder
  if (buttonstate == LOW) {      // LOW means the button is pressed
    digitalWrite(forwardPin, HIGH);
    while (myEnc.read() < target_distance) {
      // keeps checking for enc position
    }
    digitalWrite(forwardPin, LOW);
    digitalWrite(backwardPin, HIGH);
    while (myEnc.read() > brake_number) {
      //goes back a little for braking
    }
    digitalWrite(backwardPin, LOW);
  } else {
    digitalWrite(forwardPin, LOW);
    digitalWrite(backwardPin, LOW);
    myEnc.write(0);  // Resets the encoder position
  }
}
