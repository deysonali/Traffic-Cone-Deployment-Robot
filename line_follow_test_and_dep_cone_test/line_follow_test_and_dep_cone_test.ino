#include<stdio.h>
#include<SoftwareSerial.h>

void line_follow(void);
int check_path(void);
void deploy_cone(int roadstate);

float track_distance(void);
void turn_back(void);
void dep_right(void);
void dep_left(void);
void dep_mid(void);

// line follow sensor states
int left_sensor_state = 0;
int right_sensor_state = 0;

// dep sensor states
int l_state = 0;
int r_state = 0;
int m_state =0;

int read_num = 0;
int read_byte = 0;
int temp_count = 0;
int state = -100;

float circumference = 40.8571428; //cm
// main movement motors
// 0 refers to GND and 1 refers to Power connected side.

const byte rx = 1;
const byte tx = 0;

SoftwareSerial mySerial = SoftwareSerial(rx, tx);



int road_state = -1;
int vSpeed = 150;        // MAX 255 //was 110 earlier, trying to reduce the amount of shaking. 160 worked well
int turn_speed = 200;    // MAX 255 
int turn_delay = 10;
float prev_crack = 0;
float prev_hole = 0;
float distance = 0;



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


// shaft encoders
const int enc_left = 12;
const int enc_right = 13;

// other constants - input from sensors

int IR_left_in = 0;
int IR_right_in = 0;
int IR_dep_left_in = 0;
int IR_dep_right_in = 0;
int IR_dep_mid_in = 0;

// linked list struct for storing the distances - ignore for the time being

//Node *crack_dist, *hole_dist;

//crack_dist = (Node *)malloc(sizeof(Node)); 

//hole_dist =  (Node *)malloc(sizeof(Node));

void setup()
{
  pinMode(left_0,OUTPUT);
  pinMode(left_1,OUTPUT);
  pinMode(right_0,OUTPUT);
  pinMode(right_1,OUTPUT);
  
  pinMode(IR_left,INPUT);
  pinMode(IR_right,INPUT);

  if (mySerial.available() > 0) {  // this reads every time u get a value from the PIC
  // read the incoming byte:
    read_byte = mySerial.read();
    read_num = read_byte - 48;
  //// say what you got to test:
    mySerial.print("received:");
    mySerial.println(read_byte, DEC);
    //Serial.write(45);
}
  if(read_num == 0){ // when the * button is pressed to start
    mySerial.begin(9600); // this is now Serial. replace.
  }
}


void loop() 
{
  if (mySerial.available() > 0) {  // this reads every time you get a value from the PIC
    // read the incoming byte:
    read_byte = mySerial.read();
    read_num = read_byte - 48;
    //// say what you got to test:
    mySerial.print("received:");
    mySerial.println(read_byte, DEC);
    //Serial.write(45);
  }
  //n++;

  // = track_distance();
  state = check_path();
  if(state != 0){
    deploy_cone(state);
  }
  line_follow();

}


void line_follow(void){
  
  left_sensor_state = analogRead(IR_left);
  right_sensor_state = analogRead(IR_right);
  
  if(right_sensor_state > 350 && left_sensor_state < 350)
  {
    mySerial.println("turning right");
  
    digitalWrite (left_0,LOW);                       
    digitalWrite (right_0,LOW);
  
    analogWrite (left_1, turn_speed);
    analogWrite (right_1, vSpeed);
    
    }
    
  if(right_sensor_state < 350 && left_sensor_state > 350)
  {
    mySerial.println("turning left");
    
    digitalWrite (left_0,LOW);                       
    digitalWrite (right_0,LOW);
  
    analogWrite (left_1, vSpeed);
    analogWrite (right_1, turn_speed); 

    delay(turn_delay);
    }
  
  if(right_sensor_state > 350 && left_sensor_state > 350)
  {
    mySerial.println("going forward");
 
    digitalWrite (left_0,LOW);                       
    digitalWrite (right_0,LOW);
    
    analogWrite (left_1, 255);
    analogWrite (right_1, 255);
  
    delay(turn_delay);
    
    }
}

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

   if (l_state > 350 && m_state > 350 && r_state > 350) { // nothing detected
    rval = 0;
   }
   else if (l_state < 350 && m_state < 350){ //left and mid
    rval = 2;
   }
   else if(m_state < 350 && r_state < 350){ //middle + right
    rval = 4;
   } 
   else if(l_state < 350){ // left only
    rval = 1;
   }
   else if (r_state < 350){ //right only
    rval = 5;
   }
   else if (m_state < 350) { //hole
    rval = 3;
   }
   else{ //start or end line
    rval = 0;
   }
  return rval;
}


void deploy_cone(int roadstate){

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
      return;
    case 2:
      dep_left();
      dep_mid();
      return;
    case 3:
      dep_mid();
      return;
    case 4:
      dep_mid();
      dep_right();
      return;
    case 5:
      dep_right();
      return;
    case 0:
      return;
    default:
      return;
  }
}

float track_distance(void){
}

float check_record(int current_dist){

  
  }
void turn_back(void){
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
