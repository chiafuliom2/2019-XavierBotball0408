#include <kipr/botball.h>
/*

1. Move to burning medical centers on an msleep while loop
2. follow medical center black line with left infrared sensor in a while loop until right sensor detects.
3. Move on black line until white line is detected with right sensor
4. Turn right and follow black line with right infrared sensor while loop with claw sensor.
5. Have claw extended for the whole duration of follow line
6. once black line is detected, turn off all motors and close claw.
7. lift up claw and turn right.
8. Follow wall while loop and push WTC deep into the utility zone. Break while loop when infrared sensor detects black line of utility zone. 
9. Deposit poms in WTC and tamp it down
10. Possibly do something with the power lines.
*/

// Variable Declarations

int r_motor = 0;
int l_motor = 2;
int speed_avg = 50;
int b_right = 1;
int b_claw = 2;
int d_left = 3;
int b_r_sweet = 650;
int d_wash_sweet = 2500;
int d_start_sweet = 1450;
int button = 0;
int f_speed = 40;
int l_speed = 20;
int claw = 2;
int open_c = 200;
int close_c = 1640;
int left_arm = 1;
int right_arm = 0;
int left_arm_down = 1625; // 1120
int right_arm_down = 375; //970
int right_max = 1500;
int left_max = 600;
int wall = 3;
int open_w = 650;
int close_w = 1900;
int arm_tamp = 1000;
int d_med_sweet = 1000;


// Function Declarations

int main(){
   // lower_plow();
    initialize();
    move_to_mid_line();
    cross();
    lift_and_align();
    
    
    
   // approach_bucket();
    
    /*
    lift_plow();
    disable_servos();
    dump();
    ao();
    msleep(2000);
    lower_plow();
    */
    
    return 0;
}
int lift_and_align(){
    open_claw();
    msleep(2000);
    printf("closing slowly");
    back_up_close();
    reverse(500);
    ao();
    close_claw_s();
    ao();
    reverse(1000);
    turnRight(1600);
    ao();
    
}


int back_up_close(){
    int pos = open_c;
    reverse(800);
    ao();
    enable_servos();
    while(pos < close_c){
    set_servo_position(claw, pos);
    msleep(50);
    pos += 10;
    }
    disable_servos();
    
    
    
}



/*Once we finish following the main black line, we should be in front of the power lines. 
	This function turns right and then follows the wall until we hit the black line that marksthe utility zone. 
    In this process, we will be pushing the water treatment zone into the utility zone during the line follow 
    since it will be in the path of motion.
*/
int approach_bucket (){
    
    
    while(analog(b_right) < b_r_sweet){
        if(analog(d_left) > d_wash_sweet){
            drift_right();
        }
        
        if(analog(d_left) < d_wash_sweet){
            drift_left();
        }
    }
    forward(2000);
}



// this dump function opens the back wall of the plow and shakes to let the poms out. 
// It then tamps the poms down with the bottom of the plow
int dump (){
    
    open_wall();
   // shake();
    msleep(5000);
    close_wall();
    reverse(1000); 
    disable_servos();
}

//  Moves the plow up and down in little increments to shake the poms out of the plow and into the treatment zone.
//
int shake(){
    
    enable_servos();
    
    int i = 0;
    while(i < 10){
        
     //   set_servo_position(arm, arm_up+50);
    	msleep(100);
      //  set_servo_position(arm, arm_up-50);
        msleep(100);
       i++;
    }
    disable_servos();
}


// Calls servo functions to set servos for our initial conditions
int initialize(){
    
    	close_wall();
    	set_servo_position(left_arm, left_arm_down);
    	set_servo_position(right_arm, right_arm_down);
    	msleep(500);
    	medium_claw();
    	
   
}

//servo function that closes the back wall of the plow
int close_wall (){
    enable_servos();
    set_servo_position(wall, close_w);
    msleep(1000);
    disable_servos();  
}

// servo function that opens the back wall of the plow
int open_wall (){
    enable_servos();
    set_servo_position(wall, open_w);
    msleep(1000);
    disable_servos();   
}

int medium_claw(){
    enable_servos();
    set_servo_position(claw, 1100);
    msleep(500);
    disable_servos();
}

// servo function that lowers the plow
int lower_plow(){
    
    printf("finding line");
	int h = left_max;
	int l = right_max;
    enable_servos();
    while(h < left_arm_down && l > right_arm_down){
        printf("raising");
  		set_servo_position(right_arm,l);
		set_servo_position(left_arm,h);
    	l -= 1; 
    	h += 1;
        msleep(5);
     }
}

// servo function that raises the plow
int lift_plow(){
    
	int h = left_arm_down;
	int l = right_arm_down;
    enable_servos();
    while(h > left_max && l < right_max){
        printf("raising \n" );
     	
  		set_servo_position(right_arm,l);
		set_servo_position(left_arm,h);
    	l += 1; 
    	h -= 1;
        msleep(5);
     }
}

// We begin this function in the starting box. The Robot should be positioned diagonally to the medical center tape.
// the bot will move forward, past the starting tape lines.
// Next, it will move forward on a while loop until it detects the black line that marks the outskirts of the medical centers
// Next, it will be following the line that marks the medical center until it detects the main dissecting line of the course.
// We will break out if this while loop by detecting the medical center.
// Then, we will manuever to position ourselves right next to the middle line, where we will then follow it in the next function. 
int move_to_mid_line (){
    
    while(analog(b_right) < b_r_sweet){
        forward();
    }
    printf("Touched Tape");
    forward(1000);
    ao();
    close_claw_s();
    ao();
    while(digital(button) == 0){
        if (analog(d_left) < d_start_sweet){
            drift_left();
        }
        if (analog(d_left) > d_start_sweet){
            drift_right();
        }
    }
    printf("Followed Wall");
    
    reverse(1500);
    ao();
    turnRight(1650);
    ao();
    printf("Approaching Midline");
    while(analog(b_right) < b_r_sweet){
        forward();
    }
    printf("Touched Midline");
    reverse(500);
    ao();
    open_claw();
    ao();
    
    forward(1500);
    ao();
    close_claw_s();
    forward(500);
    ao();
    printf("Pivoting");
    
    while(analog(b_right) < b_r_sweet){
        pivot_right_s();
    }
    ao();
    open_claw();
    forward(600);
    ao();
    close_claw_s();
   
    while(analog(b_right) < b_r_sweet){
        pivot_right_s();
    }
    open_claw();
    forward(500);
     while(analog(b_right) < b_r_sweet){
        pivot_right_s();
    }
    printf("On the midline, prepared to cross");
    
}


// Servo function to open the claw
int open_claw(){
 
    enable_servos();
    set_servo_position(claw, open_c);
    msleep(1000);
    disable_servos();
}
    
// this function is a while loop that will follow the black middle line to the other side of the board.
// we will collect poms in the process
// To break out of the loop, we will use a black line sensor attached to the claw to detect the black line near the gas valve

int cross (){
    while(digital(button) == 0){
        if(analog(b_right) < b_r_sweet){
            drift_right();
        }
        
        if(analog(b_right) > b_r_sweet){
            drift_left();
        }    
    }
}

// servo function to close the claw
int close_claw_s(){
    enable_servos();
    set_servo_position(claw, close_c);
    msleep(1000);
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