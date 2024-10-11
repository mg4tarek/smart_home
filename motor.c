 /******************************************************************************
 *
 * Module: Motor
 *
 * File Name: motor.c
 *
 * Description: Source file for the Motor driver
 *
 * Author: Mohamed Gamal
 *
 *******************************************************************************/
#include "motor.h"
#include "gpio.h"
#include "pwm.h"

/*
 * Description:
 * Function to initialize the DC motor.
 * It sets the direction of the motor control pins (IN1 and IN2) as output.
 * Initially, both control pins are set to LOW, stopping the motor.
 */
void DcMotor_Init(void)
{
    /* Set the motor control pin IN1 as output */
    GPIO_setupPinDirection(DC_MOTOR_PORT, DC_MOTOR_IN1, PIN_OUTPUT);

    /* Set the motor control pin IN2 as output */
    GPIO_setupPinDirection(DC_MOTOR_PORT, DC_MOTOR_IN2, PIN_OUTPUT);

    /* Initially, stop the motor by setting both IN1 and IN2 to LOW */
    GPIO_writePin(DC_MOTOR_PORT, DC_MOTOR_IN1, LOGIC_LOW);
    GPIO_writePin(DC_MOTOR_PORT, DC_MOTOR_IN2, LOGIC_LOW);
}

/*
 * Description:
 * Function to rotate the DC motor in a specific direction and at a certain speed.
 * It takes two arguments:
 *  - state: The desired state of the motor (CW, ACW, Stop).
 *  - speed: The speed of the motor, controlled via PWM (0 to 100%).
 */
void DcMotor_Rotate(DcMotor_State state, uint8 speed)
{
    /* Start the PWM signal to control the motor speed */
    PWM_Timer0_start(speed);

    /* Set the motor's rotation state */
    switch(state)
    {
        case CW:
            /* Rotate the motor clockwise: IN1 is LOW, IN2 is HIGH */
            GPIO_writePin(DC_MOTOR_PORT, DC_MOTOR_IN1, LOGIC_LOW);
            GPIO_writePin(DC_MOTOR_PORT, DC_MOTOR_IN2, LOGIC_HIGH);
            break;

        case ACW:
            /* Rotate the motor anti-clockwise: IN1 is HIGH, IN2 is LOW */
            GPIO_writePin(DC_MOTOR_PORT, DC_MOTOR_IN1, LOGIC_HIGH);
            GPIO_writePin(DC_MOTOR_PORT, DC_MOTOR_IN2, LOGIC_LOW);
            break;

        case Stop:
            /* Stop the motor by setting both IN1 and IN2 to LOW */
            GPIO_writePin(DC_MOTOR_PORT, DC_MOTOR_IN1, LOGIC_LOW);
            GPIO_writePin(DC_MOTOR_PORT, DC_MOTOR_IN2, LOGIC_LOW);
            break;
    }
}
