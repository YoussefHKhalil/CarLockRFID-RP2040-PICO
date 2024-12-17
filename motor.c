#include "pico/stdlib.h"
#include "motor.h"
#include "hardware/pwm.h"

void motor_init() {

    gpio_init(Motor_dir1);
    gpio_set_dir(Motor_dir1, GPIO_OUT);
    gpio_init(Motor_dir2);
    gpio_set_dir(Motor_dir2, GPIO_OUT);


    gpio_set_function(Motor_pwm, GPIO_FUNC_PWM);

    uint slice = pwm_gpio_to_slice_num(Motor_pwm);

    pwm_set_wrap(slice,255);
    pwm_set_clkdiv(slice,4.0f);

    pwm_set_enabled(slice,true);

}

void motor_drive(uint16_t speed, bool forward){
    if(speed > 255) speed = 255;

    if(forward){
        gpio_put(Motor_dir1,1);
        gpio_put(Motor_dir2,0);
    }else{
        gpio_put(Motor_dir1,0);
        gpio_put(Motor_dir2,1);
    }

    pwm_set_gpio_level(Motor_pwm,speed);
}