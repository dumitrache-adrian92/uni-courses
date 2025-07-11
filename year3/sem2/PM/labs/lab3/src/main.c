#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "usart.h"
#include "timers.h"
#include "colors.h"
#include "sound.h"

/* Configuration constants: */
#define PM_BAUD 28800

#define RGB_PULSE  1
#define RGB_HSV    2

#define LED_ANIMATION  3
#define SPEAKER_ENABLED 1


/**
 * Initialize the GPIOs of LEDs / speaker etc.
 */
int GPIO_init() {
    /* RGB led directions & default PORTs to 1 (OFF state) */
    DDRB |= (1 << PB3);
    DDRD |= (1 << PD5) | (1 << PD7);
    PORTB |= (1 << PB3);
    PORTD |= (1 << PD5) | (1 << PD7);

    return 0;
}

int main() {
    /* initialize peripheral modules: */
    GPIO_init();
    USART0_init(CALC_USART_UBRR(PM_BAUD));
    USART0_use_stdio();

    if (SPEAKER_ENABLED) {
        Timer1_init_ctc();
    } else {
        Timer1_init_pwm();
    }
    Timer2_init_systicks();
    /* TODO add more *_init_*() calls here? */
    Timer0_init_pwm();

    sei(); /* activate global interrupts */

    printf("It's timer hammer!\n");

    unsigned int last_ping = 0;

    while (1) {
        /* Print alive message */
        if (SYSTICKS_PASSED(last_ping, 3000)) {
            last_ping = systicks;
            printf("Stayin' alive! [ticks=%i]\n", systicks);
        }
        if (LED_ANIMATION == RGB_PULSE) {
            /*
             * Pulse de LEDs based on a triangle wave:
             * y = (P - abs(t % (2*P) - P) )
             * Note: outputs values between [0, 3000]!
             */
            int wave = (3000 - abs(((int)systicks % 6000) - 3000));
            /* rescale [0, 3000] to [0, 255] using ceil(3000 / 255) */
            OCR1A = (wave / 12);

            /* TODO task 1 & 2: do the same for other LEDs */
            wave = (1000 - abs(((int)systicks % 2000) - 1000));
            OCR0A = (wave / 4);

            wave = (94 - abs(((int)systicks % 188) - 94));
            OCR2B = wave;
        } else if (LED_ANIMATION == RGB_HSV) {
            /* TODO task 3: output all different Hue colors */
            uint8_t rgb[3];

            convert_HSV_to_RGB(systicks % 360, 1, 1, rgb);
            OCR1A = rgb[0];
            OCR0A = rgb[2];
            OCR2B = rgb[1];
        }
        if (SPEAKER_ENABLED) {
            /* TODO task 4 (bonus): you know what you have to do ;) */
            if (SYSTICKS_PASSED(last_ping, 1000)) {
                last_ping = systicks;
                // play_melody(surprise_notes, durations, num_notes);
            }
        }
    }

    return 0;
}
