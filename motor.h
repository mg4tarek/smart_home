 /******************************************************************************
 *
 * Module: Motor
 *
 * File Name: motor.h
 *
 * Description: Header file for the Motor driver
 *
 * Author: Mohamed Gamal
 *
 *******************************************************************************/

#ifndef MOTOR_H_
#define MOTOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*
 * Define the port and control pins for the DC motor.
 * These macros are used to specify the connections for controlling the motor.
 */
#define DC_MOTOR_PORT   PORTB_ID  // Port where the DC motor is connected
#define DC_MOTOR_IN1    PIN0_ID   // Control pin 1 for the DC motor
#define DC_MOTOR_IN2    PIN1_ID   // Control pin 2 for the DC motor

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/*
 * Enum to represent the possible states of the DC motor.
 * - CW: Clockwise rotation.
 * - ACW: Anti-clockwise rotation.
 * - Stop: Motor is stopped.
 */
typedef enum
{
    CW,      // Clockwise rotation
    ACW,     // Anti-clockwise rotation
    Stop     // Motor is stopped
} DcMotor_State;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:
 * Function to initialize the DC motor.
 * This sets up the necessary GPIO pins as output and ensures the motor is in a stopped state.
 */
void DcMotor_Init(void);

/*
 * Description:
 * Function to control the rotation of the DC motor. It takes two parameters:
 * - state: The desired state of the motor (CW, ACW, Stop).
 * - speed: The speed of the motor, controlled via PWM (0 to 100%).
 */
void DcMotor_Rotate(DcMotor_State state, uint8 speed);

#endif /* MOTOR_H_ */

