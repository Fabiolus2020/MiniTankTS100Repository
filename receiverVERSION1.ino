//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 myRadio(8, 9); // CE, CSN

struct package
{
  int joyposX;
  int joyposY;
  int potValue;
  int modeNow;


};


typedef struct package Package;
Package data;

//address through which two modules communicate.
const byte address[6] = "00001";

//byte addresses[][6] = {"0"};

// Motor A Connections
int enA = 10;
int in1 = 4;
int in2 = 5;

// Motor B Connections
int enB = 3;
int in3 = 6;
int in4 = 7;



// Set initial motor direction as forward
int motordirection = 0;
int motorspeed1 = 0;
int motorspeed2 = 0;

void setup()
{
  while (!Serial);
  Serial.begin(9600);
  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ;
  //myRadio.openReadingPipe(1, addresses[0]);

  //set the address
  myRadio.openReadingPipe(0, address);
  myRadio.startListening();
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}

void loop()
{
  if ( myRadio.available())
  {
    //while (myRadio.available())
    //{
    myRadio.read( &data, sizeof(data) );
    //}

    //Serial Print the values
    // Serial.print(": motorspeed1 :");
    //  Serial.println(data.motorspeed1);
    //  Serial.print(" motorspeed2 :");
    //  Serial.println(data.motorspeed2);
    //  Serial.print(" direction");
    // Serial.println(data.motordirection);
    //delay (2000);
    // Set Motor Direction


    if (data.joyposX < 470)
    {
      // This is forward
      motordirection = 1;
      //Determine Motor Speeds

      motorspeed1 = map(data.joyposX, 470, 0, 0, 255);
      motorspeed2 = map(data.joyposX, 470, 0, 0, 255);

    }
    else  if (data.joyposX > 600)
    {
      // This is backward
      motordirection = 2;

      //Determine Motor Speeds
      motorspeed1 = map(data.joyposX, 600, 1023, 0, 255);
      motorspeed2 = map(data.joyposX, 600, 1023, 0, 255);

    }
    else if (data.joyposY < 470) {
      // This is left
      motordirection = 3;

      //Determine Motor Speeds
      motorspeed1 = map(data.potValue, 470, 0, 0, 255);
      motorspeed2 = map(data.potValue, 470, 0, 0, 255);
    }
    else if (data.joyposY > 600) {
            // This is right
      motordirection = 3;
      
      motorspeed1 = map(data.potValue, 1023, 0, 0, 255);
      motorspeed2 = map(data.potValue, 1023, 0, 0, 255);
      
    }
    else
    {
      // This is Stopped
      motordirection = 0;
      motorspeed1 = 0;
      motorspeed2 = 0;


    }


    if (motordirection == 1)
    {
      // Motors are forward
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
    }
    else  if (motordirection == 2)
    {
      // Motors are bacward
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
    }

    else  if (motordirection == 3)
    {
      // Motors are bacward
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
    }
    else  if (motordirection == 4)
    {
      // Motors are bacward
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
    }
    // Drive Motors
    analogWrite(enA, motorspeed1);
    analogWrite(enB, motorspeed2);

  }
  delay(30);
  Serial.println(data.joyposX);
}
