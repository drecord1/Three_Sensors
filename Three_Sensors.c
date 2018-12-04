#include <stdint.h>
#include "msp.h"
#include "../inc/Clock.h"
#include "../inc/CortexM.h"
#include "../inc/LaunchPad.h"
#include "../inc/Motor.h"
#include "../inc/TimerA1.h"

//Conected to P6.4
uint8_t trigBitMid = 0x10;

//Connected to P6.5
uint8_t echoBitMid = 0x20;

//Trigger pinL connected to P6.0
uint8_t trigBitLeft = 0x01;

//Echo pinL connected to P3.2
uint8_t echoBitLeft = 0x04;

//Trigger pinR connected to P4.1
uint8_t trigBitRight = 0x02;

//Echo pin R connected to P3.3
uint8_t echoBitRight = 0x08;

int distanceMid;
int distanceLeft;
int distanceRight;

int objectDetectedMid = 0;
int objectDetectedLeft = 0;
int objectDetectedRight = 0;


void Distance_Init(void){
    //Trigger as GPIO, P6.4
    P6->SEL0 &= ~trigBitMid;
    P6->SEL1 &= ~trigBitMid;
    //Trigger as Output
    P6->DIR |= trigBitMid;

    //Echo as GPIO P6.5
    P6->SEL0 &= ~echoBitMid;
    P6->SEL1 &= ~echoBitMid;
    //Echo as input
    P6->DIR &= ~echoBitMid;

    //TriggerL as GPIO P6.0
    P6->SEL0 &= ~trigBitLeft;
    P6->SEL1 &= ~trigBitLeft;
    //Trigger as Output
    P6->DIR |= trigBitLeft;

    //EchoBitL as GPIO P3.2
    P3->SEL0 &= ~echoBitLeft;
    P3->SEL1 &= ~echoBitLeft;
    //Echo as input
    P3->DIR &= ~echoBitLeft;

    //TriggerR as GPIO P4.1
    P4->SEL0 &= ~trigBitRight;
    P4->SEL1 &= ~trigBitRight;
    //Trigger as Output
    P4->DIR |= trigBitRight;

    //EchoBitR as GPIO P3.3
    P3->SEL0 &= ~echoBitRight;
    P3->SEL1 &= ~echoBitRight;
    //Echo as input
    P3->DIR &= ~echoBitRight;
}

void SetDistanceMid(int timeOut){
    //timeOut is a value in microseconds
    //it is used to exit the while loop if the signal is not found within the time limit

    int time;
    uint8_t echoValue;

    //Trigger off
    P6->OUT &= ~trigBitMid;
    Clock_Delay1us(2);

    //Trigger on
    P6->OUT |= trigBitMid;
    Clock_Delay1us(10);

    //Trigger off
    P6->OUT &= ~trigBitMid;

    time = 0;
    //Store the value of the echo sensor ANDing the pin vector with the bit that the echo sensor is connected to
    echoValue = (P6->IN & echoBitMid);

    //wait for triggers signal to be received by the echo sensor
    while( echoValue == 0x00 && time < timeOut){
        //Delay for one microsecond so we can keep track of how much time it took to receive signal
        Clock_Delay1us(1);
        time++;
        echoValue = (P6->IN & echoBitMid);
    }

    time = 0;
    echoValue = (P6->IN & echoBitMid);

    //wait for echo signal to return to LOW
    while( echoValue != 0x00 && time < timeOut  ){
        //Delay for 1 microsecond and increment time variable so the time variable will store how much time it took for the echo signal to return to 0
        Clock_Delay1us(1);
        time++;
        echoValue = (P6->IN & echoBitMid);
    }

    //Rate of sound in air is approximately 0.0343 centimeters per microsecond
    //Distance = Rate * time
    distanceMid = (0.0343 * time);
}

void SetDistanceLeft(int timeOut){
    //timeOut is a value in microseconds
    //it is used to exit the while loop if the signal is not found

    //Trigger Left connect to P6.0
    //Echo Left connect to P3.2

    int time;
    uint8_t echoValue;

    //Trigger off
    P6->OUT &= ~trigBitLeft;
    Clock_Delay1us(2);

    //Trigger on
    P6->OUT |= trigBitLeft;
    Clock_Delay1us(10);

    //Trigger off
    P6->OUT &= ~trigBitLeft;

    time = 0;
    //Store the value of the echo sensor ANDing the pin vector with the bit that the echo sensor is connected to
    echoValue = (P3->IN & echoBitLeft);

    //wait for triggers signal to be received by the echo sensor
    while( echoValue == 0x00 && time < timeOut){
        //Delay for one microsecond so we can keep track of how much time it took to receive signal
        Clock_Delay1us(1);
        time++;
        echoValue = (P3->IN & echoBitLeft);
    }

    time = 0;
    echoValue = (P3->IN & echoBitLeft);

    //wait for echo signal to return to LOW
    while( echoValue != 0x00 && time < timeOut  ){
        //Delay for 1 microsecond and increment time variable so the time variable will store how much time it took for the echo signal to return to 0
        Clock_Delay1us(1);
        time++;
        echoValue = (P3->IN & echoBitLeft);
    }

    //Rate of sound in air is approximately 0.0343 centimeters per microsecond
    //Distance = Rate * time
    distanceLeft = (0.0343 * time);
}


