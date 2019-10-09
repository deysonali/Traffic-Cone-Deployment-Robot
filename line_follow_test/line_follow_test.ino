#include<stdio.h>

int left_sensor_state =0;
int right_sensor_state = 0;
int l_state = 0;
int r_state = 0;
int m_state =0;
int read_num = 0;
int read_byte = 0;
int temp_count = 0;
int state = -100;
// main movement motors
// 0 refers to GND and 1 refers to Power connected side.
float b = 0.0;
const byte rx = 1;
const byte tx = 0;


int vSpeed = 155;        // MAX 255 //was 110 earlier, trying to reduce the amount of shaking. 160 worked well
int turn_speed = 210;    // MAX 255 
int turn_delay = 10;
float prev_crack = 0;
float prev_hole = 0;
float distance = 0;

int road_status = -1;


int left_0 = 4;
int left_1 = 5; //enable
int right_0 = 7;
int right_1 = 6; //enable



// deployment motors

int dep_left_0 = 2;
int dep_left_1 = 3;
int dep_right_0 = 10;
int dep_right_1 = A5;
int dep_mid_0 = 8;
int dep_mid_1 = 9;

// IR sensors;





const int IR_left = A0;
const int IR_right = A4;









const int IR_dep_left = A1;
const int IR_dep_right = A3;
const int IR_dep_mid = A2;

const int enc_left = 12;
const int enc_right = 13;

// other constants

int IR_left_in = 0;
int IR_right_in = 0;
int IR_dep_left_in = 0;
int IR_dep_right_in = 0;
int IR_dep_mid_in = 0;

// linked list struct for storing the distances

//Node *crack_dist, *hole_dist;

//crack_dist = (Node *)malloc(sizeof(Node)); 

//hole_dist =  (Node *)malloc(sizeof(Node));

void setup()
{
  pinMode(left_0,OUTPUT);
  pinMode(left_1,OUTPUT);
  pinMode(right_0,OUTPUT);
  pinMode(right_1,OUTPUT);

  pinMode (dep_left_0,OUTPUT);                       
  pinMode (dep_left_1,OUTPUT);
  pinMode (dep_right_0,OUTPUT);                       
  pinMode (dep_right_1,OUTPUT);
  pinMode(dep_mid_0,OUTPUT);                       
  pinMode(dep_mid_1,OUTPUT);
  pinMode(IR_left,INPUT);
  pinMode(IR_right,INPUT);

//  if(read_num == 0){ // when the * button is pressed
    Serial.begin(9600); // this is now Serial. replace.
//  }
}

void loop() 
{
//  n++;
  digitalWrite (dep_left_0,LOW);                       
  digitalWrite (dep_left_1,LOW);
  digitalWrite (dep_right_0,LOW);                       
  digitalWrite (dep_right_1,LOW);
  digitalWrite(dep_mid_0,LOW);                       
  digitalWrite (dep_mid_1,LOW);
  digitalWrite(left_0,LOW);                       
  digitalWrite (right_0,LOW);
  digitalWrite(left_1,LOW);                       
  digitalWrite (right_1,LOW);

  line_follow();

}


void line_follow(void){
  left_sensor_state = analogRead(IR_left);
  right_sensor_state = analogRead(IR_right);
  b = analogRead(IR_dep_right);
  Serial.println(b);
  //Serial.println(right_sensor_state);

   if(right_sensor_state < 440 && left_sensor_state < 440)
  {
    Serial.println("going forward");
 
    digitalWrite (left_0,LOW);                       
    digitalWrite (right_0,LOW);
    
    
    analogWrite (left_1, 255);
    analogWrite (right_1, 255);
  
    delay(turn_delay);
    
    }
    
  else if(right_sensor_state > 440 && left_sensor_state < 440)
  {
    Serial.println("turning right");
  
    digitalWrite (left_0,LOW);                       
    digitalWrite (right_0,LOW);
  
    analogWrite (left_1, turn_speed);
    analogWrite (right_1, vSpeed);

    delay(turn_delay);
    
    }
  else if(right_sensor_state < 440 && left_sensor_state > 440)
  {
    Serial.println("turning left");
    
    digitalWrite (left_0,LOW);                       
    digitalWrite (right_0,LOW);
  
    analogWrite (left_1, vSpeed);
    analogWrite (right_1, turn_speed); 

    delay(turn_delay);
    }
}
