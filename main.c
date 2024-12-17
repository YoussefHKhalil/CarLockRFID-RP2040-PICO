#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/spi.h"
#include "lcd.h"
#include "IR.h"
#include "buzzer.h"
#include "lock.h"
#include "motor.h"
#include "ultrasonic.h"
#include "rc522.h"
#include "led.h"



int main() { 

    stdio_init_all();
    LCD_init();
    IR_init();
    doorlock_init();
    Buzzer_init();
    motor_init();
    Ultrasonic_init();
    LEDS_init(); 
    rc522_init();
    LED_on(BLUE);
    int fault = 0;
    while (1) { 
        unsigned short distance = Ultrasonic_readDistance();
        LCD_moveCursor(0,0);
        LCD_displayString("Welcome Stranger");
        if (distance < 15) {
            LCD_clearScreen();
            LCD_moveCursor(0,0);
            LCD_displayString("Please Scan");
            LCD_moveCursor(1,0);
            LCD_displayString("Your Card");
            LED_off();
            LED_on(RED);
            while(1){
                unsigned int uid = rc522_get_uid();
                if (uid == DESIRED_UID) {
                    fault = 0;
                    unlock_door();
                    LED_off();
                    LED_on(GREEN);
                    LCD_clearScreen();
                    LCD_moveCursor(0,0);
                    LCD_displayString("WELCOME KHELLO");
                    sleep_ms(2000);
                    motor_drive(200,false);
                    sleep_ms(500);
                    motor_drive(0,false);  
                    while(1){
                        bool entered_car = IR_getState(IR_Pin);
                        bool done = false;
                        if (!entered_car && !done) {
                            motor_drive(200,true);
                            sleep_ms(500);
                            motor_drive(0,true);
                            LCD_clearScreen();
                            LCD_moveCursor(0,0);
                            LCD_displayString("Let's GOOOOOOOOO");
                            LCD_moveCursor(1,0);
                            LCD_displayString("HOOOOMMMEEEE");
                            sleep_ms(2000);
                            lock_door();
                            LED_off();
                            LED_on(RED);
                            done = true;
                            while(1){

                            }
                        }
                    }
                }
                else if(uid == UNDESIRED_UID && fault < 3){
                    lock_door();
                    fault++;
                    LCD_clearScreen();
                    LCD_moveCursor(0,0);
                    LCD_displayString("Wrong Card !");
                    LCD_moveCursor(1,0);
                    LCD_displayString("Plz Try Again");
                    for (int buzz_count = 0; buzz_count < 3; buzz_count++) {
                        Buzzer_on();
                        LED_off();
                        LED_on(RED);
                        sleep_ms(200);  
                        Buzzer_off();
                        LED_off();
                        sleep_ms(200);
                    }
                }else if(fault >= 3){
                    LCD_moveCursor(0,0);
                    LCD_displayString("Warning ! ! ! !");
                    LCD_moveCursor(1,0);
                    LCD_displayString("Emshi Ya Harami");
                    for (int buzz_count = 0; buzz_count < 5; buzz_count++) {
                        Buzzer_on();
                        LED_off();
                        LED_on(RED);
                        sleep_ms(1000);
                        Buzzer_off();
                        LED_off();
                        sleep_ms(500);
                    }
                    while (1)
                    {
                    }
                    

                }
            }
        }
        
    } 
    return 0; 
}

