//green pwm
// yellow 
//orange dir 1

#include <Servo.h>
#include <PS3BT.h>
#include <usbhub.h>

USB Usb;
BTD Btd( &Usb );
PS3BT PS3(&Btd);

Servo front_Servo;
Servo arm_Servo;
Servo thr_Servo;

int M_1D_1 = 31;
int M_1D_2 = 33;

int M_2D_1 = 37;
int M_2D_2 = 39;




int PWM_1 = 2;
int PWM_2 = 3; //RIGHT
int pwm_value1;
int pwm_value2;
int value1 = 0;
int value2 = 0;


int counter = 160;


void setup()
{
  Serial.begin(115200);
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
  
  front_Servo.attach( 9 ); 
  arm_Servo.attach( 10 );
  thr_Servo.attach( 11 );
  thr_Servo.write( 0 );
  //delay(500);
  //thr_Servo.write( 50 );
   
  

  
  pinMode( M_1D_1, OUTPUT ); // Motor 1 Dir 1
  pinMode( M_1D_2, OUTPUT ); // Motor 1 Dir 2
  
  pinMode( M_2D_1, OUTPUT ); // Motor 2 Dir 1
  pinMode( M_2D_2, OUTPUT ); // Motor 2 Dir 2
  
  pinMode( PWM_1, OUTPUT ); // PWM 1
  pinMode( PWM_2, OUTPUT ); // PWM 2- RIGHT MOTOR
  
  
  
  
  
  
  
  
}

void loop()
{ 
  Usb.Task();
  
   if ( PS3.PS3Connected || PS3.PS3NavigationConnected ) 
   {  
     
     
       if (PS3.getAnalogHat(LeftHatX) > 137 || PS3.getAnalogHat(LeftHatX) < 117 || PS3.getAnalogHat(LeftHatY) > 137 || PS3.getAnalogHat(LeftHatY) < 117 || PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) < 117 || PS3.getAnalogHat(RightHatY) > 137 || PS3.getAnalogHat(RightHatY) < 117) {
              //Serial.print(F("\r\nLeftHatX: "));
              //Serial.print(PS3.getAnalogHat(LeftHatX));
              //Serial.print(F("\tLeftHatY: "));
      
               // Serial.print(PS3.getAnalogHat(LeftHatY));
      
               
                     value1 = PS3.getAnalogHat( RightHatX ) - 128;
                     value2 = 255- PS3.getAnalogHat( LeftHatY ) - 128;
                       Serial.print( " \n");
                        Serial.print(value1 );
                     
                if( value2 >= 25 )
                {     
                    Move_Fwd();
                    if( value1 >= 20 ){
                        pwm_value1 = value1*2 -1 ;
                        pwm_value2 = 50 ;
      
                        analogWrite( PWM_1, pwm_value1);
                        analogWrite( PWM_2, pwm_value2);
                    } 
                    else if( value1 <= -20 )
                    {
                        pwm_value1 =  50;
                        pwm_value2 = 2*abs(value1+1);
                      
      
                        analogWrite( PWM_1, pwm_value1);
                        analogWrite( PWM_2, pwm_value2);
                    }
                    else 
                    {
                  
                         pwm_value1 = value2*2 - 1;
                         pwm_value2 = value2*2 - 1;
      
                        analogWrite( PWM_1, pwm_value1);
                        analogWrite( PWM_2, pwm_value2);
                    }
                }
                
                /////////// REVERSE
                else if( value2 <= -20 )
                {
                  Move_Bwd();
                  
                   if( value1 >= 20 ){
                        pwm_value1 = 2*abs(value1 - 1) ;
                        pwm_value2 =  50;
      
                        analogWrite( PWM_1, pwm_value1);
                        analogWrite( PWM_2, pwm_value2);
                    } 
                    else if( value1 <= -20 )
                    {
                        pwm_value1 = 50  ;
                        pwm_value2 = 2*abs(value1 + 1) ;
      
                        analogWrite( PWM_1, pwm_value1);
                        analogWrite( PWM_2, pwm_value2);
                    }
                    else 
                    {
                  
                         pwm_value1 = abs(value2);
                         pwm_value2 = abs(value2);
      
                        analogWrite( PWM_1, pwm_value1);
                        analogWrite( PWM_2, pwm_value2);
                  }
                }
                
                else
                {
                   
                  
                   if( value1 >= 40 ){
                        Rotate_Right();
                        
                        pwm_value1 = abs(value1 - 1) ;
                        pwm_value2 =  abs(value1 - 1) ;
      
                        analogWrite( PWM_1, pwm_value1);
                        analogWrite( PWM_2, pwm_value2);
                    } 
                    else if( value1 <= -40 )
                    {
                        Rotate_Left();
                        pwm_value1 = abs(value1 + 1) ;
                        pwm_value2 = abs(value1 + 1) ;
      
                        analogWrite( PWM_1, pwm_value1);
                        analogWrite( PWM_2, pwm_value2);
                    }
                    
                   else
                   { 
                       Active_Brake();
                     
                   }
                   
                }
                
                
                
                
    }
    
    
       if ( PS3.getButtonClick(PS) ) 
       {
            //Serial.print(F("\r\nPS"));
            PS3.disconnect();
       }
       ///////////////////////////////////////////////     
       ////////////////////////////////////////////////
       if (PS3.getButtonClick(TRIANGLE)) 
       {
            //Serial.print(F("\r\nUp"));
            
            if (PS3.PS3Connected) 
            {
                PS3.setLedOff();
                PS3.setLedOn(LED1);
                Grabbing();
            }
       }
       ///////////////////////////////////////////////
       ///////////////////////////////////////////////
        if (PS3.getButtonClick(L1)) 
       {
            //Serial.print(F("\r\nUp"));
            
            if (PS3.PS3Connected) 
            {
                PS3.setLedOff();
                PS3.setLedOn(LED4);
                Active_Brake();
            }
       }
       //////////////////////////////////////////////
       //////////////////////////////////////////////
        if (PS3.getButtonClick(R2)) 
       {
            //Serial.print(F("\r\nUp"));
            
            if (PS3.PS3Connected) 
            {
                PS3.setLedOff();
                PS3.setLedOn(LED3);
                Releasing();
            }
       }
       ////////////////////////////////////////////////
       // Control arm with precision
       if (PS3.getButtonClick(R1)) 
       {
            //Serial.print(F("\r\nUp"));
            
            if (PS3.PS3Connected) 
            {
                PS3.setLedOff();
                PS3.setLedOn(LED2);
                arm_Servo.write( 9 );
                
                if( PS3.getButtonClick( CROSS ) )
                {
                    front_Servo.write( 165 );
                }
            }
       }
       
       
       ////////////////////////////////////////////////////////
       ///////////////////////////////////////////////////////
       //Clutch and MOTOR
        if (PS3.getButtonClick(RIGHT)) 
       {
            //Serial.print(F("\r\nUp"));
            
            if (PS3.PS3Connected) 
            {
                PS3.setLedOff();
                PS3.setLedOn(LED3);
                thr_Servo.write( 50 );
                
                delay(500);
                thr_Servo.write( 0 );
            }
       }
      while (PS3.getButtonClick(UP)) 
       {
            //Serial.print(F("\r\nUp"));
            
            if (PS3.PS3Connected) 
            {
                PS3.setLedOff();
                PS3.setLedOn(LED4);
                front_Servo.write( abs(PS3.getAnalogHat( RightHatY ) ) );
            }
       }
       
       
       
       }
   }
  
  /*
  Move_Fwd();
  delay( 2000 );
  Active_Brake();
  Grabbing();
  Move_Fwd();
  delay( 2000 );
  Active_Brake();
  
  
*/



