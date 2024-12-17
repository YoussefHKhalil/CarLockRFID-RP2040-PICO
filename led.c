/*
 * led.c
 *
 *  Created on: 11 Oct 2024
 *      Author: youss
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include "led.h"


/*
 * Description :
 * Function responsible for initializing all Leds (red, green, blue) pins direction.
 */
void LEDS_init(void) {
	gpio_init(RED_LED);
    gpio_init(GREEN_LED);
    gpio_init(BLUE_LED);
	
	gpio_set_dir(RED_LED, GPIO_OUT);
    gpio_set_dir(GREEN_LED, GPIO_OUT);
    gpio_set_dir(BLUE_LED, GPIO_OUT);

}



/*
 * Description :
 * Function responsible for turning on the given led.
 */
void LED_on(LED_ID id) {
	switch(id){
	case RED : 	
        gpio_put(RED_LED, true);
        break ;
	case GREEN : 
        gpio_put(GREEN_LED, true);
		break ;
	case BLUE : 
        gpio_put(BLUE_LED, true);
		break ;
	}
}


/*
 * Description :
 * Function responsible for turning off the given led.
 */
void LED_off() {
    gpio_put(RED_LED, false);
    gpio_put(GREEN_LED, false);
    gpio_put(BLUE_LED, false);
}



