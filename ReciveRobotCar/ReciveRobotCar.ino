/* nRF24L01 
 http://arduino-info.wikispaces.com/Nrf24L01-2.4GHz-HowTo
   1 - GND
   2 - VCC 3.3V !!! NOT 5V
   3 - CE to Arduino pin 9
   4 - CSN to Arduino pin 10
   5 - SCK to Arduino pin 13
   6 - MOSI to Arduino pin 11
   7 - MISO to Arduino pin 12
   8 - UNUSED */
   
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define CE_PIN   9
#define CSN_PIN 10
const uint64_t pipe = 0xE8E8F0F0E1LL; 
RF24 radio(CE_PIN, CSN_PIN); 
int joystick[2];  

int pwm1=5,pwm2=6,motorleft1=3,motorleft2=2,motorright1=7,motorright2=4;


void setup()   
{
  Serial.begin(9600);delay(1000);
  Serial.println("Nrf24L01 Receiver Starting");
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();;
  pinMode(pwm1, OUTPUT);   
  pinMode(pwm2, OUTPUT);   
  pinMode(motorleft1, OUTPUT);   
  pinMode(motorleft2, OUTPUT);   
  pinMode(motorright1, OUTPUT);   
  pinMode(motorright2, OUTPUT); 
}


void loop()   
{

  
}
void rx()
{
  if ( radio.available() )
  {
    bool done = false;
    while (!done)
    {
      done = radio.read( joystick, sizeof(joystick) );
      /*Serial.print("X = ");
      Serial.print(joystick[0]);
      Serial.print(" Y = ");      
      Serial.println(joystick[1]);*/
      
      if(joystick[0] >400)
      {
        Serial.println("RIGHT");
      }
      else if(joystick[0] <200)
      {
        Serial.println("LEFT");
      }
      else if(joystick[1] >400)
      {
        Serial.println("FRONT");
      }
      else if(joystick[1] <200)
      {
        Serial.println("BACK");
      }
      else
      { Serial.println("NONE");  }
    }
    delay(200);
  }
}
void forword(int man1,int man2)
{
  analogWrite(pwm1, man1);
  digitalWrite(motorleft1,HIGH);
  digitalWrite(motorleft2,LOW);
  
  analogWrite(pwm2, man2); 
  digitalWrite(motorright1,HIGH);
  digitalWrite(motorright2,LOW);
}

void backword(int man1,int man2)
{
  analogWrite(pwm1, man1);
  digitalWrite(motorleft1,LOW);
  digitalWrite(motorleft2,HIGH);
  
  analogWrite(pwm2, man2); 
  digitalWrite(motorright1,LOW);
  digitalWrite(motorright2,HIGH);
}

void left(int man1,int man2)
{
  analogWrite(pwm1, man1);
  digitalWrite(motorleft1,LOW);
  digitalWrite(motorleft2,HIGH);
  
  analogWrite(pwm2, man2); 
  digitalWrite(motorright1,HIGH);
  digitalWrite(motorright2,LOW);
}

void right(int man1,int man2)
{
  analogWrite(pwm1, man1);
  digitalWrite(motorleft1,HIGH);
  digitalWrite(motorleft2,LOW);
  
  analogWrite(pwm2, man2); 
  digitalWrite(motorright1,LOW);
  digitalWrite(motorright2,HIGH);
}




