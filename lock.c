#include <stdio.h>
#include "pico/stdlib.h"
#include "lock.h"


void doorlock_init(void) {
    gpio_init(Lock);
    gpio_set_dir(Lock, GPIO_OUT);
}

void unlock_door(void){
    gpio_put(Lock,true);
}

void lock_door(void){
    gpio_put(Lock,false);
}