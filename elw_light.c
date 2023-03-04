#include "elw_light.h"
#include "fsl_adc16.h"

/* the light sensor is connected to ADC0 (channel 3) */
#define ADC_BASE_ADDR      ADC0
#define ADC_CHANNEL_GROUP  0U
#define ADC_CHANNEL        3U
#define ADC_CALIBRATE      0

void elw_light_init(void)
{
    adc16_config_t adc16ConfigStruct;

    ADC16_GetDefaultConfig(&adc16ConfigStruct);
    ADC16_Init(ADC_BASE_ADDR, &adc16ConfigStruct);
    ADC16_EnableHardwareTrigger(ADC_BASE_ADDR, false);

#if ADC_CALIBRATE == 1
    ADC16_DoAutoCalibration(ADC_BASE_ADDR);
#endif
}

uint32_t elw_light_read(void)
{
    adc16_channel_config_t channel_config;

    channel_config.channelNumber = ADC_CHANNEL;
    channel_config.enableInterruptOnConversionCompleted = false;
    channel_config.enableDifferentialConversion = false;

    ADC16_SetChannelConfig(ADC_BASE_ADDR, ADC_CHANNEL_GROUP, &channel_config);

    while (0U == (kADC16_ChannelConversionDoneFlag &
            ADC16_GetChannelStatusFlags(ADC_BASE_ADDR, ADC_CHANNEL_GROUP)));

    return ADC16_GetChannelConversionValue(ADC_BASE_ADDR, ADC_CHANNEL_GROUP);
}
