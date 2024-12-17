#ifndef MOTOR_H
#define MOTOR_H


#define Motor_pwm 22
#define Motor_dir1 26
#define Motor_dir2 27


void motor_init(void);

void motor_drive(uint16_t speed, bool forward);

#endif