#include <stdio.h>
#include "myADC.h"
#include "esp_adc/adc_oneshot.h"

adc_oneshot_unit_handle_t adc1_handle;
adc_oneshot_unit_init_cfg_t init_config1 = {
    .unit_id = ADC_MODULE,
    .ulp_mode = ADC_ULP_MODE_DISABLE,
};

adc_oneshot_chan_cfg_t config = {
    .bitwidth = ADC_BITWIDTH_DEFAULT,
    .atten = ADC_ATTEN_DB_12,
};



int myADC_waarde(void)
{
    int getal;
    adc_oneshot_read(adc1_handle, ADC_KANAAL, &getal);
    return getal;
}



void myADC_setup(void)
{
    adc_oneshot_new_unit(&init_config1, &adc1_handle);
    adc_oneshot_config_channel(adc1_handle, ADC_KANAAL, &config);
}