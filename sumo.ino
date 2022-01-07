#define trig1 23         //RIGHT       
#define echo1 22

#define trig2 25       // Back
#define echo2 24

#define trig3 27      // left
#define echo3 26

#define trig4 29     // forward
#define echo4 28

#define trig5 31    // forwardpro
#define echo5 30

//=========================motor=======================
#define left1 8
#define right1 7    // right motors
#define speed1 5

#define left2 9
#define right2 4   // left motors
#define speed2 6
//========================interrupts===================
#define interrupt1 18
#define interrupt2 19
#define interrupt3 20
#define interrupt4 21
int dis_F,dis_Fpro, dis_B, dis_L, dis_R, Time, dis=0;
bool flag1=true,flag2Back=LOW,flag2forward=LOW;


void setup() {
  delay(3000);
 // Serial.begin(9600);
  pinMode(trig1 , OUTPUT);
  pinMode(trig2 , OUTPUT);
  pinMode(trig3 , OUTPUT);
  pinMode(trig4 , OUTPUT);
  pinMode(trig5 , OUTPUT);
  
  pinMode(echo1 , INPUT);
  pinMode(echo2 , INPUT);
  pinMode(echo3 , INPUT);
  pinMode(echo4 , INPUT);
  pinMode(echo5 , INPUT);

  pinMode(interrupt1 , INPUT_PULLUP);
  pinMode(interrupt2 , INPUT_PULLUP);
  pinMode(interrupt3 , INPUT_PULLUP);
  pinMode(interrupt4 , INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interrupt1), IR1, FALLING);
  attachInterrupt(digitalPinToInterrupt(interrupt2), IR2, FALLING);
  attachInterrupt(digitalPinToInterrupt(interrupt3), IR3, FALLING);
  attachInterrupt(digitalPinToInterrupt(interrupt4), IR4, FALLING);
  

  pinMode(left1,OUTPUT);
  pinMode(right1,OUTPUT);
  pinMode(left2,OUTPUT);
  pinMode(right2,OUTPUT);
  
  digitalWrite(left1,LOW);
  digitalWrite(right1,LOW);
  
  digitalWrite(left2,LOW);
  digitalWrite(right2,LOW);
 
}


void loop() {
  dis_F=ultra(trig4,echo4);
  interrupt_action ();
  dis_Fpro=ultra(trig5,echo5);   // altra sonic distance
  interrupt_action ();
  dis_B=ultra(trig2,echo2);
  interrupt_action ();
  dis_R=ultra(trig1,echo1);
  interrupt_action ();
  dis_L=ultra(trig3,echo3);   // altra sonic distance
  interrupt_action ();
 // Serial.println((String)dis_F + " "+(String)dis_B +" "+(String)dis_L+" "+(String)dis_R+" "+ (String)dis_Fpro);
 // ====================================== control unit ==========================
 
 if((dis_F>0&&dis_F<=50)||(dis_Fpro>0&&dis_Fpro<=50)){
  delay(2);
  forward(250);
  delay(2);
 }
 
 else if (dis_B>0&&dis_B<=40){
  delay(2);flag1=HIGH;
  
  while(flag1==HIGH)
  {
  left(210);
  delay(1);
  if((ultra(trig4,echo4)<=40)||(ultra(trig5,echo5)<=40)){delay(300); flag1=LOW;}
  interrupt_action ();
  }
  
 }
 
  else if (dis_R>0&&dis_R<=40)
  {
  delay(2);flag1=HIGH;
  
  while(flag1){
  right(210);
  delay(1);
  if((ultra(trig4,echo4)<=40)||(ultra(trig5,echo5)<=40)){delay(250);flag1=LOW;}
  interrupt_action ();
  }
  
 }

 else if (dis_L>0&&dis_L<=40){
  delay(2);flag1=HIGH;
  
  while(flag1){
  left(210);
  delay(1);
  if((ultra(trig4,echo4)<=40)||(ultra(trig5,echo5)<=40)){delay(250);flag1=LOW;}
  interrupt_action ();
  }
  
 }

 else if (dis_L>40&&dis_R>40&&dis_F>40&&dis_B>40&&dis_Fpro>40)
 {
  delay(2);
  forward(70);
  delay(2);
 }
 
 else
 {
  delay(2);
  forward(150);
  delay(2);
 }


 
}
//==============================interupt action===========================
void interrupt_action ()
{
   if (flag2Back==HIGH){
      forward(250);
      delay(1500);
      right(250);
      delay(1500);
      stoop();
      flag2Back=LOW;
 }
 if (flag2forward==HIGH){
      Back(250);
      delay(1500);
      right(250);
      delay(1500);
      stoop();
      flag2forward=LOW;
 }
}


// ============================= distanc ===================================
int ultra(int trig,int echo){
  delay(1);
   digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  Time = pulseIn(echo,HIGH,40000);
  dis=Time/57;
delay(10);
if (dis>200){
  dis=200;
}
if(dis <0){
  dis=0;
}
  return dis;
}
// ===================================interupt ================================
void IR1(){
  flag2Back=HIGH;
}
void IR2(){
  flag2Back=HIGH;
}
void IR3(){
  flag2forward=HIGH;
 
}
void IR4(){
  flag2forward=HIGH;
}

//===========================motor control functions ===========================
void forward(int Speed){
  digitalWrite(left1,LOW);
  digitalWrite(right1,HIGH);
  
  digitalWrite(left2,LOW);
  digitalWrite(right2,HIGH);
  
  analogWrite(speed1,Speed);
  analogWrite(speed2,Speed);
}

void Back(int Speed){
  digitalWrite(left1,HIGH);
  digitalWrite(right1,LOW);
  
  digitalWrite(left2,HIGH);
  digitalWrite(right2,LOW);
  
  analogWrite(speed1,Speed);
  analogWrite(speed2,Speed);
}

void left(int Speed){
  digitalWrite(left1,HIGH);
  digitalWrite(right1,LOW);
  
  digitalWrite(left2,LOW);
  digitalWrite(right2,HIGH);
  
  analogWrite(speed1,Speed);
  analogWrite(speed2,Speed);
}

void right(int Speed){
  digitalWrite(left1,LOW);
  digitalWrite(right1,HIGH);
  
  digitalWrite(left2,HIGH);
  digitalWrite(right2,LOW);
  
  analogWrite(speed1,Speed);
  analogWrite(speed2,Speed);
}

void stoop(){
   digitalWrite(left1,LOW);
  digitalWrite(right1,LOW);
  
  digitalWrite(left2,LOW);
  digitalWrite(right2,LOW);
  
  analogWrite(speed1,0);
  analogWrite(speed2,0);
}
