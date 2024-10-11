/******************************************************************************
 *
 * Module: LDR sensor
 *
 * File Name: ldr_sensor.c
 *
 * Description: Source file for the LDR sensor driver
 *
 * Author: Mohamed Gamal
 *
 *******************************************************************************/


#include "ldr_sensor.h"
#include "led.h"
#include "adc.h"


/*
 * ADC configuration for the LDR sensor:
 * - Reference voltage: Internal 2.56V.
 * - Prescaler: 128.
 */
ADC_ConfigType adc_ldr_configurations = {Internal_2_56v, ONE_HUNDRED_TWENTY_EIGHT};

/*
 * ADC Ref Voltage for ldr.
 */
static float ADC_Ref_Voltage_ldr = 0;


/*
 * Description :
 * Function initiate the sensor and  ADC.
 */

void LDR_init(void)
{
	ADC_init(&adc_ldr_configurations);

	switch (adc_ldr_configurations.ref)
	{
	case AVCC:
		ADC_Ref_Voltage_ldr = 5.0;
		break;
	case Internal_2_56v:
		ADC_Ref_Voltage_ldr = 2.56;
		break;
	case AREF:
		ADC_Ref_Voltage_ldr = 3.3; /* Example for an external reference */
		break;
	default:
		ADC_Ref_Voltage_ldr = 0.0;
		break;
	}
}

/*
 * Description:
 * Function to get the light intensity percentage from the LDR (Light Dependent Resistor).
 * It reads the ADC value, converts it to a voltage, and calculates the corresponding light intensity.
 * The function returns the light intensity as a percentage (0% - 100%).
 */


uint8 LDR_getLightIntensity(void)
{
	uint8 light_value = 0;

	uint16 adc_value = 0;

	adc_value = ADC_readChannel(LDR_SENSOR_CHANNEL_ID);

	light_value = (uint8)(LDR_SENSOR_MAX_LIGHT_INTENSITY*(1-(((float32)adc_value*ADC_Ref_Voltage_ldr )/(LDR_SENSOR_MAX_VOLT_VALUE*ADC_MAXIMUM_VALUE))));

	return ( 100-light_value);
}

