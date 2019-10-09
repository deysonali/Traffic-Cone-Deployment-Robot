#include<stdio.h>
#include<SoftwareSerial.h>
void line_follow(void);
float distance(void);
int ll_add_to_head(struct Node **head, int data);
int ll_add_to_tail(struct Node **head, int data);
int ll_ret_head(struct Node *head);
void turn_back(void);

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

const float circumference = 22; //centimeters


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

void loop() 
{
  if (mySerial.available() > 0) {  // this reads every time u get a value from the PIC
    // read the incoming byte:
    read_byte = mySerial.read();
    read_num = read_byte - 48;
    //// say what you got to test:
    mySerial.print("received:");
    mySerial.println(read_byte, DEC);
    //Serial.write(45);

    
  }
  
  line_follow();
  
  dist = distance(dist);
  
  if(dist >= 400.0){
    turn_back();
  }
  else{
    state = check_path();
    if(state != 0){
      deploy_cone(state);
  }
 }   
}

/*
int ll_add_to_head(struct Node **head, int data) {
   struct Node *old_head;
   if (head == NULL) { // if the linked list is empty (no cracks/holes detected)
      return -1;
   }
  old_head = *head;

  *head = (struct Node *)malloc(sizeof(struct Node));
  (*head) -> data = data;
  (*head) -> next = old_head;
  return 0;
}

int ll_add_to_tail(struct Node **head, int data) {
   if (head == NULL) {
      return -1;
   }
   if (*head == NULL) {
      *head =  (struct Node *)malloc(sizeof(struct Node));
      (*head) -> data = data;
      (*head) -> next = NULL;
      return 0;
   } else { /* recursively call ll_add_to_tail until we get to the tail
          which is the point where the pointer is NULL */ /*
      return ll_add_to_tail(&((*head)->next), data);
   }
}

int ll_ret_head(struct Node *head){
  int head_data = -1.0;
  if (head == NULL) {
    return head_data;
  }
  else {
    head_data = (Node* head) -> data;
    return head_data;
  }
}

*/

void line_follow(void){
  
  left_sensor_state = analogRead(IR_left);
  right_sensor_state = analogRead(IR_right);
  
  if(right_sensor_state > 450 && left_sensor_state < 450)
  {
    Serial.println("turning right");
  
    digitalWrite (left_0,LOW);                       
    digitalWrite (right_0,LOW);
  
    analogWrite (left_1, turn_speed);
    analogWrite (right_1, v_speed);
    
    }
  if(right_sensor_state < 450 && left_sensor_state > 450)
  {
    Serial.println("turning left");
    
    digitalWrite (left_0,LOW);                       
    digitalWrite (right_0,LOW);
  
    analogWrite (left_1, v_speed);
    analogWrite (right_1, turn_speed); 

    delay(turn_delay);
    }
  
  if(right_sensor_state > 450 && left_sensor_state > 450)
  {
    Serial.println("going forward");
 
    digitalWrite (left_0,LOW);                       
    digitalWrite (right_0,LOW);
    
    analogWrite (left_1, 255);
    analogWrite (right_1, 255);
  
    delay(turn_delay);
    
    }
}

/*int check_path(){ // input? sensor states, distance measurement, prev distances for stuff // output -1 for nothing. 0 for hole, 1 for left, 2 for left + mid, 3 for mid + right, 4 for right only.
   l_state = analogRead(IR_dep_left);
   r_state = analogRead(IR_dep_right);
   m_state = analogRead(IR_dep_mid);

   if (l_state > 450  && m_state > 450 && r_state >450) {
    return -1;
   }
   else if (l_state > 450 && m_state > 450){
    return 2;
   }
   else if(m_state > 450 && r_state > 450){
    return 3;
   } 
   else if(l_state > 450){
    return 1;
   }
   else if (r_state > 450){
    return 4;
   }
   else if (m_state > 450) {
    return 0;
   }
   
   else{
    return -100;
   }
   

} */

int check_path(void){
  
  int rval = 0;
  
  // left = 1
  // left + mid = 2
  // mid = 3 (hole)
  // mid + right = 4
  // right = 5
  
  // none/none of the above = 0

   l_state = analogRead(IR_dep_left);
   r_state = analogRead(IR_dep_right);
   m_state = analogRead(IR_dep_mid);

   if (l_state < 450 && m_state < 450 && r_state < 450) { // nothing detected // try 500, distance goes high on black  // difference function tests if the prev crack/hole is an issue. 0 for hole 1 for crack
    rval = 0;
   }
   else if (l_state > 450 && m_state > 450){ //left and mid
    if(difference_problem(dist,1)){
      rval = 0;
    }
    else{
    rval = 2;
   }
   }
   else if(m_state > 450 && r_state > 450){ //middle + right
    if(difference_problem(dist,1)){
      rval = 0;
    }
    else{
    rval = 4;
    }
   } 
   else if(l_state > 450){ // left only
     if(difference_problem(dist,1)){
      rval = 0;
    }
    else {
    rval = 1;
    }
   }
   else if (r_state > 450){ //right only
    if(difference_problem(dist,1)){
      rval = 0;
    }
    else{
    rval = 5;
    }
   }
   
   else if (m_state > 450) { //hole in the middle
    if(difference_problem(dist,0)){
      rval = 0;
    }
    else{
    rval = 3;
    }
   }
   
   else{ //start or end line
    rval = 0;
   }
  return rval;
}


