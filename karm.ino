/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
Servo myservo4;
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

double r1_1;
double r2_1;
double r3_1;
double r4_1;

int r1=90;
int r2=90;
int r3=90;
int r4=90;

int s1=0;
int s2=0;
int s3=0;
int s4=0;

int r1_step[100];
int r2_step[100];
int r3_step[100];
int r4_step[100];

int r1_goal;
int r2_goal;
int r3_goal;
int r4_goal;

int r1_old;
int r2_old;
int r3_old;
int r4_old;

int r1_now=90;
int r2_now=90;
int r3_now=90;
int r4_now=90;

int r1_arrive;
int r2_arrive;
int r3_arrive;
int r4_arrive;

int r1_ready=0;
int r2_ready=0;
int r3_ready=0;
int r4_ready=0;

int c=0;

int mode=0;

int i=0;

void setup() {
  Serial.begin(9600);
  myservo1.attach(2); 
  myservo2.attach(3); 
  myservo3.attach(4); 
  myservo4.attach(5);  // attaches the servo on pin 9 to the servo object
  pinMode(6, INPUT_PULLUP);   //스위치1번 포트 인풋 풀업 선언(INPUT_PULLUP은 스위치 사용시 풀업저항을 따로 사용하지 않기 위해 사용)
  pinMode(7, INPUT_PULLUP);  //스위치2번 (1번 포트는 rx포트라서 불편하기 때문에 analog5번 포트인 19번 포트 사용)
  pinMode(8, INPUT_PULLUP);   //스위치3번
  pinMode(9, INPUT_PULLUP);   //스위치4번
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
 

}

void loop() {
  r1_1=analogRead(0);
  r2_1=analogRead(1);
  r3_1=analogRead(2);
  r4_1=analogRead(3);

  s4 = digitalRead(6);  // 디지털0번 포트의 값을 읽어 s1에 입력
  s3 = digitalRead(7); // 스위치가 눌리지 않으면 변수값이 1이 되고 눌리면 0이 됨
  s2 = digitalRead(8);
  s1 = digitalRead(9);

  r1=(180-(r1_1/4.111))/3;
  r2=(180-(r2_1/4.111))/3;
  r3=((r3_1/4.111))/3;
  r4=(180-(r4_1/4.111))/3;

  r1=r1*3;
  r2=r2*3;
  r3=r3*3;
  r4=r4*3;

  if(s1==0)
  {
    if(mode==0)
    {
      mode=1;
      led();
    }

    else if(mode==2)
    {
      mode=1;
      led();
    }
    
  }
  
  if(s2==0)
  {
    if(mode==1)
    {
      mode=2;
      led();
    }
    else if(mode==2)
    {
      mode=0;
      led();
    }
  }
  
  if(mode==0)
  {
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    i=0;

    if(s3==0)
    {
      r1_step[c]=r1;
      r2_step[c]=r2;
      r3_step[c]=r3;
      r4_step[c]=r4;
      c++;
      led();
    }

    else if(s4==0)
    {
      c--;
      led();
    }


    myservo1.write(r1);              // tell servo to go to position in variable 'pos'
    myservo2.write(r2);
    myservo3.write(r3);
    myservo4.write(90);
  }

  
  else if(mode==1)
  {
    
    
    digitalWrite(11, LOW);
    digitalWrite(10, HIGH);

    r1_goal=r1_step[i];
    r2_goal=r2_step[i];
    r3_goal=r3_step[i];
    r4_goal=r4_step[i];


    if(r1_old<r1_goal)
    {
      r1_now++;
    }
    else if(r1_old>r1_goal)
    {
      r1_now--;
    }
    else if(r1_old==r1_goal)
    {
      r1_ready=1;
    }

    
    if(r2_old<r2_goal)
    {
      r2_now++;
    }
    else if(r2_old>r2_goal)
    {
      r2_now--;
    }
    else if(r2_old==r2_goal)
    {
      r2_ready=1;
    }

    
    if(r3_old<r3_goal)
    {
      r3_now++;
    }
    else if(r3_old>r3_goal)
    {
      r3_now--;
    }
    else if(r3_old==r3_goal)
    {
      r3_ready=1;
    }

    
    if(r4_old<r4_goal)
    {
      r4_now++;
    }
    else if(r4_old>r4_goal)
    {
      r4_now--;
    }
    else if(r4_old==r4_goal)
    {
      r4_ready=1;
    }

    r1_old=r1_now;
    r2_old=r2_now;
    r3_old=r3_now;
    r4_old=r4_now;

    if(r1_ready==1&&r2_ready==1&&r3_ready==1&&r4_ready==1)
    {
      r1_ready=0;
      r2_ready=0;
      r3_ready=0;
      r4_ready=0;
      i++;
      if(i==c)
      {
        i=0;
      }
    }
    

    myservo1.write(r1_now);              // tell servo to go to position in variable 'pos'
    myservo2.write(r2_now);
    myservo3.write(r3_now);
    myservo4.write(r4_now);
    delay(10);
  }
  else if(mode==2)
  {
    digitalWrite(11,HIGH);
    digitalWrite(10,LOW);
  }


  /*
   Serial.print(r1_goal);   // reads the value of the potentiometer (value between 0 and 1023)
   Serial.print("-"); 
   Serial.print(r2_goal); 
   Serial.print("-"); 
   Serial.print(r3_goal); 
   Serial.print("-"); 
   Serial.print(r4_goal);
   Serial.print("-"); 
   Serial.print(r1_now);   // reads the value of the potentiometer (value between 0 and 1023)
   Serial.print("-"); 
   Serial.print(r2_now); 
   Serial.print("-"); 
   Serial.print(r3_now); 
   Serial.print("-"); 
   Serial.print(r4_now);
   Serial.print("-"); 
   Serial.print(c);
   Serial.print("-"); 
   Serial.print(i);
   Serial.print("-"); 
   Serial.print(s3);
   Serial.print("-"); 
   Serial.print(s4);
   Serial.print("-"); 
   Serial.println(mode);
*/
  
              // sets the servo position according to the scaled value
  delay(10);      

}



void led(void)
{
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  delay(300);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  delay(300);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  delay(300);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  delay(300);
  
  
}

