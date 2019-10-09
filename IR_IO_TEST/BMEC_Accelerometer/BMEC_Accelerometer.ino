
int LED1 = 9;
int LED2 = 10;


void setup(){
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  digitalWrite(LED1, HIGH);
  delay(10000);
  digitalWrite(LED1, LOW);
  delay(10000);
  digitalWrite(LED2, HIGH);
  delay(10000);
  digitalWrite(LED2, LOW);
  delay(10000);

}
