#include<stdio.h>
#include<SoftwareSerial.h>
void line_follow(void);
float distance(void);
int ll_add_to_head(struct Node **head, int data);
int ll_add_to_tail(struct Node **head, int data);
int ll_ret_head(struct Node *head);
void turn_back(void);

int current = 0;
int tick_left = 0;
int tick_right = 0;
int left_sensor_state = 0;
int right_sensor_state = 0;
int l_state = 0;
int r_state = 0;
int m_state =0;
int read_num = 0;
int read_byte = 0;
int state = -100;

int cone_count = 0;
int crack_count = 0;
int hole_count = 0;


float prev_hole_dist = 0.0;
float prev_crack_dist = 0.0;

const float circumference = 22.0; //centimeters


float left_dist = 0.0; // left encoder
float right_dist = 0.0; // right encoder

float dist = 0.0; //average the two I guess
float return_dist = 0.0;
// main movement motors
// 0 refers to GND and 1 refers to Power connected side.

const byte rx = 1;
const byte tx = 0;

SoftwareSerial mySerial = SoftwareSerial(rx, tx);

int v_speed = 150;        // MAX 255
int turn_speed = 230;    // MAX 255 
int turn_delay = 10;


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

// IR sensors

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
/*
struct Node  
{ 
  int data; 
  struct Node *next; 
}; 
*/
typedef struct Node Node;

//Node *crack_dist, *hole_dist;

//crack_dist = (Node *)malloc(sizeof(Node)); 

//hole_dist =  (Node *)malloc(sizeof(Node));

void setup()
{
  pinMode(left_0,OUTPUT);
  pinMode(left_1,OUTPUT);
  pinMode(right_0,OUTPUT);
  pinMode(right_1,OUTPUT);
  pinMode(dep_left_0,OUTPUT);
  pinMode(dep_left_1,OUTPUT);
  pinMode(dep_right_0,OUTPUT);
  pinMode(dep_right_1,OUTPUT);
  pinMode(dep_mid_0,OUTPUT);
  pinMode(dep_mid_1,OUTPUT);
  pinMode(IR_left,INPUT);
  pinMode(IR_right,INPUT);
  pinMode(IR_dep_left,INPUT);
  pinMode(IR_dep_right,INPUT);
  pinMode(IR_dep_mid,INPUT);
  pinMode(enc_left,INPUT);
  pinMode(enc_right,INPUT);

    digitalWrite(left_0, LOW);
    digitalWrite(right_0, LOW);
    digitalWrite(right_1, LOW);
    digitalWrite(left_1, LOW);
  
  if (mySerial.available() > 0) {  // this reads every time u get a value from the PIC
  
  // read the incoming byte:
  read_byte = mySerial.read();
  read_num = read_byte - 48;
  //// say what you got to test:
  
  mySerial.print("received:");
  mySerial.println(read_byte, DEC);
  //Serial.write(45);
}
 if(read_num == 0){ // when the * button is pressed
    mySerial.begin(9600); // this is now Serial. replace.
    }



}

void loop(){
 digitalWrite(dep_mid_0,LOW);
 digitalWrite(dep_mid_1,LOW);

 digitalWrite(dep_right_0, LOW);
 digitalWrite(dep_right_1, LOW);
 
 digitalWrite(dep_left_0, LOW);
 digitalWrite(dep_left_1, HIGH);   
 delay(50);
 
 digitalWrite(dep_left_0, LOW);
 digitalWrite(dep_left_1, LOW);
 
 delay(50);
 digitalWrite(dep_mid_0, HIGH);
 digitalWrite(dep_mid_1, LOW);   
 
 delay(50);
 digitalWrite(dep_left_0, LOW);
 digitalWrite(dep_left_1, LOW);
 delay(50);
}
