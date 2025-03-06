
const int D3_PIN = 3;
const int D5_PIN = 5;
const int D6_PIN = 6;

void setup() {
  // Stel de pinnen in als uitgangen
  pinMode(D3_PIN, OUTPUT);
  pinMode(D5_PIN, OUTPUT);
  pinMode(D6_PIN, OUTPUT);

  Serial.begin(9600);

  randomSeed(analogRead(0));
}

void loop() {
  int A = random(1000); // 0 tot 999
  int B = random(1000);
  int C = random(1000);
  int D = random(1000);


  Serial.print("A: "); Serial.print(A);
  Serial.print(", B: "); Serial.print(B);
  Serial.print(", C: "); Serial.print(C);
  Serial.print(", D: "); Serial.println(D);

  if (A > B || A < C) {
    digitalWrite(D3_PIN, HIGH);
  } else {
    digitalWrite(D3_PIN, LOW);
  }

  if (C > A && A < B) {
    digitalWrite(D5_PIN, HIGH);
  } else {
    digitalWrite(D5_PIN, LOW);
  }

  if (B > C && B > A && C < A) {
    digitalWrite(D6_PIN, HIGH);
  } else {
    digitalWrite(D6_PIN, LOW);
  }


  if (D > A && D > B && D > C) {
    blinkAllLeds();
  }


  delay(10000);
}

void blinkAllLeds() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(D3_PIN, HIGH);
    digitalWrite(D5_PIN, HIGH);
    digitalWrite(D6_PIN, HIGH);
    delay(100);
    digitalWrite(D3_PIN, LOW);
    digitalWrite(D5_PIN, LOW);
    digitalWrite(D6_PIN, LOW);
    delay(100);
  }
}
