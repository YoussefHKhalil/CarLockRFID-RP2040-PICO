/*
 * buzzer.h
 *
 *  Created on: 9 Oct 2024
 *      Author: youss
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#define BUZZER 14


/*
 * Description :
 * Initializes the buzzer pin direction and turn off the buzzer.
 */
void Buzzer_init(void);

/*
 * Description :
 * Activates the buzzer.
 */
void Buzzer_on(void) ;


/*
 * Description :
 * Deactivates the buzzer.
 */
void Buzzer_off(void) ;




#endif /* BUZZER_H_ */