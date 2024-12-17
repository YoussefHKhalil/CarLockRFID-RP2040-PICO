#ifndef LED_H_
#define LED_H_


#define RED_LED 6
#define GREEN_LED 7
#define BLUE_LED 8


typedef enum {
	RED,GREEN,BLUE
}LED_ID ;



/*
 * Description :
 * Function responsible for initializing all Leds (red, green, blue) pins direction.
 */
void LEDS_init(void) ;


/*
 * Description :
 * Function responsible for turning on the given led.
 */
void LED_on(LED_ID id) ;


/*
 * Description :
 * Function responsible for turning off the given led.
 */
void LED_off(void) ;


#endif