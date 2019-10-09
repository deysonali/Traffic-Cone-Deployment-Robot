#include<stdio.h>
void line_follow(void);

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

const byte rx = 1;
const byte tx = 0;


int vSpeed = 110;        // MAX 255
int turn_speed = 230;    // MAX 255 
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
int dep_left_1 = 3 ;
int dep_right_0 = 10;
int dep_right_1 = 11;
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
  pinMode(dep_left_0,OUTPUT);
  pinMode(dep_left_1,OUTPUT);
  pinMode(right_0,OUTPUT);
  pinMode(right_1,OUTPUT);
  
  pinMode(IR_left,INPUT);
  pinMode(IR_right,INPUT);

    delay(50);
    
    digitalWrite(dep_left_0, LOW);
    digitalWrite(dep_left_1, HIGH);


    delay(50);

    digitalWrite(dep_left_0, HIGH);
    digitalWrite(dep_left_1, LOW);
  
//  if(read_num == 0){ // when the * button is pressed
    Serial.begin(9600); // this is now Serial. replace.
//  }
}

void loop() 
{
   // digitalWrite (left_0,LOW);                       
   // digitalWrite (right_0,LOW);
   // digitalWrite (left_1,LOW);                       
   // digitalWrite (right_1,LOW); 

    digitalWrite(dep_left_0, LOW);
    digitalWrite(dep_left_1, LOW);   

    delay(25);
}
