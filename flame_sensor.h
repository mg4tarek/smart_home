 /******************************************************************************
 *
 * Module: Flame sensor
 *
 * File Name: flame_sensor.H
 *
 * Description: Header file for the Flame sensor driver
 *
 * Author: Mohamed Gamal
 *
 *******************************************************************************/

#ifndef FLAME_SENSOR_H_
#define FLAME_SENSOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*
 * Define the port and pin where the flame sensor is connected.
 */
#define FlameSensor_port PORTD_ID  // Flame sensor is connected to Port D
#define FlameSensor_pin  PIN2_ID   // Flame sensor is connected to Pin 2

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:
 * Function to initialize the flame sensor.
 * It sets the pin connected to the flame sensor as input.
 */
void FlameSensor_init(void);

/*
 * Description:
 * Function to get the current value from the flame sensor.
 * It reads the logic state of the flame sensor pin and returns:
 *  - LOGIC_HIGH (1) if a flame is detected.
 *  - LOGIC_LOW (0) if no flame is detected.
 */
uint8 FlameSensor_getValue(void);

#endif /* FLAME_SENSOR_H_ */
