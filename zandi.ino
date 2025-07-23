#define DEBUG
#undef DEBUG

#ifdef DEBUG
#define debugbegin(x) Serial.begin(x)
#define debugln(x)    Serial.println(x)
#define debug(x)      Serial.print(x)
#else
#define debugbegin(x)
#define debugln(x)
#define debug(x)
#endif

#define EN1 2
#define EN2 3
#define IN3 50
#define IN4 51
#define IN1 52
#define IN2 53
#define CALIB_BTN 8  

#define MRF(pwm) 
digitalWrite(IN1, LOW);  
digitalWrite(IN2, HIGH); 
analogWrite(EN1, pwm);
#define MRB(pwm) 
digitalWrite(IN1, HIGH); 
digitalWrite(IN2, LOW);  
analogWrite(EN1, pwm);
#define MRS()    
digitalWrite(IN1, HIGH); 
digitalWrite(IN2, HIGH);
 analogWrite(EN1, 255);
#define MLF(pwm)
 digitalWrite(IN3, HIGH); 
 digitalWrite(IN4, LOW); 
  analogWrite(EN2, pwm);
#define MLB(pwm) 
digitalWrite(IN3, LOW); 
 digitalWrite(IN4, HIGH);
  analogWrite(EN2, pwm);
#define MLS()   
 digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
   analogWrite(EN2, 255);

int THRESHOLD = 600;  
void setup() {
  debugbegin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(CALIB_BTN, INPUT_PULLUP);  
  delay(500); 

  if (digitalRead(CALIB_BTN) == LOW) {
     autoCalibrateThreshold();
  }
}

void autoCalibrateThreshold() {
  const int sampleCount = 100;
  long total = 0;

  debugln("Calibrating...");

  for (int i = 0; i < sampleCount; i++) {
    for (int a = 0; a < 15; a++) {
      total += analogRead(A0 + a);
    }
    delay(5);
  }

  long avg = total / (sampleCount * 15);
  THRESHOLD = avg;

  debug("New THRESHOLD = ");
  debugln(THRESHOLD);
}

unsigned int counter = 0;

void loop() {
  bool sensors[15];
  for (int i = 0; i < 15; i++) {
    sensors[i] = analogRead(A0 + i) > THRESHOLD;
  }

  for (int i = 0; i < 15; i++) {
    debug(sensors[i] ? "1" : "0");
  }
  debugln("");

  if (sensors[7]) {
    MLF(255)
    MRF(255)
  } else if (sensors[8]) {
    MLF(255)
    MRF(150)
  } else if (sensors[6]) {
    MLF(150)
    MRF(255)
  } else if (sensors[9]) {
    MLF(255)
    MRF(70)
  } else if (sensors[5]) {
    MLF(70)
    MRF(255)
  } else if (sensors[10]) {
    MLF(255)
    MRS()
  } else if (sensors[4]) {
    MLS()
    MRF(255)
  } else if (sensors[11]) {
    MLF(255)
    MRB(90)
  } else if (sensors[3]) {
    MLB(90)
    MRF(255)
  } else if (sensors[12]) {
    MLF(255)
    MRB(180)
  } else if (sensors[2]) {
    MLB(180)
    MRF(255)
  } else if (sensors[13]) {
    MLF(255)
    MRB(225)
  } else if (sensors[1]) {
    MLB(225)
    MRF(255)
  } else if (sensors[14]) {
    MLF(255)
    MRB(255)
  } else if (sensors[0]) {
    MLB(255)
    MRF(255)
  }
}
