#include<SoftwareSerial.h>  //  HC-05
#include <Servo.h>
Servo upperservo; 
Servo lowerservo; 
SoftwareSerial Serialk2(8,7);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serialk2.begin(9600);
upperservo.attach(9); //uper arm connection
lowerservo.attach(10); //lower arm connection
upperservo.write(0); 
Serialk2.println(int(EEPROM.read(0)));//
lowerservo.write(0);
Serialk2.println(int(EEPROM.read(1)));//
}
bool flag=0 , flag_A=0;
int angle_up = 0, angle_low = 0;
String msg;
void loop() {
          int motor_speed = 3, time_delay=0, tar_low=0,tar_up=0;
          if (Serial.available()>0)   // to operate from pc
          {
            msg = Serial.readStringUntil('\n');
            Serial.println(msg);
            if(msg[0]=='T')
            {
            int i=1; 
            
            while (msg[i]!='u')
            {
             time_delay=10*time_delay+(msg[i]-48);
             ++i;
             }
             ++i;
            while(msg[i]!='l')
            {
              
              tar_up=10*tar_up+(msg[i]-48);
              ++i;
            }
            ++i;
            while(msg[i]!='e')
            {
              tar_low=10*tar_low+(msg[i]-48);
              ++i;
            }
            Serial.println(time_delay);
            Serial.println(angle_low);
            Serial.println(angle_up);
            start_m(tar_up, tar_low, time_delay);}}
            
            if (Serialk2.available()>0)   // to operate from pc
          {
            
            msg = Serialk2.readStringUntil('\n');
            Serialk2.println("here");
            if(msg[0]=='T')
            {
            int i=1; 
            
            while (msg[i]!='u')
            {
             time_delay=10*time_delay+(msg[i]-48);
             ++i;
             }
             ++i;
            while(msg[i]!='l')
            {
              
              tar_up=10*tar_up+(msg[i]-48);
              ++i;
            }
            ++i;
            while(msg[i]!='e')
            {
              tar_low=10*tar_low+(msg[i]-48);
              ++i;
            }
            Serialk2.println(time_delay);
            Serialk2.println(tar_low);
            Serialk2.println(tar_up);

            start_m(tar_up, tar_low, time_delay);        
            }
            if(msg[0]=='S')
            {
              reset();}
            }}
            
            
           
             
            /*   
            motor_speed = int(msg[4]-48);
            Serial.println(motor_speed);
            flag = 1; 
            }
            else if(msg[0]=='S')
            {
              flag = 0;
              reset();
            }
            else if(msg[0]=='R')
            reset();
          }
          if (Serial12.available()>0)   // to operate from app String is TXXSY     XX - repeat cycle         Y - speed 1-slower 2-slow 3- normal 4-fast    * 4 not applicable
          {
            msg = Serial12.readStringUntil('\n');
            if(msg[0]=='T')
            {
            repeat = (int(msg[1]-48)*10) + int(msg[2]-48);
            motor_speed = int(msg[4]-48);
            Serial.println(repeat);
            Serial.println(motor_speed);
            flag = 1; 
            }
            else if(msg[0]=='S')
            {
              flag = 0;
              reset();
            }
            else if(msg[0]=='R')
            reset();
          }
          if (flag != 0 && one_ex<repeat)
          {
            if(msg[5]=='A')     //first exercise
            {
              start_m(0,0,0,90);
            }
            if(msg[5]=='B')    //2nd
            {
              start_m(0,90,0,0);
            }
            if(msg[5]=='C')      //3rd
            {
              start_m(0,150,0,0);  
            }
              if(msg[5]=='D') //4th
            {
              start_m(0,10,0,0);
            }
            speed_delay(motor_speed);
            //count++;
          }*/
          




void start_m(int upper_stop,int lower_stop,int dur)//angle_up = 0, angle_low = 0;
{
  
int u_angstep=(int(upper_stop)-int(angle_up))*100/dur;
Serialk2.println(int(upper_stop)-int(angle_up));
int l_angstep=(int(lower_stop)-int(angle_low))*100/dur;
Serialk2.println(int(lower_stop)-int(angle_low));  
int flagu=0,flagl=0;

for(int i=0;i<dur/10;i++) 
{
  int flagu=0,flagl=0;
  //upper motor
  if(u_angstep>0){
  if(angle_up>=upper_stop)
  {
    flagu=1;
    }
    else if(angle_up<upper_stop)
    angle_up=angle_up+u_angstep;
    Serialk2.println(angle_up);
  }
else if(u_angstep<0){
  if(angle_up<=upper_stop)
  {
    flagu=1;
    }
    else if(angle_up>upper_stop)
    angle_up=angle_up+u_angstep;
    Serialk2.println(angle_up);
  }
//lower motor
  if(l_angstep>0){
  if(angle_low>=lower_stop)
  {
    flagl=1;
    }
    else if(angle_low<lower_stop)
    angle_low=angle_low+l_angstep;
    Serialk2.println(angle_low);
  }
else if(l_angstep<0){
  if(angle_low<=lower_stop)
  {
    flagl=1;
    }
    else if(angle_low>lower_stop)
    angle_low=angle_low+l_angstep;
    Serialk2.println(angle_low);
  }
  if(flagu==1 ||flagl==1)
  {
    break;
    }
    else{
  upperservo.writeMicroseconds(1000+angle_up*5.88);  
  lowerservo.writeMicroseconds(1000+angle_low*5.88); 
  romWrite();
  } 
delay(10);}
}
void romWrite()
{
  EEPROM.write(0,angle_up);
  EEPROM.write(1,angle_low);
  }

void reset()
{
  while(angle_up!=0||angle_low!=0)
  {
  if(angle_up!=0)
  {
    angle_up--;
    delay(40);
    upperservo.writeMicroseconds(1000+angle_up*5.88);  
    Serialk2.println(1000+angle_up*5.88);
  }
  if(angle_low!=0)
  {
    angle_low--;
    delay(10);
    lowerservo.writeMicroseconds(1000+angle_low*5.88);  
    Serialk2.println(1000+angle_low*5.88);
  }
  }
}



