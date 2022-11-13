 /******************************************************************************
 *
 * Module: Mini_Project4
 *
 * File Name: Mini_Project4.c
 *
 * Description: Source file for the AVR Main Function
 *
 * Author: Tarek Ahmed
 *
 *******************************************************************************/

#include "lcd.h" /* To use LCD */
#include "ultrasonic.h" /* To use Ultrasonic */
#include <avr/io.h>/* To use I-bit */

void main(void)
{
	uint16 data=2;

	SREG |= (1<<7); /* To use Timer1 ISR */

	LCD_init(); /* Initialize LCD */

	Ultrasonic_init();/* Initialize Ultrasonic */

	LCD_displayString("Distance =    cm");

	for(;;)
	{
		data=Ultrasonic_readDistance(); /* Get ultrasonic measured distance */

		LCD_moveCursor(0, 11); /* Display ultrasonic measured distance in this location */

		if(data<=500 && data>=100) /* Maxmium value = 500 */
		{
			LCD_intgerToString(data); /* Display ultrasonic value in LCD */
		}
		else if(data<=500 && data>=10)
		{
			LCD_intgerToString(data); /* Display ultrasonic value in LCD */
			LCD_displayCharacter(' '); /* To remove third bit */
		}
		else if(data<10 && data>=3)/* Minimum value = 500 */
		{
			LCD_intgerToString(data); /* Display ultrasonic value in LCD */
			LCD_displayString("  ");/* To remove second bit */
		}

	}
}
