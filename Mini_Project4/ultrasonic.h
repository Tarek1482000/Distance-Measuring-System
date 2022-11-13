 /******************************************************************************
 *
 * Module: ULTRASONIC
 *
 * File Name: ultrasonic.h
 *
 * Description: Header file for the AVR ULTRASONIC driver
 *
 * Author: Tarek Ahmed
 *
 *******************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ULTRASONIC_TRIGGER_PORT_ID           PORTD_ID
#define ULTRASONIC_TRIGGER_PIN_ID            PIN5_ID

#define ULTRASONIC_ECHO_PORT_ID              PORTD_ID
#define ULTRASONIC_ECHO_PIN_ID               PIN6_ID

#define ECHO_EDGES                           2

#define SOUND_VELOCITY_IN_CM_AT_HALF_TIME     17000

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/


/*
 * Set ultrasonic setting
 * First initialize Icu
 * call back edge processing function
 * Set Triggre pin output
 */

void Ultrasonic_init(void);

/*
 * Send signal for 10us
 */

void Ultrasonic_Trigger(void);

/*
 * send 10us for ultrasonic trigger pin
 * wait until calculate edge  and calculate distance
 *return measured distance
 */
uint16 Ultrasonic_readDistance(void);

/*
 * capture edge
 */
void Ultrasonic_edgeProcessing(void);


#endif /* ULTRASONIC_H_ */
