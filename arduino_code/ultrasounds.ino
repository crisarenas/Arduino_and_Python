// CONSTANTS
const int trigger = 2; //Trigger pin
const int echo = 3; //Echo pin
long time_taken;
int dist,distance;



// SETUP
void setup() {
Serial.begin(9600); 
pinMode(trigger, OUTPUT);
pinMode(echo, INPUT);
}


// FUNCTION TO CALCULATE THE DISTANCE
void calculate_distance(int trig, int ec)
{
digitalWrite(trig, LOW);
delayMicroseconds(2);
digitalWrite(trig, HIGH);
delayMicroseconds(10);
digitalWrite(trig, LOW);
time_taken = pulseIn(ec, HIGH);
dist= time_taken*0.034/2;
if (dist>60)
dist = 60;
}



// LOOP
void loop() { 
calculate_distance(trigger,echo);
distance =dist; //get distance of the sensor

//Pause Modes -Hold
if (distance >40 && distance <60){
  Serial.println("Play/Pause"); delay (500);
  } 
calculate_distance(trigger,echo);
distance =dist;

//Control Modes
//Lock Left - Control Mode
if (distance>=13 && distance<=17)
{
  delay(100); //Hand Hold Time
  calculate_distance(trigger,echo);
  distance =dist;;
  if (distance>=13 && distance<=17)
  {
    Serial.println("Left Locked");
    while(distance<=40)
    {
      calculate_distance(trigger,echo);
      distance =dist;
      if (distance<10) //Hand pushed in 
      {Serial.println ("Volume Increased"); delay (300);}
      if (distance>20) //Hand pulled out
      {Serial.println ("Volume Decreased"); delay (300);}
    }
  }
}

delay(200);
}
