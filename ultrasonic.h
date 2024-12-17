#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_



#define TRIGGER 3    
#define ECHO  2 

void Ultrasonic_init(void);


unsigned short Ultrasonic_readDistance(void);



#endif