/*
This program makes your robot either seek light or avoid light, depending on how it is wired up.
Try this program first, and then start modifying it to give your robot the personality you desire.
Shine a flashlight, or hold your hand over a light sensor, to change the behaviour.
*/
//TODO: Startup and turn left 1 second, right 2 seconds, left 1 second to get back to start.  Then 
//every 5 seconds, stop for a bit, look left & right again, then resume light seeking.
const int leftMotorPin = 5;
const int rightMotorPin = 3;
const int leftLightSensor = A0;
const int rightLightSensor = A2;
const int leftLed = 11;
const int rightLed = 9;
const int led = 13;

const int SAMENESS_THRESHOLD = 2;

String leftStr, rightStr, outStr;

const unsigned int FIRST_PERIOD_MS = 2000;
const unsigned int TURN_EVERY_PERIOD_MS = 5000;
const unsigned int TURN_DURATION_MS = 500;

void setup()
{
  pinMode( leftMotorPin, OUTPUT );
  pinMode( rightMotorPin, OUTPUT );
  pinMode( leftLed, OUTPUT );
  pinMode( rightLed, OUTPUT );
  pinMode( led, OUTPUT );
  
  pinMode( leftLightSensor, INPUT );
  pinMode( rightLightSensor, INPUT );
  
  Serial.begin( 9600 );
  leftStr = String( "left: " );
  rightStr = String( ", right: " );
  outStr = String();
}

void loop()
{
/*
  digitalWrite( led, HIGH );
  digitalWrite( leftMotorPin, HIGH );
  
  delay( 2000 );

  digitalWrite( led, LOW );  
  digitalWrite( leftMotorPin, LOW );
  
  delay( 2000 );
*/

  unsigned long currentMs = millis();
  
  if ( currentMs < FIRST_PERIOD_MS )  //First period after boot.
  {
    turnRight();
    return;
  }
  else if ( currentMs % TURN_EVERY_PERIOD_MS < TURN_DURATION_MS )  //Every X seconds, turn a random direction for Y seconds, to make things more interesting.
  {
    long randy = random( 2 );
    if ( randy == 0 )
    {
      turnLeft();
    }
    else
    {
      turnRight();
    }
    
    return;
  }

  int leftLightSensorVal = analogRead( leftLightSensor );
  int rightLightSensorVal = analogRead( rightLightSensor );
  int diff = leftLightSensorVal - rightLightSensorVal;
  int percent = ( (float)leftLightSensorVal / rightLightSensorVal ) * 100;
  outStr = leftStr + leftLightSensorVal + rightStr + rightLightSensorVal + ", diff=" + diff + ", percent=" + percent;
  
  Serial.println( outStr );
  
  //if ( leftLightSensorVal < rightLightSensorVal )
  if ( diff < -SAMENESS_THRESHOLD )
  {
    turnRight();
  }
  else if ( diff > SAMENESS_THRESHOLD )
  //else
  {
    turnLeft();
  }
  else
  {
    goStraight();
  }
  
}

void goStraight()
{
    digitalWrite( led, LOW );  
    digitalWrite( leftMotorPin, HIGH );
    digitalWrite( rightMotorPin, HIGH );
    digitalWrite( leftLed, LOW );
    digitalWrite( rightLed, LOW );
}

void turnLeft()
{
    digitalWrite( led, LOW );  
    digitalWrite( leftMotorPin, LOW );
    digitalWrite( rightMotorPin, HIGH );
    digitalWrite( leftLed, HIGH );
    digitalWrite( rightLed, LOW );
}

void turnRight()
{
    digitalWrite( led, HIGH );
    digitalWrite( leftMotorPin, HIGH );
    digitalWrite( rightMotorPin, LOW );
    digitalWrite( leftLed, LOW );
    digitalWrite( rightLed, HIGH );
}

