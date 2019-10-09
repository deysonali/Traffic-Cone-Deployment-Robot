/*

*/

  
  int move_left_1 = 7 ;
  int move_left_2 = 8 ;
  int move_right_1 = 9;
  int move_right_2 = 10;
  int move_mid_1 = 11;
  int move_mid_2 = 12;

 // int A = 1; // hole only
 // int B = 0; // left crack
 // int C = 0; // right crack
  volatile int A = 4;
  volatile int B = 5;
  volatile int C = 6;

void setup() {
    Serial.begin(9600);
    pinMode(move_left_1,OUTPUT);
    pinMode(move_left_2,OUTPUT);    
    pinMode(move_right_1,OUTPUT);
    pinMode(move_right_2,OUTPUT);
    pinMode(move_mid_1,OUTPUT);
    pinMode(move_mid_2,OUTPUT);
    pinMode(A,INPUT);
    pinMode(B,INPUT);
    pinMode(C,INPUT);
  
}

void loop() {
  
  if(A == 1){
    digitalWrite(move_left_1,LOW);
    digitalWrite(move_left_2,LOW);
    digitalWrite(move_right_1,LOW);
    digitalWrite(move_right_2,LOW); 
    digitalWrite(move_mid_1,HIGH);
    digitalWrite(move_mid_2,LOW);
    
    delay(500);
    
    digitalWrite(move_left_1,LOW);
    digitalWrite(move_left_2,LOW);
    digitalWrite(move_right_1,LOW);
    digitalWrite(move_right_2,LOW); 
    digitalWrite(move_mid_1,LOW);
    digitalWrite(move_mid_2,HIGH);
    
    delay(500);
    
    digitalWrite(move_left_1,LOW);
    digitalWrite(move_left_2,LOW);
    digitalWrite(move_right_1,LOW);
    digitalWrite(move_right_2,LOW); 
    digitalWrite(move_mid_1,LOW);
    digitalWrite(move_mid_2,LOW);
    
    delay(5000);   
  }
  
  else if (B == 1){
    digitalWrite(move_left_1,HIGH);
    digitalWrite(move_left_2,LOW);
    digitalWrite(move_right_1,LOW);
    digitalWrite(move_right_2,LOW); 
    digitalWrite(move_mid_1,HIGH);
    digitalWrite(move_mid_2,LOW);    
    
    delay(500);
    
    digitalWrite(move_left_1,LOW);
    digitalWrite(move_left_2,HIGH);
    digitalWrite(move_right_1,LOW);
    digitalWrite(move_right_2,LOW); 
    digitalWrite(move_mid_1,LOW);
    digitalWrite(move_mid_2,HIGH);
    
    delay(500);
    
    digitalWrite(move_left_1,LOW);
    digitalWrite(move_left_2,LOW);
    digitalWrite(move_right_1,LOW);
    digitalWrite(move_right_2,LOW); 
    digitalWrite(move_mid_1,LOW);
    digitalWrite(move_mid_2,LOW);
    
    delay(5000);
  }
  
  else if(C == 1){
    
    digitalWrite(move_left_1,LOW);
    digitalWrite(move_left_2,LOW);
    digitalWrite(move_right_1,HIGH);
    digitalWrite(move_right_2,LOW); 
    digitalWrite(move_mid_1,HIGH);
    digitalWrite(move_mid_2,LOW);
    
    delay(500);
    
    digitalWrite(move_left_1,LOW);
    digitalWrite(move_left_2,LOW);
    digitalWrite(move_right_1,LOW);
    digitalWrite(move_right_2,HIGH); 
    digitalWrite(move_mid_1,LOW);
    digitalWrite(move_mid_2,HIGH);
    
    delay(500);
    
    digitalWrite(move_left_1,LOW);
    digitalWrite(move_left_2,LOW);
    digitalWrite(move_right_1,LOW);
    digitalWrite(move_right_2,LOW); 
    digitalWrite(move_mid_1,LOW);
    digitalWrite(move_mid_2,LOW);
    
    delay(5000);

    }
  
    digitalWrite(move_left_1,LOW);
    digitalWrite(move_left_2,LOW);
    digitalWrite(move_right_1,LOW);
    digitalWrite(move_right_2,LOW); 
    digitalWrite(move_mid_1,LOW);
    digitalWrite(move_mid_2,LOW); 
    
    delay(2000);
  
  return;
}
