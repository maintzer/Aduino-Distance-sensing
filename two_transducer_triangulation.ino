

const int trigPin1 = 7;
const int echoPin1 = 8;

const int trigPin2 = 10;
const int echoPin2 = 11;

const int sep = 10;// list in CENTIMETRES
const int threshold = 100;


void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  pinMode(trigPin1,OUTPUT);
  pinMode(echoPin1,INPUT);
  
  pinMode(trigPin2,OUTPUT);
  pinMode(echoPin2,INPUT);
}

void loop() {
  // establish variables 
  long duration1, duration2, cm1, cm2, x, y;


  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  

  // for 1st transducer (pin 7/8)
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  duration1 = pulseIn(echoPin1, HIGH);

  delayMicroseconds(30);

  // for 2nd transducer (pin 10/11)
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  duration2 = pulseIn(echoPin2, HIGH);

  // convert the time into a distance
  cm1 = microsecondsToCentimeters(duration1);
  cm2 = microsecondsToCentimeters(duration2);

  x = triangulatex(cm1, cm2, sep);
  y = triangulatey(cm1, x);


  if (cm1 < threshold) {
    Serial.print("Distance 1: ");
    Serial.print(cm1);
    Serial.print("cm.   ");
  } else {
    Serial.print("No object at 1.   ");
  }
  if (cm2 < threshold) {
    Serial.print("Distance 2: ");
    Serial.print(cm2);
    Serial.print("cm.   ");
  } else {
    Serial.print("No object at 2.   ");
  }
  Serial.println();
  if ((cm1 < threshold) && (cm2 < threshold)) {
      Serial.print("x = ");
      Serial.print(x);
      Serial.print("cm  ");
      Serial.print("y = ");
      Serial.print(y);
      Serial.print("cm");
      Serial.println();
    } else {
      Serial.println("No triangulation possible.");
    }

  

  delay(1000);
}


long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The sound travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}

long triangulatex(long cm1,long cm2,long sep) {
  return (sep*sep + cm1*cm1 - cm2*cm2)/(2*sep);
}

long triangulatey(long cm1, long x) {
  return sqrt(cm1*cm1 - x*x);
}