void SetDistanceRight(int timeOut){
    //timeOut is a value in microseconds
    //it is used to exit the while loop if the signal is not found

    //Trigger Right P4.1
    //Echo Right P3.3

    int time;
    uint8_t echoValue;

    //Trigger off
    P4->OUT &= ~trigBitRight;
    Clock_Delay1us(2);

    //Trigger on
    P4->OUT |= trigBitRight;
    Clock_Delay1us(10);

    //Trigger off
    P4->OUT &= ~trigBitRight;

    time = 0;
    //Store the value of the echo sensor ANDing the pin vector with the bit that the eacho sensor is connected to
    echoValue = (P3->IN & echoBitRight);

    //wait for triggers signal to be received by the echo sensor
    while( echoValue == 0x00 && time < timeOut){
        //Delay for one microsecond so we can keep track of how much time it took to receive signal
        Clock_Delay1us(1);
        time++;
        echoValue = (P3->IN & echoBitRight);
    }

    time = 0;
    echoValue = (P3->IN & echoBitRight);

    //wait for echo signal to return to LOW
    while( echoValue != 0x00 && time < timeOut  ){
        //Delay for 1 microsecond and increment time variable so the time variable will store how much time it took for the echo signal to return to 0
        Clock_Delay1us(1);
        time++;
        echoValue = (P3->IN & echoBitRight);
    }

    //Rate of sound in air is approximately 0.0343 centimeters per microsecond
    //Distance = Rate * time
    distanceRight = (0.0343 * time);
}


void CheckDistance(void){

    //Look for distance for a max of 1 second
    SetDistanceMid(1000);
    SetDistanceLeft(1000);
    SetDistanceRight(1000);

    uint8_t LED = 0x00;

    if(distanceMid < 15){
        //You can change the value in the if statement to whatever you would like

        //If an object is closer than 10cm in the middle...
        //make the LED light RED
        LED = RED;

        //objectDetectedMid is a global variable, and is referenced in the AvoidObject function
        objectDetectedMid = 1;

    }else{
        //set LED to green if no object is in front
        LED = GREEN;

        objectDetectedMid = 0;
    }

    if(distanceLeft < 10){
        //If an object is closer than 6cm on the left...
        //make the LED light yellow
        LED = 0x03;
        objectDetectedLeft = 1;

    }else{

        objectDetectedLeft = 0;
    }

    if(distanceRight < 10){
        //If an object is closer than 6cm on the right...
        //make the LED light blue
        LED = 0x04;
        objectDetectedRight = 1;

    }else{

        objectDetectedRight = 0;
    }

    //set LED's color
    LaunchPad_Output(LED);
}

void AvoidObjectMid(void){

    //Turn on RED led on Robot
    LaunchPad_LED(0x01);
	
    Motor_Stop();
    Clock_Delay1ms(250);

    if(distanceLeft < distanceRight){
        //If an object is closer on the left side, then robot turns right
        Motor_Right(4000,4000);
    }else{
        //If object is closer on the right side, then robot turns left
        Motor_Left(4000,4000);
    }


    while(objectDetectedMid == 1){
        //The robot will turn right until an object is no longer detected
    }

    //Stop motor when an object is no longer in front of the distance sensor
    Motor_Stop();

    //Turn off RED led
    LaunchPad_LED(0x00);

    //Wait for a short period of time before the function completes
    //This is not needed, however, I used it so the robot came to a short stop before continuing forward
    Clock_Delay1ms(500);
}


void AvoidObjectLeft(void){

    //Turn on RED led on Robot
    LaunchPad_LED(0x01);

    Motor_Stop();
    Clock_Delay1ms(250);

    //Robot turns right when an object is detected on left
    Motor_Right(4000,4000);

    while(objectDetectedLeft == 1){
        //The robot will turn right until an object is no longer detected
    }

    //Stop motor when an object is no longer in front of the distance sensor
    Motor_Stop();

    //Turn off RED led
    LaunchPad_LED(0x00);

    //Wait for a short period of time before the function completes
    //This is not needed, however, I used it so the robot came to a short stop before continuing forward
    Clock_Delay1ms(500);
}

void AvoidObjectRight(void){

    //Turn on RED led on Robot
    LaunchPad_LED(0x01);
	
    Motor_Stop();
    Clock_Delay1ms(250);

    //Robot turns left when an object is detected on right
    Motor_Left(4000,4000);

    while(objectDetectedRight == 1){
        //The robot will turn left until an object is no longer detected
    }

    //Stop motor when an object is no longer in front of the distance sensor
    Motor_Stop();

    //Turn off RED led
    LaunchPad_LED(0x00);

    //Wait for a short period of time before the function completes
    //This is not needed, however, I used it so the robot came to a short stop before continuing forward
    Clock_Delay1ms(500);
}

int main(void){

    Clock_Init48MHz();
    LaunchPad_Init();
    Motor_Init();
    Distance_Init();
    TimerA1_Init(&CheckDistance,50000);
    Clock_Delay1ms(1000);
    EnableInterrupts();

    while(1)
    {
        //objectDetected variable is changed in the CheckDistance function
        if(objectDetectedMid == 1){
            AvoidObjectMid();
            Clock_Delay1ms(250);
        }
        else if(objectDetectedLeft == 1){
            AvoidObjectLeft();
            Clock_Delay1ms(250);
        }
        else if(objectDetectedRight == 1){
            AvoidObjectRight();
            Clock_Delay1ms(250);
        }else{
            Motor_Forward(5000,5000);
        }
    }
}

