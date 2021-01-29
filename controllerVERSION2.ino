//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 myRadio(8, 9); // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

//byte addresses[][6] = {"0"};

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

// Define Joystick Values - Start at 512 (middle position)
int joyposX = 512;
int joyposY = 512;

void setup()
{

  Serial.begin(9600);
  delay(100);
  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MIN);
  myRadio.setDataRate( RF24_250KBPS );

 //myRadio.openWritingPipe( addresses[0]);
 //set the address
  myRadio.openWritingPipe(address);

//Set module as transmitter
  myRadio.stopListening();


  delay(100);



}

void loop()
{

  myRadio.write(&data, sizeof(data));


  // Read the Joystick X and Y positions
  data.joyposX = analogRead(joyX);
  data.joyposY = analogRead(joyY);

 
  delay(100);  // Wait a bit before next transmission
}
