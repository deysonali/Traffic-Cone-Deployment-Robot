  const int enc_left = 12;
  const int enc_right = A1;

int x = 0;
float y = 0.0;

void setup() {
  // put your setup code here, to run once:
  pinMode(enc_left, INPUT);
  pinMode(enc_right,INPUT);
  
  Serial.begin(9600); // this is now Serial. replace.
  

}

void loop() {
  // put your main code here, to run repeatedly:
  x = digitalRead(enc_left);
  Serial.println(x);
 // y = analogRead(enc_right);
 // Serial.println(y); 
  delay(1000);  

}
