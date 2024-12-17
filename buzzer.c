/*
 * buzzer.c
 *
 *  Created on: 9 Oct 2024
 *      Author: youss
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include "buzzer.h"


/*
 * Description :
 * Initializes the buzzer pin direction and turn off the buzzer.
 */
void Buzzer_init(void){
	gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);
}


/*
 * Description :
 * Activates the buzzer.
 */
void Buzzer_on(void) {
	gpio_put(BUZZER,true);
}

/*
 * Description :
 * Deactivates the buzzer.
 */
void Buzzer_off(void) {
	gpio_put(BUZZER,false);
}
