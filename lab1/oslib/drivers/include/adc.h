#ifndef _ADC_H_
#define _ADC_H_

#include "board.h"

typedef void (*OnSample)(uint32 channel, uint32 val);

/* adc_init
 *   intialize ADC
 */
int adc_init(ADC *adc, OnSample cb);

/* adc_channel_enable
 *   set up adc channel
 */
int adc_channel_enable(ADC *adc, uint32 channel);

/* adc_channel_sample
 *   sample the specified channel and generate an interrupt when it is done
 */
int adc_channel_sample(ADC *adc, uint32 channel);

#endif
