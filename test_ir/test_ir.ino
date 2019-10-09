
const int IR_left = A1;
const int IR_right = A4;
float b = 0.0;

void setup() {
  // put your setup code here, to run once:
  pinMode(IR_left,INPUT);
  pinMode(IR_right,INPUT);
  Serial.begin(9600); // this is now Serial. replace.


}

void loop() {
  // put your main code here, to run repeatedly:
 b = analogRead(IR_left);
  Serial.println(b);
  delay(1000);
  
}
