


// wrote most of this in an ADHD trance, will add proper comments at some point



const int trigPin1 = 7;
const int echoPin1 = 8;

const int trigPin2 = 10;
const int echoPin2 = 11;

const int trigPin3 = 13;
const int echoPin3 = 14;

const int max = 200;
const int warn = 100;
const int sep = 5;

bool one = 0;
bool two = 0;
bool three = 0;


void setup() {
  // initialize serial communication
  Serial.begin(9600);
  pinMode(trigPin1,OUTPUT);
  pinMode(echoPin1,INPUT);
  
  pinMode(trigPin2,OUTPUT);
  pinMode(echoPin2,INPUT);
}

void loop() {
  long one, two, three, duration1, duration2, duration3, cm1, cm2, cm3, warn;

  one = 0;
  two = 0;
  three = 0;  

  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  cm1 = microsecondsToCentimeters(duration1);
  if (cm1 < max) {
    Serial.print("dist1 = ");
    Serial.print(cm1);
    Serial.print("cm. ");
    one = 1;
  } else {
    Serial.println("No object detected");
  }
  delayMicroseconds(30);

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  cm2 = microsecondsToCentimeters(duration2);
  if (cm2 < max) {
    Serial.print("dist2 = ");
    Serial.print(cm2);
    Serial.print("cm. ");
    two = 1;
  } else {
    Serial.println("No object detected");
  }
  delayMicroseconds(30);

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  cm3 = microsecondsToCentimeters(duration3);
  if (cm3 < max) {
    Serial.print("dist3 = ");
    Serial.print(cm3);
    Serial.print("cm. ");
    three = 1;
  } else {
    Serial.println("No object detected");
  }

  // Classifying which region the object is in. Not yet able to distinguish
  // multiple objects, definitely possible but may make code slower.
  if (one = 1, two = 0, three = 0) {
    Serial.print("Left. Distance: ");
    Serial.print(cm1);
    Serial.print("cm");
  } else if (one = 0, two = 0, three = 1) {
    Serial.print("Right. Distance: ");
    Serial.print(cm3);
    Serial.print("cm");
  } else if (one = 0, two = 1, three = 0) {
    // Centre region has "warning range" differentiation
    if (cm2 < warn) {
      Serial.print("CAUTION. ");
      Serial.print(cm2);
      Serial.print("cm");
    } else {
      Serial.print("Centre - caution. Distance: ");
      Serial.print(cm2);
      Serial.print("cm");
    }
  } else if (one = 1, two = 1, three = 0) {
    Serial.print("Centre-left. Distance: ");
    Serial.print(0.5*(cm1 + cm2));
    Serial.print("cm");
  } else if (one = 0, two = 1, three = 1) {
    Serial.print("Centre-right. Distance: ");
    Serial.print(0.5*(cm2 + cm1));
    Serial.print("cm");
  } else {
    Serial.print("Error: multiple objects");
  }


}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}








