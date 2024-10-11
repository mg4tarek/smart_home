/*
 ================================================================================================
File Name    : smart_home.c

 Author      : Mohamed Gamal

 Description : Smart Home Automation Using ATmega32, LCD, Temperature Sensor, LDR Sensor, Flame Sensor
 and Motor Control

 Date        : Oct 5, 2024
 ================================================================================================
 */

#include "buzzer.h"
#include "led.h"
#include "motor.h"
#include "lm35_sensor.h"
#include "ldr_sensor.h"
#include "flame_sensor.h"
#include "lcd.h"
#include <util/delay.h>
#include "std_types.h"

int main(void)
{
	/* Variable declarations*/
	uint8 light     = 0;       /* Variable to store light intensity */
	uint8 temp      = 0;       /* Variable to store temperature */
	uint8 flame_flag = 0;      /* Flag to indicate if a flame is detected */

	/* Initialize devices*/
	LM35_init();                /* Initialize the temperature sensor */
	LDR_init();					/* Initialize the LDR sensor */
	FlameSensor_init();         /* Initialize the flame sensor */
	LDR_getLightIntensity();    /* Initialize the light sensor */
	BUZZER_init();              /* Initialize the buzzer */
	LEDS_init();                /* Initialize the LEDs */
	LCD_init();                 /* Initialize the LCD */
	DcMotor_Init();             /* Initialize the DC motor */


	/* Display initial messages on the LCD*/
	LCD_displayStringRowColumn(1, 0, "Temp=   ");
	LCD_displayStringRowColumn(1, 8, "LDR=   %");

	while (1) /* Infinite loop */
	{
		/* Read temperature and light intensity*/
		temp  = LM35_getTemperature();          /* Get temperature from the LM35 sensor */
		light = LDR_getLightIntensity();         /* Get light intensity from the LDR sensor */

		/********************************************************/
		/* Check for flame detection */
		if (FlameSensor_getValue())
		{
			flame_flag = 1;                      /* Set flame flag */
			BUZZER_on();                         /* Activate the buzzer for alert */
			LCD_clearScreen();                   /* Clear the LCD screen */
			LCD_displayStringRowColumn(0, 0, "Critical alert!"); /* Display alert message */
			while (FlameSensor_getValue());     /* Wait until flame is no longer detected */
		}
		else
		{
			/* If flame was previously detected and is now gone */
			if (flame_flag == 1)
			{
				flame_flag = 0;                  /* Reset flame flag */
				BUZZER_OFF();                    /* Turn off the buzzer */
				LCD_clearScreen();/* Clear the LCD screen */
				LCD_displayStringRowColumn(1, 0, "Temp=   "); /* Redisplay temperature label */
				LCD_displayStringRowColumn(1, 8, "LDR=   %"); /* Redisplay LDR label */
			}
		}
		/********************************************************/

		/* Fan control based on temperature */
		if (temp < 25)
		{
			LCD_displayStringRowColumn(0, 3, "FAN is OFF"); /* Indicate fan is off */
		}
		else
		{
			LCD_displayStringRowColumn(0, 3, "FAN is ON");  /* Indicate fan is on */
			LCD_displayCharacter(' ');                    /* Clear any extra characters */
		}

		/* Move cursor to Temp section on the LCD */
		LCD_moveCursor(1, 5); /* Move cursor to the position for temperature */

		if (temp >= 100)
		{
			LCD_intgerToString(temp); /* Display temperature value */
		}
		else
		{
			LCD_intgerToString(temp); /* Display temperature value */
			LCD_displayCharacter(' '); /* Clear any extra spaces */
		}

		/* Control motor speed based on temperature */
		if (temp >= 40)
		{
			DcMotor_Rotate(ACW, 100); /* Rotate motor at full speed */
		}
		else if ((temp >= 35) && (temp < 40))
		{
			DcMotor_Rotate(ACW, 75); /* Rotate motor at 75% speed */
		}
		else if ((temp >= 30) && (temp < 35))
		{
			DcMotor_Rotate(ACW, 50); /* Rotate motor at 50% speed */
		}
		else if ((temp >= 25) && (temp < 30))
		{
			DcMotor_Rotate(ACW, 25); /* Rotate motor at 25% speed */
		}
		else
		{
			DcMotor_Rotate(Stop, 0); /* Stop the motor */
		}

		/********************************************************/
		/* Move cursor to LDR section on the LCD */
		LCD_moveCursor(1, 12); /* Move cursor to the position for light intensity */

		if (light == 100)
		{
			LCD_intgerToString(light); /* Display light intensity value */
		}
		else
		{
			LCD_intgerToString(light); /* Display light intensity value */
			LCD_displayCharacter(' '); /* Clear any extra spaces */
		}

		/* Control LEDs based on light intensity */
		if (light > 70)
		{
			LED_off(LED1); /* Turn off all LEDs if light intensity is > 70 */
			LED_off(LED2);
			LED_off(LED3);
		}
		else if ((light <= 70) && (light > 50))
		{
			LED_on(LED1);  /* Turn on LED1 if light intensity is  51–70%:*/
			LED_off(LED2);
			LED_off(LED3);
		}
		else if ((light <= 50) && (light > 15))
		{
			LED_on(LED1);  /* Turn on LED1 and LED2 if light intensity is 16–50% */
			LED_on(LED2);
			LED_off(LED3);
		}
		else
		{
			LED_on(LED1);  /* Turn on all LEDs if light intensity is < 15% */
			LED_on(LED2);
			LED_on(LED3);
		}
	}
}