void Grabbing()
{
    front_Servo.write( 160 );
    arm_Servo.write( 45 );
    
    delay( 300 );
    
    arm_Servo.write( 8 );
    delay( 300 );
    front_Servo.write( 150);delay( 100 );
    front_Servo.write( 135);delay( 100 );
    front_Servo.write( 125);delay( 100 );
    front_Servo.write( 95);delay( 100 );
    delay( 300 );
    arm_Servo.write( 50 );
    delay( 200 );
}

void Releasing()
{
  arm_Servo.write( 0 );
  delay( 300 );
  front_Servo.write( 165 );
  delay( 300 );
  arm_Servo.write( 50 );
  delay( 300 );
  front_Servo.write( 105 );
  
}



void Active_Brake()
{
  digitalWrite( M_1D_1, HIGH );
  digitalWrite( M_1D_2, HIGH ); 
 
  digitalWrite( M_2D_1, HIGH );
  digitalWrite( M_2D_2, HIGH );
  
  analogWrite( PWM_1,  255 );
  analogWrite( PWM_2,  255 );
}
//Move Forward
void Move_Fwd()
{
  digitalWrite( M_1D_1, HIGH );
  digitalWrite( M_1D_2, LOW );

  digitalWrite( M_2D_1, HIGH );
  digitalWrite( M_2D_2, LOW );

  analogWrite( PWM_1,  0 );
  analogWrite( PWM_2,  0 );
}
//Move backword
void Move_Bwd()
{
  digitalWrite( M_1D_1, LOW );
  digitalWrite( M_1D_2, HIGH );

  digitalWrite( M_2D_1, LOW );
  digitalWrite( M_2D_2, HIGH );

  analogWrite( PWM_1,  0 );
  analogWrite( PWM_2,  0 );
}

void Rotate_Right()
{
    digitalWrite( M_1D_1, High );
    digitalWrite( M_1D_2, LOW );

    digitalWrite( M_2D_1, LOW );
    digitalWrite( M_2D_2, HIGH );

    analogWrite( PWM_1,  0 );
    analogWrite( PWM_2,  0 );
}

void Rotate_Left()
{
    
    digitalWrite( M_1D_1, LOW );
    digitalWrite( M_1D_2, HIGH );

    digitalWrite( M_2D_1, HIGH );
    digitalWrite( M_2D_2, LOW );

    analogWrite( PWM_1,  0 );
    analogWrite( PWM_2,  0 );
    
}

