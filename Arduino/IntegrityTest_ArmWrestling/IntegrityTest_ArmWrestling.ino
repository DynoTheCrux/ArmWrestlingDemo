//*****CHECKS ALL ENCODERS AND SWITCHES*****//

// SWI: 23.05.2023 -> All work

// *****LIBRARIES*****
#include "Encoder.h"
#include "DC_Motor.h"

// *****VARIABLES & DEFINITIONS*****
// Force sensor
double sensor1 = A12;                   // Select the input pin for the potentiometer 1
double sensor2 = A15;                   // Select the input pin for the potentiometer 2
double Value1 = 0;                      // Variable to store the value coming from the force sensor 1
double Value2 = 0;                      // Variable to store the value coming from the force sensor 2
double total = 0;                       // Variable to store sum of force sensors
double Forcevalue = 0;                  // Variable to store the force value of force sensors
int diff = 0;                           // Variable to store the reduction of speed of wrist motor when pressing force sensor
int vel = 0;                            // Variable to store the residual speed of wrist motor when pressing force sensor

// Linear equation system for force sensor f(x)= k*x+d  
double k= 4.905/(222-205);              // sensorvalue = 222 (measured with 500 g)
double d= 4.905/(222-205)*222-4.91;     // sensorvalue = 205 (measured with 0 g)

// Initialization
uint8_t xSwitchVal = -1;                                       
uint8_t ySwitchVal = -1;
uint8_t wrist_SwitchVal = -1;   

// Encoders
int32_t encoderPos_wrist = 0;                                    
int32_t encoderPosX = 0;      
int32_t encoderPosY = 0; 

// Encoder pin definition (channel_1, channel_2)
Encoder encoder_wrist(3, 2);          // Wrist
Encoder encoderY(18, 19);             // Y axis
Encoder encoderX(20, 21);             // X axis

// Limit switch definition
#define switchX 32
#define switchY 24
#define switch_wrist 30

// *****FUNCTIONS*****

void debugSwitches()
{
    xSwitchVal = digitalRead(switchX);                            // Read limit switch status and store it into variables
    ySwitchVal = digitalRead(switchY);
    wrist_SwitchVal = digitalRead(switch_wrist);
    
    //Serial.print ("Switchvals: ");
    Serial.print (xSwitchVal);
    Serial.print (' ');
    Serial.print (ySwitchVal);
    Serial.print (' ');
    Serial.print (wrist_SwitchVal);
    Serial.print (' ');
    //Serial.println ();
}


void encoderRead(){                                               // Read encoder positions and store them into variables
  encoderPos_wrist = encoder_wrist.read();
  encoderPosX = encoderX.read();
  encoderPosY = encoderY.read();
  }

void printEncoderPos(){                                           // Serial printing of encoder positions for the communication with Unity 3D
  //Serial.print ("Encodervals:");
  Serial.print (encoderPosX);
  Serial.print (' ');
  Serial.print (encoderPosY);
  Serial.print (' ');
  Serial.print (encoderPos_wrist);
  Serial.println ();
  }



void setup() {
  pinMode(switchX, INPUT_PULLUP);                                 // Define limit switches as input
  pinMode(switchY, INPUT_PULLUP);                                       
  pinMode(switch_wrist, INPUT_PULLUP);

  Serial.begin(9600);  

}

void loop() {
  // put your main code here, to run repeatedly:
  encoderRead();                                                  // Read encoder position
  debugSwitches();
  printEncoderPos();

}
