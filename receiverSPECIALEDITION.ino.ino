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

#define enA 10   // Note: Pin 9 in previous video ( pin 10 is used for the SPI communication of the NRF24L01)
#define in1 4
#define in2 5
#define enB 3   // Note:  Pin 10 in previous video
#define in3 6
#define in4 7


// Set initial motor direction as forward and speed at 0
int motorSpeedA = 0;
int motorSpeedB = 0;
int motordirection = 0;
int motorspeed1 = 0;
int motorspeed2 = 0;


void modeOne()
{
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
      motordirection = 4;
      
      motorspeed1 = map(data.potValue, 600, 0, 0, 255);
      motorspeed2 = map(data.potValue, 600, 0, 0, 255);
      
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
 delay(30);
  }
 
 



void modeTwo()
{
      // X-axis used for forward and backward control
    if (data.joyposX < 470) {
      // Set Motor A backward
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      // Set Motor B backward
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
      motorSpeedA = map(data.joyposX, 470, 0, 0, 255);
      motorSpeedB = map(data.joyposX, 470, 0, 0, 255);
    }
    else if (data.joyposX > 550) {
      // Set Motor A forward
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      // Set Motor B forward
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
      motorSpeedA = map(data.joyposX, 550, 1023, 0, 255);
      motorSpeedB = map(data.joyposX, 550, 1023, 0, 255);
    }
    // If joystick stays in middle the motors are not moving
    else {
      motorSpeedA = 0;
      motorSpeedB = 0;
    }


    // Y-axis used for left and right control
    //this is left
    if (data.joyposY < 470) {

      // Set Motor A forward
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      // Set Motor B backward
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);

      // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
      motorSpeedA = map(data.joyposY, 470, 0, 0, 255);
      motorSpeedB = map(data.joyposY, 470, 0, 0, 255);
    }


    if (data.joyposY > 550) {

      // Set Motor A forward
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      // Set Motor B backward
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);

      // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
      motorSpeedA = map(data.joyposY, 550, 1023, 0, 255);
      motorSpeedB = map(data.joyposY, 550, 1023, 0, 255);
    }
    // Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
    if (motorSpeedA < 70) {
      motorSpeedA = 0;
    }
    if (motorSpeedB < 70) {
      motorSpeedB = 0;
    }
    analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
    analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
  }


void modeThree()
{
  // X-axis used for forward and backward control
  if (data.joyposX > 600) {
    // Set Motor A backward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // Set Motor B backward
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(data.potValue, 1023, 0, 0, 255);
    motorSpeedB = map(data.potValue, 1023, 0, 0, 255);
  }
  else if (data.joyposX < 400) {
    // Set Motor A forward
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    // Set Motor B forward
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(data.potValue, 1023, 0, 0, 255);
    motorSpeedB = map(data.potValue, 1023, 0, 0, 255);
  }
  // If joystick stays in middle the motors are not moving
  else {
    motorSpeedA = 0;
    motorSpeedB = 0;
  }


  // Y-axis used for left and right control
  //this is left
  if (data.joyposY < 400) {

    // Set Motor A forward
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    // Set Motor B backward
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(data.potValue, 1023, 0, 0, 255);
    motorSpeedB = map(data.potValue, 1023, 0, 0, 255);
  }


  if (data.joyposY > 600) {

    // Set Motor A forward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // Set Motor B backward
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(data.potValue, 1023, 0, 0, 255);
    motorSpeedB = map(data.potValue, 1023, 0, 0, 255);
  }
  // Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
  if (motorSpeedA < 70) {
    motorSpeedA = 0;
  }
  if (motorSpeedB < 70) {
    motorSpeedB = 0;
  }
  analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
  analogWrite(enB, motorSpeedB); // Send PWM signal to motor B

}





void setup() {

  while (!Serial);

  Serial.begin(9600);
  myRadio.begin();
  //set the address
  myRadio.openReadingPipe(0, address);
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS );
  //Set module as receiver
  myRadio.startListening();
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  // Set Motor to low initially
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(enA, LOW);
  digitalWrite(enB, LOW);
}


void loop() {
  if ( myRadio.available())
  {

    myRadio.read( &data, sizeof(data) );

    // Serial.print("X : ");
    // Serial.println(data.joyposX);
    //Serial.print("Y : ");
    // Serial.println(data.joyposY);
    // Serial.print("potValue : ");
    //Serial.println(data.potValue);
    delay(10);

  
  if(data.modeNow == 1)
  {
    modeOne();
  }
  if(data.modeNow == 2)
  {
    modeTwo();
  }
  if(data.modeNow == 3)
  {
    modeThree();
  }

  }
}
