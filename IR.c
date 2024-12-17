#include <stdio.h>
#include "pico/stdlib.h"
#include "IR.h"


void IR_init(void){
    gpio_init(IR_Pin);
    gpio_set_dir(IR_Pin,GPIO_IN);

}

bool IR_getState(uint IR_pin){
	return gpio_get(IR_pin);
}
