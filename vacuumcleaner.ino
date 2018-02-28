const int pin1RightMotor=3,pin2RightMotor = 4,pin1LeftMotor=7,pin2LeftMotor=6,
echopin=12,trigpin=13,turnRightTimeout=80;
int distance,countDownWhileMovingToRight=-1;
long duration;

void runRightMotorForward(){
  digitalWrite(pin1RightMotor,HIGH);
  digitalWrite(pin2RightMotor,LOW);
  Serial.print("rf");
  Serial.print("\n");
}

void runLeftMotorForward(){
  digitalWrite(pin1LeftMotor,HIGH);
  digitalWrite(pin2LeftMotor,LOW);
  Serial.print("lf");
  Serial.print("\n");
}

void runRightMotorBackward(){
  digitalWrite(pin2RightMotor,HIGH);
  digitalWrite(pin1RightMotor,LOW);
  Serial.print("rb");
  Serial.print("\n");
}


void processRightSide(){
  if(countDownWhileMovingToRight <= 0)
    return;
  countDownWhileMovingToRight--;
  if(countDownWhileMovingToRight <= 0)
    runRightMotorForward();
}

void verify(){
  if(countDownWhileMovingToRight>0)
    runRightMotorBackward();
   else {runRightMotorForward();
         digitalWrite(trigpin,LOW);
         delayMicroseconds(2);
         digitalWrite(trigpin, HIGH);
         delayMicroseconds(10);
         digitalWrite(trigpin, LOW);
         duration = pulseIn(echopin, HIGH);
         distance= duration*0.034/2;
         Serial.print(distance);
         Serial.print("-distance\n");
         if(distance<=14)
             countDownWhileMovingToRight = turnRightTimeout;
        }
}


void setup() {
  pinMode(pin1RightMotor,OUTPUT);        
  pinMode(pin2RightMotor,OUTPUT);        
  pinMode(pin1LeftMotor,OUTPUT);
  pinMode(pin2LeftMotor,OUTPUT);
  Serial.begin(9600);
  pinMode(echopin, INPUT);
  pinMode(trigpin, OUTPUT);
}

void loop() {
 runLeftMotorForward();
 verify();
 processRightSide();
}
                   

