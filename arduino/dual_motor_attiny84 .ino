







int led_status;

# define x_step_pin 3//5//1
# define x_dir_pin 2//3
# define y_step_pin 1//5//1

# define xy_enable 0//4//2
int ledpin = 4;//10;
bool ledState = false;
int blinkDelay = 1000;
unsigned long previousMillisMotor = 0;
int moveCount = 0;
int countDelay = 0;
int buttonState = 0;
int buttonState_2 = 0;
const int buttonPin = 7;
const int buttonPin2 = 8;
unsigned long MoveDelay = 60000;

unsigned long previousMillis = 0;
boolean x_homestate = false;
boolean y_homestate = false;
// steps per mm for motor = 18 degrees/360 * 16 micrstepping
// 360/18 * 16 = 320
// gear ratio 1:100
// final steps per trun = 320 * 100 = 32000
// gear ratio in clock= 12:30 = 1:2.5
// one ful turn = 32000 * 2.5 = 80000
// number of digit stops = 10
// step per digit = 8000
int gear_ratio = 99; // error in tooth count
long one_turn = 320 * gear_ratio * 2.5; //79200
int one_digit = one_turn / 10;
int set_count = 0;
long one_turn_y = 320 * gear_ratio * 2; //63360
int one_digit_y = 5280;//one_turn / 12;the cam has 12 parts
int set_count_y = 0;


# define x_stop 9
# define y_stop 10
int home_x_positon = 0;
int home_y_positon = 0;

void setup()
{
  pinMode(buttonPin, INPUT);

  pinMode(ledpin, OUTPUT);

 pinMode(y_step_pin, OUTPUT);
  pinMode(x_step_pin, OUTPUT);
  pinMode(x_dir_pin, OUTPUT);
 

  pinMode(xy_enable, OUTPUT);
  
  //digitalWrite(x_dir_pin, LOW);
enable_motor();

 home_x();
 home_y();

  
}

void loop() {
time_step();
time_step_y();
 //move_motor_one_circle();
  //delay(2000);
// move_motor_one_circle_y();
  
}






void time_step() {

  buttonState = digitalRead(buttonPin);
  blinkk();
  if (buttonState == HIGH) {
    enable_motor();
    move_motor();
    digitalWrite(ledpin, HIGH);
  }
  else {

    unsigned long currentMillisMotor = millis();

    if ((unsigned long)(currentMillisMotor - previousMillisMotor) >= MoveDelay) {
      previousMillisMotor = currentMillisMotor;
      enable_motor();
      set_count = set_count+1;
      move_motor();

    }
    motoroff();
    
  }


  motoroff();

}


void time_step_y() {

  buttonState_2 = digitalRead(buttonPin2);
  blinkk();
  if (buttonState_2 == HIGH) {
    enable_motor();
    move_motor_y();
    digitalWrite(ledpin, HIGH);
  }
  else {

    unsigned long currentMillisMotor = millis();

    if ((unsigned long)(currentMillisMotor - previousMillisMotor) >= MoveDelay) {
      previousMillisMotor = currentMillisMotor;
      enable_motor();
      set_count_y = set_count_y+1;
      move_motor_y();

    }
    motoroff();
    
  }


  motoroff();

}


void motoroff() {
  digitalWrite(xy_enable, HIGH);

}
void enable_motor() {
  digitalWrite(xy_enable, LOW);
}




void move_motor() {
  digitalWrite(x_dir_pin, HIGH);
  for (int i = 0; i < one_digit; ++i) {
    //digitalWrite(8, LOW);
    digitalWrite(x_step_pin, LOW);
 

    delayMicroseconds(55);

    digitalWrite(x_step_pin, HIGH);


  
    delayMicroseconds(55);
  }

}


void move_motor_y() {
  digitalWrite(x_dir_pin, HIGH);
  for (int i = 0; i < one_digit_y; ++i) {
    digitalWrite(0, LOW);
    digitalWrite(y_step_pin, LOW);
 

    delayMicroseconds(55);

    digitalWrite(y_step_pin, HIGH);


  
    delayMicroseconds(55);
  }

}





void move_motor_one_circle() {
  digitalWrite(x_dir_pin, HIGH);
  for (long   i = 0; i < one_turn; ++i) {
    digitalWrite(0, LOW);
    digitalWrite(x_step_pin, LOW);
  

    delayMicroseconds(55);

    digitalWrite(x_step_pin, HIGH);


  
    delayMicroseconds(55);
  }
  delay(2000);
}

void move_motor_one_circle_y() {
  digitalWrite(x_dir_pin, HIGH);
  for (long   i = 0; i < one_turn_y; ++i) {
    digitalWrite(0, LOW);
    digitalWrite(y_step_pin, LOW);
  

    delayMicroseconds(55);

    digitalWrite(y_step_pin, HIGH);


  
    delayMicroseconds(55);
  }
  delay(2000);
}

void home_x() {

  x_homestate = false;

  int x_home = digitalRead(x_stop);
  digitalWrite(x_dir_pin, LOW);



  while (x_home == 1 ) {
    int x_home = digitalRead(x_stop);

    if (x_homestate == true) {
      //motor_disable();
      break;
    }
    if (x_home == 0) {

      move_back();
      x_homestate = true;
      break;
    }
    onestep();

  }
}

void home_y() {

  y_homestate = false;

  int y_home = digitalRead(y_stop);
  digitalWrite(x_dir_pin, LOW);



  while (y_home == 1 ) {
    int y_home = digitalRead(y_stop);

    if (y_homestate == true) {
      //motor_disable();
      break;
    }
    if (y_home == 0) {

      move_back_y();
      y_homestate = true;
      break;
    }
    onestep_y();

  }
}

void onestep_y() {


  digitalWrite(y_step_pin, HIGH);
  digitalWrite(y_step_pin, LOW);


  delayMicroseconds(195);
}


void onestep() {


  digitalWrite(x_step_pin, HIGH);
  digitalWrite(x_step_pin, LOW);


  delayMicroseconds(195);
}

void move_back() {
  digitalWrite(x_dir_pin, HIGH);
  int back = 1500;
  for (int f = 0; f < back; ++f) {
    onestep();
  }
}

void move_back_y() {
  digitalWrite(x_dir_pin, HIGH);
  int back = 1500;
  for (int f = 0; f < back; ++f) {
    onestep_y();
  }
}

void blinkk() {

  unsigned long currentMillis = millis();
  //motoroff();
  if ((unsigned long)(currentMillis - previousMillis) >= blinkDelay) {

    ledState = !ledState;
    digitalWrite(ledpin, ledState);

    previousMillis = currentMillis;
  }

}

void motor_on(){
digitalWrite(xy_enable, LOW);
  
}

void motor_off(){

  
}
