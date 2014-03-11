/*
This program makes your robot either seek light or avoid light, depending on how it is wired up.
Try this program first, and then start modifying it to give your robot the personality you desire.
Shine a flashlight, or hold your hand over a light sensor, to change the behaviour.
*/

const int leftMotorPin = 5;
const int rightMotorPin = 3;
const int leftLightSensor = A0;
const int rightLightSensor = A2;
const int leftLed = 11;
const int rightLed = 9;
const int led = 13;

const int SAMENESS_THRESHOLD = 0;

String leftStr, rightStr, outStr;

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

  int leftLightSensorVal = analogRead( leftLightSensor );
  int rightLightSensorVal = analogRead( rightLightSensor );
  int diff = leftLightSensorVal - rightLightSensorVal;
  int percent = ( (float)leftLightSensorVal / rightLightSensorVal ) * 100;
  outStr = leftStr + leftLightSensorVal + rightStr + rightLightSensorVal + ", diff=" + diff + ", percent=" + percent;
  
  Serial.println( outStr );
  
  //if ( leftLightSensorVal < rightLightSensorVal )
  if ( diff < -SAMENESS_THRESHOLD )
  {
    digitalWrite( led, HIGH );
    digitalWrite( leftMotorPin, HIGH );
    digitalWrite( rightMotorPin, LOW );
    digitalWrite( leftLed, LOW );
    digitalWrite( rightLed, HIGH );
  }
  else if ( diff > SAMENESS_THRESHOLD )
  //else
  {
    digitalWrite( led, LOW );  
    digitalWrite( leftMotorPin, LOW );
    digitalWrite( rightMotorPin, HIGH );
    digitalWrite( leftLed, HIGH );
    digitalWrite( rightLed, LOW );
  }
  else
  {
    digitalWrite( led, LOW );  
    digitalWrite( leftMotorPin, HIGH );
    digitalWrite( rightMotorPin, HIGH );
    digitalWrite( leftLed, HIGH );
    digitalWrite( rightLed, HIGH );
  }
  
}

