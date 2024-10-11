 /******************************************************************************
 *
 * Module: Flame sensor
 *
 * File Name: flame_sensor.c
 *
 * Description: Source file for the Flame sensor driver
 *
 * Author: Mohamed Gamal
 *
 *******************************************************************************/
#include "flame_sensor.h"
#include "gpio.h"

/*
 * Description:
 * Function to initialize the flame sensor and ADC. It sets the pin connected to the flame sensor as input.
 *
 */
void FlameSensor_init(void)
{
	/* Set the flame sensor pin direction as input */
	GPIO_setupPinDirection(FlameSensor_port, FlameSensor_pin, PIN_INPUT);
}

/*
 * Description:
 * Function to get the current value from the flame sensor.
 * It reads the pin connected to the flame sensor and returns the logic state.
 * Return value:
 *  - LOGIC_HIGH (1) if a flame is detected.
 *  - LOGIC_LOW (0) if no flame is detected.
 */
uint8 FlameSensor_getValue(void)
{
	/* Read and return the logic state of the flame sensor pin */
	return GPIO_readPin(FlameSensor_port, FlameSensor_pin);
}
