#include <stdint.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#include "adc.h"

typedef struct
{
	float temperature;
	ADC_HandleTypeDef *adc_handler;
} TemperatureReading;

void  TEMPERATURE_READING_start(TemperatureReading *temp_reading);
void  TEMPERATURE_READING_end(TemperatureReading *temp_reading);
float TEMPERATURE_READING_get_temperature(TemperatureReading *temp_reading);
char* TEMPERATURE_READING_temperature_to_string(TemperatureReading *temp_reading);
float TEMPERATURE_READING_convert_reading_to_celsius(TemperatureReading *temp_reading);
void  TEMPERATURE_READING_clear_reading(TemperatureReading *temp_reading);
