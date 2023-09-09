
# define echo 5
# define trig 6
# define gndl 12
#define gndr 7
#define outl 13
#define outr 8
#define enl 11
#define enr 10
const int MAX=50;
int mtrspeed=0;
int i=0;
int j=0;
int dryrun=0;
int counter=0;
int turns[MAX];
void setup()
{
  Serial.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(gndl,OUTPUT);
  pinMode(gndr,OUTPUT);
  pinMode(outl,OUTPUT);
  pinMode(outr,OUTPUT);
  pinMode(enl,OUTPUT);
  pinMode(enr,OUTPUT);
}

  /*Serial.println("Dry running...");*/
void loop()
{
 int dist=calcDistance();
  Serial.println(dist);
  if(dist<=8)
  {
    
    if(i+j==2)
    {
      unsigned long startMillis = millis();
        while (millis() - startMillis < 750)//750 is time taken to turn 90 degrees by bot considering speed 20rpm 
      {
       turnLeft();
       Serial.println("back");
      }
      turns[counter]=2;
      counter++;
    }
    else
    {
     int key=0;
      unsigned long startMillis1 = millis();
      while (millis() - startMillis1 < 750) 
      {
        turnRight();
        Serial.println("turn right");
        
       }
      	if(calcDistance()>8)
      	{
          
          key=1;
          turns[counter]=0;
          counter++;
      	}
      if(key!=1)
      {
        unsigned long startMillis2 = millis();
        while (millis() - startMillis2 < 1500) 
      {
       turnLeft();
       Serial.println("turn left");
      }
       turns[counter]=1;
        counter++;
    }
   }
  }
  else
  {
    move();
    Serial.println("move straight");
  }
}
// for fastest
/*
 Serial.println("Moving in fastest time");
  counter=0;*/
/*
  void loop(){
 int dist=calcDistance();
  Serial.println(dist);
  if(dist<=8)
  {
    if(turns[counter]==0){
      unsigned long startMillis = millis();
        while (millis() - startMillis < 750)//750 is time taken to turn 90 degrees by bot considering speed 20rpm 
      {
       turnRight();
       Serial.println("right");
      }
      
    }
    else if(turns[counter]==1)
    {
      unsigned long startMillis1 = millis();
      while (millis() - startMillis1 < 750) 
      {
        turnLeft();
        Serial.println("left");
        
       }
    } 
    else if(turns[counter]==2)
    {
      unsigned long startMillis1 = millis();
      while (millis() - startMillis1 < 1500) 
      {
        turnLeft();
        Serial.println("back");
        
       }
    } 
   counter++;   
  }
  else
  {
    move();
    Serial.println("move straight");
  }
}*/
void move()
{
  mtrspeed=50;
  analogWrite(enl,mtrspeed);
  analogWrite(enr,mtrspeed);
  digitalWrite(outl,HIGH);
  digitalWrite(outr,HIGH);
  digitalWrite(gndl,LOW);
  digitalWrite(gndr,LOW);
  i=0;
  j=0;
}
void turnRight()
{
  if(mtrspeed=50)
  {
  	delay(500);  		//for speed variation
  }
  mtrspeed=20;
  analogWrite(enl,mtrspeed);
  analogWrite(enr,mtrspeed);
  digitalWrite(outl,HIGH);
  digitalWrite(outr,LOW);
  digitalWrite(gndl,LOW);
  digitalWrite(gndr,HIGH);
  i=1;
}
void turnLeft()
{
  mtrspeed=20;
  analogWrite(enl,mtrspeed);
  analogWrite(enr,mtrspeed);
  digitalWrite(outl,LOW);
  digitalWrite(outr,HIGH);
  digitalWrite(gndl,HIGH);
  digitalWrite(gndr,LOW);
  j=1;
}
int calcDistance()
{
  int dist=0;
  digitalWrite(trig,LOW);
  delay(4);
  digitalWrite(trig,HIGH);
  delay(15);
  digitalWrite(trig,LOW);
  int t=pulseIn(echo,HIGH);
  dist=t*(0.034/2);
  return dist;
}






  