# MiniTankT10 Smart Repository

Youtube:
https://youtu.be/L-Q4bE_ijFw

This repository is for the mini tank project

sketch 1,2,3,4 connections are all the same.

sketch version 1 is to control tank with PWM with joystick.
sketch version 2 is to control tank with PWM differently from version 1 using joystick
sketch version 3 is to control tank using joystick for direction and potentiometer for speed using PWM.
sketch version 4 is to control tank using joytick for direction and potentiometer 1 for left motor and potentimeter 2 for right motor speed. This compensate for not having motors with encoders.


This video is about the mini T10 Smart project update.

If you have seen the other videos I basically played around building small sketches based on some requirements I had written down for this project.

I visited the following items like.

- map function to understand how to calibrate a joystick and get full performance with dc motors.
- creating my own functions to run small programs based on conditions.
- buttons and how to keep values and use them for different cases.
- using the L298 N Dual H-Bridge Motor Driver and applying different ways to control dc motors using pulse with modulation.
- Arduino Nano.
- understanding a 2 axis joystick.
- potentiometer
- push button and LED.
- If statement
- digital write. 
- analog Read.
- Batteries and wiring.
- RNF24L01+


the requirements

1- tank chassis platform: I went for a first level entry chassis of good quality. A platform would be best, so I can expand or modify easily. 

I went on the net and found the Mini T10 Smart tank car chassis its quite solid, the tracks are made of plastic, but they seem ok so far.

The first idea for a second robot was to build a remote control tank, simple but with multiple functions. I built different sketches first then made them work wirelessly.

I kept 4 of the best versions I have built so far.

 - version 1 is simply using the joystick and pulse with modulation, the speed is adjusted with the joystick position, the further you push on the joystick the faster the motors rotate. For left and right one motor would rotate clockwise and the other counter clockwise.

- version 2 is also the same concept using pulse with modulation but the sketch is different and results seem to be better in my opinion.

Version 3 is a bit different this time I added a potentiometer that control the speed, the joystick is only to control the direction.

Version 4 I built to help with the calibration of both motors, since I dont have encoders on the motors the robot is unable to stay on a perfect direction. So I built a sketch that would include 2 potentiometers to calibrate the speed of the motors independently. The results are quite good. It makes some very cool turn when going let say forward and lowering to a stop one side of the track and then bring the speed back up for a perfect turn.

The fun part about robotic and especially Arduino is that you can practically do almost anything you want. In my situation I had 4 different sketches and had to open the controller and the tank each time to upload different sketches.

I decided to build a special edition, in this version I built the remote control that work for all 4 sketches. On the other side the tank as well contain all 4 sketches. I learned about buttons and building my own functions so I went and built a feature that would allow switching between 4 modes with the click of a button. 

The controller sketch is simply to capture and send values to the robot. On the controller I added a joystick, a switch, 2 potentiometers a led and a push button. The way it works is that each time I click on the button it captures values 1 to 4 each representing a sketch, the LED blinks the number of time representing the sketch number to help me know which sketch I am setting up. Knowing how to capture value from a push button and using a counter I can toggle easily between cases.

The robot receives the information from the controller and based on the mode sent from the controller will run a specific function representing each sketches 1 to 4. I have set a limit on the counter to not go over 4 and the counter reset to mode 1 by default.

The AT mega 328P does come with memory limitation, so I will probably keep thing as is for now but to be honest ive been thinking about adding lights to the robot, I think I night go with Individually Addressable LEDs strip which seem to be the easiest for me since I am running 12 volts on the robot.  I think that will be all for this robot once the lights are in place.


Well I guess this is it for now until I figure how I will install lights to the robot. Oh one least thing as you can see everything fits in a box which can be easily removed from the chassis I think it's a good idea, so I can leave everything in the box and remove it easily, the box could easily be applied to other platforms or project if needed...maybe a better tank chassis who knows?!?!?

