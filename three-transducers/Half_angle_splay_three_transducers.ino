// wrote most of this in an ADHD trance, will add proper comments at some point
// comments added, code tested, bugs (mostly) fixed. Enjoy! :p


// assign which Arduino pins the trigger and echo pins of each transducer connect to. I've spaced them out a bit for convenience.
const int trigPin1 = 2;
const int echoPin1 = 3;

const int trigPin2 = 4;
const int echoPin2 = 5;

const int trigPin3 = 7;
const int echoPin3 = 8;

const int max = 200;
const int warn = 100;
const int sep = 5;

// some variables we'll use to identify which region an object is in
bool one = 0;
bool two = 0;
bool three = 0;

// the delay in milliseconds between transducers firing. Use to slow down the code and make it readable.
int delt = 300


void setup() {
  // initialize serial communication
  Serial.begin(9600);
  
  // tell the Arduino which pins are inputs and outputs
  pinMode(trigPin1,OUTPUT);
  pinMode(echoPin1,INPUT);
  
  pinMode(trigPin2,OUTPUT);
  pinMode(echoPin2,INPUT);

  pinMode(trigPin3,OUTPUT);
  pinMode(echoPin3,INPUT);
}


// the main loop
void loop() {
  //declare every variable we use in the loop
  long one, two, three, duration1, duration2, duration3, cm1, cm2, cm3, warn, delt;

  // set location variables back to zero at the start of the loop
  one = 0;
  two = 0;
  three = 0;  

  // fire the trigger pin for the first transducer. We later do the same for the other two
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // record the time delay
  duration1 = pulseIn(echoPin1, HIGH);
  // convert to centimetres
  cm1 = microsecondsToCentimeters(duration1);
  // check if it's in range
  if (cm1 < max) {
    Serial.print("dist1 = ");
    Serial.print(cm1);
    Serial.print("cm. ");
    one = 1;
  } else {
    Serial.print("No object detected   ");
  }

  // time delay before we make the next reading. mostly to make the output readable.
  delay(delt);

  // all the same stuff as for transducer 1
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
    Serial.print("No object detected   ");
  }
  delay(delt);

  // and again, now for transducer 3
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  cm3 = microsecondsToCentimeters(duration3);
  if (cm3 < max) {
    Serial.print("dist3 = ");
    Serial.print(cm3);
    Serial.print("cm. ");
    three = 1;
  } else {
    Serial.print("No object detected   ");
  }
  delay(delt);
  
  // I used these for debugging. Delete if you like.
  Serial.println();
  Serial.print(one);
  Serial.print(two);
  Serial.println(three);

  // Classifying which region the object is in. Not yet able to distinguish between multiple objects, probably possible but may make code slower.
  // Nothing in range
  if (one == 0 && two == 0 && three == 0) {
    Serial.print("No object detected");
  } else if (one == 1 && two == 0 && three == 0) { // left region
    Serial.print("Left. Distance: ");
    Serial.print(cm1);
    Serial.print("cm");
  } else if (one == 0 && two == 0 && three == 1) { // right region
    Serial.print("Right. Distance: ");
    Serial.print(cm3);
    Serial.print("cm");
  } else if (one == 0 && two == 1 && three == 0) { // centre region
    // Centre region has "warning range" differentiation. Here I've set it to 100cm.
    if (cm2 < warn) {
      Serial.print("CAUTION. ");
      Serial.print(cm2);
      Serial.print("cm");
    } else {
      Serial.print("Centre - caution. Distance: ");
      Serial.print(cm2);
      Serial.print("cm");
    }
  } else if (one == 1 && two == 1 && three == 0) { // centre-left region
    Serial.print("Centre-left. Distance: ");
    Serial.print(0.5*(cm1 + cm2));
    Serial.print("cm");
  } else if (one == 0 && two == 1 && three == 1) { // centre-right region
    Serial.print("Centre-right. Distance: ");
    Serial.print(0.5*(cm2 + cm1));
    Serial.print("cm");
  } else { // if all 3 sensors fire or just the left and right ones.
    Serial.print("Error: multiple objects");
  }

  // just moving the serial down to make it more readable.
  Serial.println();
  Serial.println();

  // delay again
  delay(delt);

}

// function to convert ms to cm
long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}








