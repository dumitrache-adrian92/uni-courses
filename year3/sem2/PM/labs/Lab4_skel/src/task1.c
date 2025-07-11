#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "usart.h"
#include "adc.h"
#include "task1.h"

void task1(void) {
  while (1) {
    // TODO [task1]: Use the previous defined function to read the ADC
    // value of the temperature sensor (PA0) and print it to the serial
    uint16_t adc_value = myAnalogRead(PA0);
    char adc_value_print[50];
    sprintf(adc_value_print, "ADC value: %d\n", adc_value);
    USART0_print(adc_value_print);

    // Delay for 1 second
    _delay_ms(1000);
  }
}