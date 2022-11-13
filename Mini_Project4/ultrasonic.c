/******************************************************************************
 *
 * Module: ULTRASONIC
 *
 * File Name: ultrasonic.c
 *
 * Description: Source file for the AVR ULTRASONIC driver
 *
 * Author: Tarek Ahmed
 *
 *******************************************************************************/

#include "ultrasonic.h"
#include "icu.h" /* To use call back function and calculate edge */
#include "gpio.h"
#include <util/delay.h>/* To use delay in Trigger  function  */

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

Icu_ConfigType Config_Ptr={F_CPU_8,RISING}; /* Configre Icu */

static volatile uint8 g_count_edge=0;
static volatile uint16 g_highTimePulse=0;


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Set ultrasonic setting
 * First initialize Icu
 * call back edge processing function
 * Set Triggre pin output
 */

void Ultrasonic_init(void)
{
	Icu_init(&Config_Ptr); /* Initialize Icu */

	Icu_setCallBack(Ultrasonic_edgeProcessing); /* call back edge processing function b*/

	GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID, PIN_OUTPUT);
}


/*
 * Send signal for 10us
 */

void Ultrasonic_Trigger(void)
{
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID, LOGIC_LOW);
}


/*
 * send 10us for ultrasonic trigger pin
 * wait until calculate edge  and calculate distance
 *return measured distance
 */

uint16 Ultrasonic_readDistance(void)
{
	uint16 distance=0;
	g_highTimePulse=0;
	g_count_edge=0;

	Ultrasonic_Trigger();

	while(g_count_edge != ECHO_EDGES) { }

	/*
	 * Sound velocity = 340.00 m/s = 34000 cm/s
	 * The distance of Object (in cm) = (34000 * Time)/2
	 * = 17000 * Time
	 *
	 *Prescaler F_CPU/8 for timer frequency. Then time to execute 1 instruction is 1 us.
	 *= 17000 x (TIMER value) x 1 x 10^-6 cm
	 *= 0.017 x (TIMER value) cm
	 *= (TIMER value) / 58.8  cm
	 *= 	distance=g_highTimePulse/58.5;
	 */

	distance=(g_highTimePulse/58)+1; /* Calculate the measured distance */
	return distance;
}


/*
 * capture edge
 */

void Ultrasonic_edgeProcessing(void)
{
	g_count_edge++;

	if(1==g_count_edge) /* First edge*/
	{

		Icu_clearTimerValue();

		Icu_setEdgeDetectionType(FALLING); /* Detect Falling edge */
	}
	else if(2==g_count_edge) /* Second edge*/
	{

		g_highTimePulse=Icu_getInputCaptureValue();

		Icu_clearTimerValue(); /*Clear ICU timer */

		Icu_setEdgeDetectionType(RISING);/* Detect Raising edge */
	}
}


