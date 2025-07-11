#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "usart.h"
#include "adc.h"
#include "task3.h"

static volatile uint8_t print = 0;
static volatile uint16_t adc_value = 0;

// TODO [task3]: Implement the following function to auto-trigger the ADC conversion
void adc_auto_trigger_init(void) {
  ADCSRA |= (1 << ADEN); // Enable ADC
  ADCSRA |= (1 << ADATE); // Enable auto-triggering
  ADCSRA |= (1 << ADIE); // Enable ADC interrupt
  ADCSRB |= (1 << ADTS0) | (1 << ADTS2); // Timer1 compare match
}

// TODO [task3]: Implement the following function to configure the ADC channel
// HINT: similar to myAnalogRead function in adc.c
void configure_adc_channel(uint8_t channel) {
  ADMUX &= 0b11100000; // clear the old channel value
  ADMUX |= channel; // select the new channel in ADMUX
}

//  TODO [task3]: Interrupt Service Routine for ADC conversion complete
ISR(ADC_vect) {
  adc_value = ADC; // Read the ADC value
  TIFR1     = ( 1<<OCF1B ); // Clear the Timer1 compare match flag
  print = 1; // Set the print flag
}

// TODO [task3]: Interrupt Service Routine for Timer1 compare match
ISR(TIMER1_COMPA_vect) {
}

// Timer1 configured to trigger ISR every 1 second
void timer1_init(void) {
  // Set the Timer Mode to CTC
  TCCR1B |= (1 << WGM12);

  // Set the value that you want to count to
  OCR1A = 46875;

  // Start the timer with a prescaler of 256
  TCCR1B |= (1 << CS12);

  // Enable the compare match interrupt
  TIMSK1 |= (1 << OCIE1A);
}

void task3(void) {
  timer1_init();
  configure_adc_channel(0);
  adc_auto_trigger_init();

  while (1) {
    if (print) {
      // Print the ADC value to the serial
      char adc_value_print[50];
      sprintf(adc_value_print, "Sensor value: %d\n", adc_value);
      USART0_print(adc_value_print);

      print = 0;
    }
  }
}