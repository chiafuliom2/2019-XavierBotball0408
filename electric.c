#include <kipr/botball.h>



int r_motor = 0;
int l_motor = 2;
int speed_avg = 50;
int b_left = 1;
int d_front = 3;
int b_left_sweet = 2000;
int f_speed = 40;
int l_speed = 20;
int d_front_sweet = 2100;
int arm_down = 450;
int arm = 0;
int arm_bpole = 1300;
int arm_high = 1650;


int main()
{
    initialize();
    exit_box();
    approach_line();
    approach_pole();
    mag1();
    back_up();
    return 0;
}
int initialize(){
    enable_servos();
    set_servo_position(arm, arm_down);
    msleep(1000);
    disable_servos();
    
}

int exit_box(){
    
    while(analog(b_left) < b_left_sweet){
        forward_med();
    }
    
    while(analog(b_left) > b_left_sweet){
        forward_med();
    }
    ao();
    turnLeft(700);
    forward(1500);
}

int approach_line(){
    
    while(analog(b_left) < b_left_sweet){
        forward_med();
    }
    ao();
    turnRight(400);
    ao();
    enable_servos();
    set_servo_position(arm, arm_bpole);
    msleep(500);
    disable_servos();
}

int approach_pole(){
    
    while(analog(d_front) < d_front_sweet){
        if(analog(b_left) > b_left_sweet){
            drift_right();
        }
        if(analog(b_left) < b_left_sweet){
            drift_left();
        }
    }
    ao();
}

int back_up (){
    pivot_left_s();
    msleep(800);
    
    int i = 0;
    int g = 50;
    enable_servos();
    
    while (i < 10){
        reverse(100);
        set_servo_position(arm, arm_high - g);
        msleep(100);
        g += 50;
        i++;
  
    }
    disable_servos();
    
}

int mag1(){
    
    enable_servos();
    int h = arm_bpole;
    
    while(h < arm_high){
    	set_servo_position(arm, h);
        h+=20;
   		msleep(100);
    }
    
    disable_servos();
    ao();
    forward_slow(1800);
    ao();
    pivot_right_s();
    msleep(1800);
    ao();
    forward(500);
    ao();
   	turnRight(350);
    ao();
    forward(200);
    
    enable_servos();
    set_servo_position(arm, 1730);
    msleep(300);
    disable_servos();
}


// a turning function that pivots left slowly
int pivot_left_s (){
  motor(l_motor, -l_speed);
  motor(r_motor, l_speed);
}

// turning function that pivots right slowly
int pivot_right_s (){
  motor(l_motor, 10);
  motor(r_motor, -10);
}

// drift motor function
int drift_right (){
    motor(r_motor, l_speed);
    motor(l_motor, f_speed);
    
}

// drift motor function
int drift_left(){
    motor(r_motor, f_speed);
    motor(l_motor, l_speed);
    
}

// forward motor function
int forward_med(){

motor(r_motor,f_speed);
motor(l_motor,f_speed);
}

// timed motor forward function
int forward(int timer){

motor(r_motor,f_speed);
motor(l_motor,f_speed);
msleep(timer);
}

int forward_slow(int timer){

motor(r_motor,10);
motor(l_motor,10);
msleep(timer);
}

// reverse motor function timed
int reverse(int timer){
printf("Moving Backwards \n");
motor(r_motor,-f_speed);
motor(l_motor,-f_speed);
msleep(timer);    
}

// timed motor right turn
int turnRight(int timer){
printf("Turning right \n"); 
motor(l_motor,f_speed);
motor(r_motor,-f_speed);
msleep(timer);
}

// timed motor left turn
int turnLeft(int timer){
printf("Turning left \n"); 
motor(r_motor,f_speed);
motor(l_motor,-f_speed);
msleep(timer);
}
