#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "timers.h"

/** Allocates the system ticks counter (milliseconds since boot) */
volatile unsigned int systicks = 0;


void Timer0_init_pwm()
{
    /* TODO task 1: PWM bluez! */
    // set WGM to 0b011 = 0x3 for fast PWM
    TCCR0A = (1 << WGM00) | (1 << WGM01);
    TCCR0B &= ~(1 << WGM02);

    // set to inverting output (COM0B == 0b11)
    TCCR0A |=  (1 << COM0A0) | (1 << COM0A1);

    // set prescalers to 64 (CS = 0b011)
    TCCR0B |= (1 << CS00) | (1 << CS01);
    TCCR0B &= ~(1 << CS02);

    // set duty cycle to 0%
    OCR0A = 0;
}

void Timer1_init_pwm()
{
    /* We must choose Fast PWM 8-bit, WGMn[3:0] = 0b0101 */
    /* Note: WGM11 and WGM10 are on TCCR1A, while WGM12 and WGM13 are on TCCR1B! */
    TCCR1A = (1 << WGM10);
    TCCR1B = (1 << WGM12);
    /* set COM1A to inverting output: COM1A[1:0] = 0b11 */
    TCCR1A |= (1 << COM1A1) | (1 << COM1A0);
    /* Use 64 prescaler: CS1[2:0] = 0b011 */
    TCCR1B |= (1 << CS10) | (1 << CS11);
    /* set duty cycle to 0%; note that we're using 8-bit mode, so TOP = 255 */
    OCR1A = 0;
}

void Timer1_init_ctc()
{
    /* TODO task 4 (bonus): use CTC mode to play tones (as 50% rectangular waves) */
    /* Clear them up, just to be sure ;) */
    TCCR1A = 0;
    TCCR1B = 0;
    /* Set CTC mode: WGM1[3:0] = 0b0100 */
    TCCR1B |= (1 << WGM12);
    /* Use 64 prescaler: CS1[2:0] = 0b011 */
    TCCR1B |= (1 << CS10) | (1 << CS11);
    /* Set TOP value for 1kHz (1ms) */
    OCR1A = 188;
    OCR1B = 94;
    /* Enable interrupt on compare match */
    TIMSK1 = (1 << OCIE1A);


}

void Timer2_init_systicks()
{
    TCCR2A = (1 << WGM01); /* WGM => CTC mode */
    TCCR2B = (1 << CS22); /* Prescaler => 64 */
    OCR2A  = 188; /* 12MHz / 64 => 187.5 kHz */
    TIMSK2 = (1 << OCIE2A); /* interrupt when counter reaches OCR2A == 188 */

    /* TODO task 3: also enable COMPB interrupt and set the desired compare
     * value */
    OCR2B = 188;
    TIMSK2 |= (1 << OCIE2B);
}

/** Timer 2 COMP_A interrupt service handler */
ISR(TIMER2_COMPA_vect)
{
    /* Will get called [almost] once every 1ms! */
    systicks++;
    /* Note: the timer is in Clear Timer on Compare Match mode, so it will
     * automatically reset itself back to 0! */

    /* TODO task 3: make your virtual PWM output (fill phase) */
    PORTD &= ~(1 << PD7);
}

/** TODO task 3: Timer 2 COMPB interrupt service handler */
ISR(TIMER2_COMPB_vect) {
    PORTD |= (1 << PD7);
}

