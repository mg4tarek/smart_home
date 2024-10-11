 /******************************************************************************
 *
 * Module: Temperature Sensor
 *
 * File Name: lm35_sensor.h
 *
 * Description: source file for the LM35 Temperature Sensor driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#include "lm35_sensor.h"
#include "adc.h"


/*
 * ADC configuration for the LM35 sensor:
 * - Reference voltage: Internal 2.56V.
 * - Prescaler: 128.
 */
ADC_ConfigType adc_lm35_configurations = {Internal_2_56v, ONE_HUNDRED_TWENTY_EIGHT};

/*
 * ADC Ref Voltage for lm35.
 */
static float ADC_Ref_Voltage_lm35 = 0;

/*
 * Description :
 * Function initiate sensor and  ADC.
 */
void LM35_init(void)
{
	ADC_init(&adc_lm35_configurations);

	switch (adc_lm35_configurations.ref)
	{
	case AVCC:
		ADC_Ref_Voltage_lm35 = 5.0;
		break;
	case Internal_2_56v:
		ADC_Ref_Voltage_lm35 = 2.56;
		break;
	case AREF:
		ADC_Ref_Voltage_lm35 = 3.3; // Example for an external reference
		break;
	default:
		ADC_Ref_Voltage_lm35 = 0.0;
		break;
	}
}

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */

uint8 LM35_getTemperature(void)
{
	uint8 temp_value = 0;

	uint16 adc_value = 0;

	/* Read ADC channel where the temperature sensor is connected */
	adc_value = ADC_readChannel(SENSOR_CHANNEL_ID);

	/* Calculate the temperature from the ADC value*/
	temp_value = (uint8)(((uint32)adc_value*SENSOR_MAX_TEMPERATURE*ADC_Ref_Voltage_lm35 )/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT_VALUE));

	return temp_value;
}

