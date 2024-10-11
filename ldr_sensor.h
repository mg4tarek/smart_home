 /******************************************************************************
 *
 * Module: LDR sensor
 *
 * File Name: ldr_sensor.h
 *
 * Description: Header file for the LDR sensor driver
 *
 * Author: Mohamed Gamal
 *
 *******************************************************************************/

#ifndef LDR_SENSOR_H_
#define LDR_SENSOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*
 * Define the ADC channel where the LDR sensor is connected.
 */
#define LDR_SENSOR_CHANNEL_ID         0  // LDR sensor connected to ADC channel 0

/*
 * Define the maximum light intensity percentage the LDR sensor can measure.
 * The light intensity ranges from 0% (darkness) to 100% (maximum light).
 */
#define LDR_SENSOR_MAX_LIGHT_INTENSITY  100  // Maximum light intensity in percentage

/*
 * Define the maximum voltage output from the LDR sensor.
 * This represents the voltage corresponding to complete darkness.
 */
#define LDR_SENSOR_MAX_VOLT_VALUE     2.56  // Maximum output voltage from the LDR sensor


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initiate the LDR sensor.
 */
void LDR_init(void);
/*
 * Description:
 * Function to get the current light intensity percentage from the LDR sensor.
 * It reads the ADC value and calculates the corresponding light intensity (0% to 100%).
 */
uint8 LDR_getLightIntensity(void);

#endif /* LDR_SENSOR_H_ */

