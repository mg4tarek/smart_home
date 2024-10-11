 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: header file for the ATmega16 ADC driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023
/*******************************************************************************
 *                      Type declaration                                   *
 *******************************************************************************/


typedef enum{
	TWO=1, FOUR, EIGHT, SIXTEEN, THIRTY_TWO, SIXTY_FOUR, ONE_HUNDRED_TWENTY_EIGHT
}ADC_Prescaler;

typedef enum{
	AREF, AVCC, Internal_2_56v=3
}ADC_VoltageReference;

typedef struct{
	ADC_VoltageReference ref;
	ADC_Prescaler prescaler;

}ADC_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType * Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 channel_num);

#endif /* ADC_H_ */
