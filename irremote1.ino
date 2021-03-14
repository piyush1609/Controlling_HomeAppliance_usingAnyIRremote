#include <IRremote.h>
const int RECV_PIN = 2;
int toggelState_1 = 0;
int toggelState_2 = 0;
int toggelState_3 = 0;
int speed=75;        
unsigned long lastCode; 
IRrecv irrecv(RECV_PIN);
decode_results results;

int fan = 5;
int bulb1 = 11;
int bulb2 = 12;
void setup()
{
  irrecv.enableIRIn();

  pinMode(fan , OUTPUT);
  pinMode(bulb1 , OUTPUT);
  pinMode(bulb2 , OUTPUT);

}
 
void loop() {
if(irrecv.decode(&results)) //this checks to see if a code has been received
{ switch(results.value)
  {
    case 0xFD08F7:                  //button 1 for Bulb 1
     {if(toggelState_1 == 0)
       {digitalWrite(bulb1, HIGH);
        toggelState_1=1;
        }
      else { digitalWrite(bulb1, LOW);
            toggelState_1=0;
             }
     break;}
     
     case 0xFD8877:                //button 2 for bulb 2
     {if(toggelState_2 == 0)
       {digitalWrite(bulb2, HIGH);
        toggelState_2=1;
         }
      else { digitalWrite(bulb2, LOW);
            toggelState_2=0;
             }
     break;}
     
     case 0xFD48B7:        //button 3 for fan
     {if(toggelState_3 == 0)
       {analogWrite(fan, speed);
        toggelState_3=1;
         }
      else { analogWrite(fan,0);
            toggelState_3=0;
             }
     break;}
    
    case 0xFD10EF:              //lower triagle fan to reduce speed r 
    {if(toggelState_3==1)
    {speed =speed - 75 ;
   if (speed < 75) {
      speed = 75; }
  analogWrite(fan,speed);
              }
  break;}
  
    case 0xFD50AF:                //upper triagle fan speed increase
  {if(toggelState_3==1)
  {
    speed = speed + 75 ;
    if (speed > 255) {
      speed = 255; }
  analogWrite(fan,speed);
    }
    break;}

     
  }
     delay(30);    // Add delay to prevent false readings
    //receive the next value  
    irrecv.resume();

    
}}
