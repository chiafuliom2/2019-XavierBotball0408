#include <kipr/botball.h>

//Variables//

int target_f = 2100;
int target_g = 3500; 
int fire_target = 3000;
int black = 1500;
int g_sens2 = 5;
int g_sens = 0;
int eyes = 3;
int servo = 0; 
int tophat = 1;
int LM = 1;
int RM = 3;
int speed1 = 47;
int speed2 = 70;
int speed3 = 85;
int yellow = 0;
int red = 1; 
int claw = 0;
int arm = 3;
int midpoint = 500;
int midmidpoint = 1500;
int highpoint = 100;
int lowpoint = 1950;
int claw_closed = 30;
int claw_opened = 800;
int claw_mid = 350;
int servo_pause = 1000;
int fire;
int count = 0;
int turn_count;

int main()
{
  	/*wait_for_light(2);
  	shut_down_in(120.0);*/

	init_servos();
    	printf("servos_in_position\n");
        forward();//drive forward briefly to get lined up with the ambulance
    msleep(750);
    ao();
    close_claw();
    raise_arm_mid();
	find_black();
    	printf("black_detected\n");
    ao();
    find_white();
    	printf("white_detected\n");
    ao();
    drift_r();//slight adjust turn to face hospitals
    msleep(3400);
    find_black();//find black line in front of med centers
    	printf("black detected at building\n");
    ao();
    find_white();
    ao();
    drift_r();//slight adjust turn to face hospitals
    msleep(750);
    ao();
drift_r_line();
    ao();
    backward();
    msleep(300);
    ao();
fire_check_loop();
decision();
}

//Function definitions//
//SERVO FUNCTIONS //
int raise_arm_mid()
{
    set_servo_position(arm,midpoint);
    msleep(servo_pause);
}
int raise_arm_midmid()
{
    set_servo_position(arm,midmidpoint);
    msleep(servo_pause);
}

int raise_arm_full()
{
    set_servo_position(arm,highpoint);
    msleep(servo_pause);
}
int lower_arm()
{
    set_servo_position(arm,lowpoint);
    msleep(servo_pause);
}
int open_claw()
{
    set_servo_position(claw,claw_opened);
    msleep(servo_pause);
}
int close_claw()
{
    set_servo_position(claw,claw_closed);
    msleep(servo_pause);
}
int forward()  
{
  	motor(LM,speed1);
	motor(RM,speed1);
}
int backward()
{
	motor (LM,-speed2);
	motor (RM,-speed2);
	//msleep(1400);
}
int l_turn()
{
  	motor(LM,-speed1);
    motor(RM,speed1);
}
int r_turn()
{
	while(analog(g_sens)<target_g)
	motor(LM, speed1);
 	motor(RM, -speed1);
}

int find_black()
{
  	while(analog(g_sens2)<target_g)
    {
        printf("gsens2=%d\n",analog(g_sens2));
      forward();
    //  msleep(1000);
    }
}
int stop_black()
{
  	while(analog(g_sens)>=target_g)
    {
      ao();
    }
}
int find_white()  
{
  	while(analog(g_sens2)>target_g)
    {
        printf("gsens2=%d\n",analog(g_sens2));
      forward();
    //  msleep(1000);
    }
}
int turn_white()
{  
	while(analog(g_sens2)<target_g)
    {	
    r_turn();
	}
}
int turn_black()
{
  while(analog(g_sens)<target_g)
  {
    r_turn();
  }
}   
int drift_r()  
{
    motor(LM,speed2);
    motor(RM,speed1);           
}
int drift_l()
{
	motor (LM,-10);
	motor (RM,speed2);
}

int big_drift_1()
{
    while(analog(g_sens2)<target_g)
    {
        drift_r();
    }
}
int pivot_r()  
{
    motor(LM,speed1);      
    msleep(2500);
}
int pivot_l()
{
	motor (RM,speed2);
    msleep(3000);
}
int line_follow_1()   
{
        while(analog(g_sens)<target_g)
		{           				  //while the bot is not sensing the line//
        if(analog(g_sens2)>target_g)
		{                                      //the bot will drift off the line when it senses it//
        	drift_l();
        }
        if(analog(g_sens2)<target_g)
		{                                  //the bot will drift onto the line when it doesn't sense it//
            drift_r_line();
        }
    }
    ao();
}
int line_follow_2()   
{
        while(analog(eyes)<target_f)
		{           				  //while the bot is not sensing the line//
        if(analog(g_sens)>target_g)
		{                                      //the bot will drift off the line when it senses it//
        	drift_r();
        }
        if(analog(g_sens)<target_g)
		{                                  //the bot will drift onto the line when it doesn't sense it//
            drift_l();
        }
    }
}

