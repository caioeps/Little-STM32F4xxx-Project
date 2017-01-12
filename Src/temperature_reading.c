#include "temperature_reading.h"

/*
 * Função para criar nova medição
 * Como utilizar:
 *   float temp;
 *   TemperatureReading temp_reading = TEMPERATURE_READING_new(&hadc1);
 *   TEMPERATURE_READING_start(temp_reading);
 *   temp_reading = TEMPERATURE_READING_get_temperature(temp_reading);
 *   TEMPERATURE_READING_end(temp_reading);
 */
TemperatureReading* TEMPERATURE_READING_new(ADC_HandleTypeDef *adc_handler)
{
	TemperatureReading *temp_reading = (TemperatureReading* ) malloc(sizeof(TemperatureReading));

	temp_reading->adc_handler = adc_handler;

	return temp_reading;
}

/*
 * Prepara para iniciar as leituras.
 */
void TEMPERATURE_READING_start(TemperatureReading *temp_reading)
{
	HAL_ADC_Start(temp_reading->adc_handler);
	HAL_ADC_PollForConversion(temp_reading->adc_handler, 100);
}

/*
 * Termina as leituras.
 */
void TEMPERATURE_READING_end(TemperatureReading *temp_reading)
{
	HAL_ADC_Stop(temp_reading->adc_handler);
	TEMPERATURE_READING_clear_reading(temp_reading);
}

/*
 * Pega a leitura do sensor e a retorna em float.
 */
float TEMPERATURE_READING_get_temperature(TemperatureReading *temp_reading)
{
	uint32_t reading;
	float temperature;

	reading     = HAL_ADC_GetValue(temp_reading->adc_handler);
	temperature = TEMPERATURE_READING_convert_reading_to_celsius(temp_reading);

	return temperature;
}

/*
 * Transforma a leitura em string para poder ser impressa.
 */
char* TEMPERATURE_READING_temperature_to_string(TemperatureReading *temp_reading)
{
	char reading[8];

	sprintf(reading, "%.3f", temp_reading->temperature);

	return reading;
}

/*
 * Não utilizar essas funções abaixo fora desse arquivo.
 */
float TEMPERATURE_READING_convert_reading_to_celsius(TemperatureReading *temp_reading)
{
	return (0.056166 * temp_reading->temperature - 55);
}

void TEMPERATURE_READING_clear_reading(TemperatureReading *temp_reading)
{
	free(temp_reading);
}
