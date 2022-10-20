const int switchPin1 = 4;

void setup() {
  Serial.begin(115200);
  pinMode(switchPin1, OUTPUT);
}

void loop() {
  // Normally Open configuration, send LOW signal to let current flow
  // (if you're usong Normally Closed configuration send HIGH signal)
  digitalWrite(switchPin1, LOW);
  Serial.println("Current Flowing");
  delay(5000); 
  
  // Normally Open configuration, send HIGH signal stop current flow
  // (if you're usong Normally Closed configuration send LOW signal)
  digitalWrite(switchPin1, HIGH);
  Serial.println("Current not Flowing");
  delay(5000);
}