void decision(){
    printf("fire = %d\n",fire);
	if(fire == 1){
         printf("running fire_building 1\n");
		fire_building1();
        
       
	}
	if(fire == 0){
         printf("running fire_building 2\n");
		fire_building2();
        
	}
}

        
void fire_building1(){
    forward();
    msleep(500);
    ao();
	find_white();
        l_turn();
    	msleep(300);
    	ao();
    lower_arm();
	open_claw();
		
}
void fire_building2(){
    
    	printf("turning");
		backward();
    msleep(1500);
    ao();
    	l_turn();
    msleep(700);
    ao();
		lower_arm();
    	open_claw();// drops ambulance
    	raise_arm_mid();//get clear of ambulance
    msleep(1000);
    back_black();//back up to the black line
    ao();
    back_white();//baCK UP TO THE WHITE TABLE
    ao();
    lower_arm();	
    back_left(); //get clear of the dropped ambulance
    msleep(5000);
    find_black();
    close_claw();
    /*find_pillar();//turn till g_sens2 sees the black then follows the black till the ET sees the Fire pole
    ao();
    forward();//move forward to get the fireman
    msleep(1100);
    ao();
    close_claw();
    raise_arm_midmid();
    shimmy();*/
    backward();//reverse with fireman
    msleep(2000);
    raise_arm_full();//raise up the fireman
    back_right();//turns to face the middle line
    msleep(5000);
    ao();
    drift_r();
    msleep(2000);
    ao();
	turn_check();
    line_follow_3();//turn to the left and follow the line with the left sensor until the right  he med centers
    ao();
    pivot_r2();
    ao();
    lower_arm();
    open_claw();
}

int init_servos()
{
	enable_servos();
    set_servo_position(claw,claw_mid);
    set_servo_position(arm,lowpoint);
    msleep(servo_pause);
}
int drift_r_line()
{
	while(analog(g_sens2)<target_g){
        drift_r();
            printf("g_sens=%d\n");
        }
    }

    int fire_check_loop(){
        camera_open_black();
        int fire_yes = 0;
        int fire_no = 0;
        int count_loop = 0;
        fire = 0;
        while(count_loop==0){
            camera_update();
            msleep(200);
            
            if(get_object_count(red) > 0 ){
                printf("fire_yes = %d\n", fire_yes);
                fire_yes ++;
            }
          if(get_object_count(red) == 0 ){
               printf("fire_no = %d\n", fire_no);
                fire_no ++;
            }
            if(fire_no == 10){
                 printf("not seeing fire\n");
                count_loop = 1;
               
            }
            if(fire_yes == 10){
                 printf("seeing fire\n");
                fire = fire + 1;
                count_loop = 1;
                
            }
        }
       camera_close();
    }
int back_black()
{
    while(analog(g_sens2) < target_g){
        backward();
    }
}
int back_white()
{
    while(analog(g_sens2) > target_g){
        backward();
    }
}
int find_pillar()
{
    while(analog(g_sens2) < target_g){
        drift_l2();
    }
    while(analog(eyes) < 2300){
        if(analog(g_sens2) < target_g){
            drift_l();
        }
        if(analog(g_sens2) > target_g){
            drift_r();
        }
    }
}
int pivot_l2()
{
   motor (RM,speed2);
   msleep(500);
}
int pivot_r2()
{
   motor (LM,speed1);
   msleep(2000);
}
int find_white2()
{
  	while(analog(g_sens)<target_g)
    {
        printf("gsens2=%d\n",analog(g_sens2));
      forward();
    }
}    
int find_black2()  
{
  	while(analog(g_sens)>target_g)
    {
        printf("gsens2=%d\n",analog(g_sens2));
      forward();
    }
}    
int drift_black()  
{
    while(analog(g_sens2)<target_g)
    {
        printf("gsens2=%d\n",analog(g_sens2));
      drift_l2();
    }
}    
int drift_white()  
{
    while(analog(g_sens2)>target_g)
    {
        printf("gsens2=%d\n",analog(g_sens2));
      drift_l2();
    }
}        
int drift_l2()
{
	motor (LM,10);
	motor (RM,40);
    printf("drifting");
}
drift_r2()
{
    motor(LM,40);
    motor(RM,10);
}
int line_follow_3()   
{
    while(analog(g_sens) < fire_target)
		{           				  //while the bot is not sensing the line//
        if(analog(g_sens2)>target_g)
		{                                      //the bot will drift off the line when it senses it//
        	drift_r();
        }
        if(analog(g_sens2)<target_g)
		{                                  //the bot will drift onto the line when it doesn't sense it//
            drift_l();
        }
    }
}
int shimmy()
{
    back_left();
    msleep(150);
    back_right();
    msleep(150);
    back_left();
    msleep(300);
    back_right();
    msleep(300);
    back_left();
    msleep(200);
    back_right();
    msleep(200);
}
int back_left()
{
    motor(LM,-speed3);
    motor(RM,-30);
}
int back_right()
{
    motor(LM,-30);
    motor(RM,-speed3);
}
void turn_check()
{
    turn_count = 0;
    while (turn_count ==0){
        if(analog(g_sens2) > target_g){
        find_white();
            turn_count=1;
    }
    if(analog(g_sens2) < target_g){
        find_black();
        find_white();
        turn_count = 1;
    }
    }
    ao();
}
int firetruck()
{
    while(analog(g_sens2) < target_g){
        drift_l2();
    }
}
    
    
