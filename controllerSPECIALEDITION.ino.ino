// Library: TMRh20/RF24, https://github.com/tmrh20/RF24/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 myRadio(8, 9); // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";





struct package
{
  int joyposX;
  int joyposY;
  int potValue;
  int modeNow;
};

typedef struct package Package;
Package data;

// Define Joystick Connections
#define joyX A0
#define joyY A1
#define readPot A2
#define buttonPin 7

// Define Joystick Values - Start at 512 (middle position)
int joyposX = 512;
int joyposY = 512;
int buttonState      = 0;     // current state of the button
int lastButtonState  = 0;     // previous state of the button
int modeNow;

void setup() {
  Serial.begin(9600);
  myRadio.begin();

  //set the address
  myRadio.openWritingPipe(address);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS );
  myRadio.setChannel(115);

  //Set module as transmitter
  myRadio.stopListening();

  delay(10);

  pinMode(buttonPin, INPUT_PULLUP);  // initialize the button pin as a input
}
void loop() {
  myRadio.write(&data, sizeof(data));

  data.joyposX = analogRead(joyX);
  data.joyposY = analogRead(joyY);
  data.potValue = analogRead(readPot);
  buttonState = digitalRead(buttonPin);
  //Serial.print("xAxis :");
  //Serial.println(data.joyposX);
  //Serial.print("yAxis :");
  //Serial.println(data.joyposY);
 // Serial.print("PotValue :");
 // Serial.println(data.potValue);
  delay(10);

// check if the button is pressed or released
  // by comparing the buttonState to its previous state
  if (buttonState != lastButtonState) {

    // change the state of the led when someone pressed the button
    if (buttonState == 1) {
      data.modeNow++;
      if (data.modeNow > 3) data.modeNow = 1;


    }

    // remember the current state of the button
    lastButtonState = buttonState;
  }


  Serial.println(data.modeNow);
  // adding a small delay prevents reading the buttonState to fast
  // ( debouncing )
  delay(20);


}
