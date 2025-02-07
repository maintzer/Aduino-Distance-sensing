/*
  This code is based on the Arduino IDE's inbuilt PING sensor code, which can be found by going to File -> Examples -> sensors in the Arduino IDE. #
  Some modifications have been made, for example because the PING sensor uses one pin for the trigger and echo signal, whereas many other transducers such as 
  the highly popular HC-SR04 use two separate pins. 
*/

// setting which board pins the echo and trigger pins in the sensor will link to (arbitary of course). 
const int trigPin = 7;
const int echoPin = 8;

// threshold distance for your sensor. 
const int threshold = 105;



void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
}

void loop() {
  // establish variables for the loop
  long duration, cm, cal;
	
  // A calibration constant (usually unnecessary)
  cal = 0
	  
  // The sensor is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  // we use the trigger ping for all of this, in a PING sensor this would
  // be the same as the echo sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);

  // duration is the time in microseconds from the sending of the ping
  // to the reception of its echo off of an object - we use echo pin for this
  duration = pulseIn(echoPin, HIGH);

  // convert duration into a distance in cm and check if it's in threshold,
  // before outputting
  cm = microsecondsToCentimeters(duration);
  if (cm < threshold) {
    Serial.print("Distance: ");
    Serial.print(cm + cal);
    Serial.print("cm");
    Serial.println();
  } else {
    Serial.println("No object");
  }

  // the delay between readings. can set this pretty low if you like but becomes a bit 
  // unreadble as it moves too fast
  delay(100);
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The sound travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}




// Hope this is useful to somebody!
