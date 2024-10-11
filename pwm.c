 /******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.c
 *
 * Description: Source file for the PWM driver
 *
 * Author: Mohamed Gamal
 *
 *******************************************************************************/


#include "pwm.h"
#include "gpio.h"
#include "avr/io.h"

/*
 * Description:
 * Function to start PWM on Timer0 with a specified duty cycle.
 * It initializes Timer0 in Fast PWM mode and sets up the output pin for PWM signal..
 */
void PWM_Timer0_start(uint8 duty_cycle)
{
    /* Reset the Timer0 counter to 0 */
    TCNT0 = 0;

    /* Calculate the Output Compare Register value based on the duty cycle.
     * The formula ensures the duty cycle is represented as a value in the range of OCR0 (0 to 255).
     */
    OCR0 = (uint8)(((uint32)duty_cycle * MAX_OVERFLOW) / 100);

    /* Set the pin (PB3) where PWM output will be generated as output */
    GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);

    /* Configure Timer0:
     * - WGM00 and WGM01: Set Timer0 to Fast PWM mode.
     * - COM01: Set non-inverting mode (clear on compare match).
     * - CS00 and CS02: Set the clock source to start the timer with a prescaler of 1024.
     */
    TCCR0 |= (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00) | (1<<CS02);
}