void deploy_cone(int roadstate){
  cone_count = cone_count + 1;

  // left = 1
  // left + mid = 2
  // mid = 3 (hole)
  // mid + right = 4
  // right = 5
  
  // none/none of the above = 0

  //stop the bot

  // deploy based on the motor activated
  switch(roadstate){
    case 1:
      dep_left();
      hole_count = hole_count + 1;
      return;
    case 2:
      dep_left();
      dep_mid();
      crack_count = crack_count + 1;
      return;
    case 3:
      dep_mid();
      hole_count = hole_count + 1;
      crack_count = crack_count + 1;
      return;
    case 4:
      dep_mid();
      dep_right();
      crack_count = crack_count + 1;
      return;
    case 5:
      dep_right();
      hole_count = hole_count + 1;
      return;
    case 0:
      cone_count = cone_count -1;
      return;      
    default:
      cone_count = cone_count -1;
      return;
  }
}

void dep_right(void){
    digitalWrite (left_0,LOW);                       
    digitalWrite (right_0,LOW);
    digitalWrite (left_1,LOW);                       
    digitalWrite (right_1,LOW); 

    delay(100);

    digitalWrite(dep_right_0, LOW);
    digitalWrite(dep_right_1, HIGH);

    delay(100);

    digitalWrite(dep_right_0, HIGH);
    digitalWrite(dep_right_1, LOW);

    delay(100);

    digitalWrite(dep_right_0, LOW);
    digitalWrite(dep_right_1, LOW);   

    delay(100);
        
}

void dep_mid(void){
    digitalWrite (left_0,LOW);                       
    digitalWrite (right_0,LOW);
    digitalWrite (left_1,LOW);                       
    digitalWrite (right_1,LOW); 

    delay(100);

    digitalWrite(dep_mid_0, LOW);
    digitalWrite(dep_mid_1, HIGH);

    delay(100);

    digitalWrite(dep_mid_0, HIGH);
    digitalWrite(dep_mid_1, LOW);

    delay(100);

    digitalWrite(dep_mid_0, LOW);
    digitalWrite(dep_mid_1, LOW);   

    delay(100);
}

void dep_left(void){
    digitalWrite (left_0,LOW);                       
    digitalWrite (right_0,LOW);
    digitalWrite (left_1,LOW);                       
    digitalWrite (right_1,LOW); 

    delay(100);
    digitalWrite(dep_left_0, LOW);
    digitalWrite(dep_left_1, HIGH);

    delay(100);

    digitalWrite(dep_left_0, HIGH);
    digitalWrite(dep_left_1, LOW);

    delay(100);

    digitalWrite(dep_left_0, LOW);
    digitalWrite(dep_left_1, LOW);   

    delay(100);
}

float distance(float current_distance){ //NEED SHAFT ENC TO WORK!!! k. returns the distance travelled in cm as a float. 
  tick_left = digitalRead(enc_left);
  tick_right = digitalRead(enc_right);
  
  if(tick_left == 1){
      left_dist = 0.05*circumference;
    }
  
  if(tick_right == 1){
      right_dist = 0.05*circumference;
    }
  current = current + (left_dist + right_dist)*0.5; //get an estimate of the distance travelled.  
  return current;
 }
}

void turn_back(void){
  analogWrite(left_1, turn_speed);
  analogWrite(right_1, v_speed);
  delay(3000);
  while(return_dist <= 410.00){
    return_dist = distance(return_dist);
    analogWrite(left_1, v_speed);
    analogWrite(right_1, v_speed);
    delay(10);
  }
  analogWrite(left_1, turn_speed);
  analogWrite(right_1, v_speed);
  delay(3000);
  
  digitalWrite(left_0, LOW);
  digitalWrite(left_0, LOW);
  digitalWrite(left_1, LOW);
  digitalWrite(right_1, LOW);}

int difference_problem(float curr_dist, int hole_or_crack){  // 0 is hole and 1 is a crack curr_dist
}
//}

// mySerial.write can be used to send values to the PIC. (maybe for display states)
// UART.c change the function names for functions/ also variable names// 
// Arduino has everything, library has everything for it.
