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
uint8_t hasBeenInit = false;            //       
uint8_t after_initialization = false;
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

// Motors
uint8_t motor_wrist_dir = 0;          // Wrist                         
uint8_t motor_wrist_pwm = 0;          
uint8_t motorY_dir = 0;               // Y axis
uint8_t motorY_pwm = 0;
uint8_t motorX_dir = 0;               // X axis
uint8_t motorX_pwm = 0;

// Motors pin definiton (direction, PWM) - (direction: 1=clockwise, 0=counterclockwise)
DC_Motor motor_wrist(5, 6);           
DC_Motor motorY(17, 12);              
DC_Motor motorX(16, 11);              

// Limit switch definition
#define switchX 32
#define switchY 24
#define switch_wrist 30

// *****SETUP*****
void setup(){
  pinMode(switchX, INPUT_PULLUP);                                 // Define limit switches as input
  pinMode(switchY, INPUT_PULLUP);                                       
  pinMode(switch_wrist, INPUT_PULLUP);

  Serial.begin(9600);                                             // Start serial communication with baud rate of 9600

  changePwmFreq();                                                // Change PWM frequency
  deviceInit();                                                   // Device initialization
  }

// *****MAIN LOOP*****
void loop(){
  encoderRead();                                                  // Read encoder position
  armWrestling();                                                 // Wrist motor loop for arm wrestling behavior
  printEncoderPos();                                              // Serial print of encoder position for communication with Unity 3D
  }

// *****FUNCTIONS*****
void encoderRead(){                                               // Read encoder positions and store them into variables
  encoderPos_wrist = encoder_wrist.read();
  encoderPosX = encoderX.read();
  encoderPosY = encoderY.read();
  }

void printEncoderPos(){                                           // Serial printing of encoder positions for the communication with Unity 3D
  Serial.print (encoderPosX);
  Serial.print (' ');
  Serial.print (encoderPosY);
  Serial.print (' ');
  Serial.print (encoderPos_wrist);
  Serial.println ();
  }

// *****DEVICE INITIALIZATION*****                                // Initialize device by pressing limit switches and moving into starting position
void deviceInit(){
  while(!hasBeenInit){                                            // Enter loop if device is not yet initiliazed
    xSwitchVal = digitalRead(switchX);                            // Read limit switch status and store it into variables
    ySwitchVal = digitalRead(switchY);
    wrist_SwitchVal = digitalRead(switch_wrist);

    if(!wrist_SwitchVal) motor_wrist.turn(1, 30);                 // Slowly move each motor unless it presses the limit switch           
    if(!ySwitchVal) motorY.turn(1, 60);
    if(!xSwitchVal) motorX.turn(1, 50);

    if(xSwitchVal) motorX.turn(0, 0);                             // Stop motor if limit switch is pressed
    if(ySwitchVal) motorY.turn(0, 0);
    if(wrist_SwitchVal) motor_wrist.turn(0, 0);

    if((xSwitchVal && ySwitchVal) && wrist_SwitchVal){            // Once all limit switches are pressed, the motors move into starting position 
      hasBeenInit = true;                                         // Variable set to true if all limit switches are pressed
                                             
      encoderX.write(0);                                          // Set encoder positions to 0
      encoderY.write(0);
      encoder_wrist.write(0);
      encoderPosX = 0;
      encoderPosY = 0;
      encoderPos_wrist = 0;

      motorX.turn(0, 0);                                          // Ensure that motors are not moving
      motorY.turn(0, 0);
      motor_wrist.turn(0,0);

      while(encoderPosX < 4000){                                  // Drive motor X to desired position
        encoderPosX = encoderX.read();                                
        motorX.turn(0, 50);//50    
        }
        motorX.turn(0, 0);                                        // Stop motor X after reaching desired position
  
      while(encoderPosY < 2000){                                  // Drive motor Y to desired position    
        encoderPosY = encoderY.read();
        motorY.turn(0, 60); //50
        }
        motorY.turn(0, 0);                                        // Stop motor Y after reaching desired position

      while (encoderPos_wrist > -1450  ){                         // Drive motor wrist to desired position
        encoderPos_wrist = encoder_wrist.read();
        motor_wrist.turn(0,25);                                   
        }
        motor_wrist.turn(0, 0);                                   // Stop motor wrist after reaching desired position
     
      after_initialization = true;                                // Variable set to true once initialization is finished
      }
    }
  }

// *****ARM WRESTLING*****
void armWrestling(){                                              // Activate wrist motor with a certain speed (depending on wrist encoder position and force sensor value)
  while ((after_initialization)&&(encoderPos_wrist > -1400)){     // Enter loop if device is initalized and wrist encoder is within the 'arm wrestling area'
    encoderPos_wrist = encoder_wrist.read();                      // Read encoder positions
    encoderPosX = encoderX.read();
    encoderPosY = encoderY.read();
    
    Value1 = analogRead(sensor1);                                 // Read force sensor signals
    Value2 = analogRead(sensor2);
       
    total = Value1 + Value2;                                      // Calculate force value of sensor signals
    Forcevalue = abs(k*total-d);
    diff = Forcevalue*0.25;
       
    Serial.print (encoderPosX);                                   // Serial printing of encoder positions for the communication with Unity 3D
    Serial.print (' ');
    Serial.print (encoderPosY);
    Serial.print (' ');
    Serial.print (encoderPos_wrist);
    Serial.println ();
       
    vel = 0.3*encoderPos_wrist+420;                               // Calculation of linear function for adequate reduction of speed depending on force value and position
    if(vel < abs(60-diff)){
      motor_wrist.turn(0, abs(vel-diff));
      }
      else{
        motor_wrist.turn(0, abs(60-diff));
        }
    }
    motor_wrist.turn(0, 0);                                       // Stop motor wrist if condition for while loop is not met
  }

// *****CHANGE PWM FREQUENCY*****
void changePwmFreq(){                                             // Change PWM frequency of needed Arduino pins to inaudible frequency of 31 kHz
  TCCR1B &= ~7;
  TCCR4B &= ~7;
  TCCR1B |= 1;
  TCCR4B |= 1;
  }
