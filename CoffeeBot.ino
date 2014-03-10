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

void setup()
{
  pinMode( leftMotorPin, OUTPUT );
  pinMode( rightMotorPin, OUTPUT );
  pinMode( leftLed, OUTPUT );
  pinMode( rightLed, OUTPUT );
  pinMode( led, OUTPUT );
  
  pinMode( leftLightSensor, INPUT );
  pinMode( rightLightSensor, INPUT );
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
  if ( analogRead( leftLightSensor ) < analogRead( rightLightSensor ) )
  {
    digitalWrite( led, HIGH );
    digitalWrite( leftMotorPin, HIGH );
    digitalWrite( rightMotorPin, LOW );
    digitalWrite( leftLed, LOW );
    digitalWrite( rightLed, HIGH );
  }
  else if ( analogRead( leftLightSensor ) > analogRead( rightLightSensor ) )
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

