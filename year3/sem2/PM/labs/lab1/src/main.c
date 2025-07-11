#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "./usart.h"

#define CLOCK_SPEED 12000000
#define BAUD 28800
#define MYUBRR CLOCK_SPEED/16/BAUD-1

volatile unsigned int timer0_millis = 0;

// returns the number of milliseconds since the program started
unsigned int millis() {
    return timer0_millis;
}

ISR(TIMER0_COMPA_vect)
{
    // cod întrerupere
    timer0_millis++;
}

ISR(INT0_vect)
{

    if ((PINB & (1 << PB2)) == 0){
     // întrerupere generată de pinul PB2
        USART0_print("Button 1 pressed\n");

  }
}

ISR(PCINT1_vect)
{
    USART0_print("Button 2 pressed\n");
}

void init_timer0()
{
    TIMSK0 |= (1 << OCIE0A);
}

int main() {
    /* Setăm pinul 7 al portului D ca pin de ieșire. */
    DDRD |= (1 << PD7); // green output
    DDRB |= (1 << PB3); // blue output
    DDRD |= (1 << PD5); // red output

    DDRB &= ~(1 << PB2); // button input
    PORTB |= (1 << PB2);

    DDRD &= ~(1 << PD6); // button input
    PORTD |= (1 << PD6);

    USART0_init(MYUBRR);

    // Set up Timer0
    TCCR0A |= (1 << WGM01);
    OCR0A   =  188;
    TCCR0B |= (1 << CS01) | (1 << CS00);

    // Set up interrupt for button 1
    EICRA |= (1 << ISC11);
    EICRA |= (1 << ISC10);
    PCICR |= (1 << PCIE1);
    EIMSK |= (1 << INT0);
    PCMSK1 |= (1 << PCINT10);

    char data[100];

    sei();

    init_timer0();

    long ts = 0;

    while (1) {
        // if (millis() - ts > 1000) {
        //     ts = millis();
        //     USART0_print("salut\n");
        // }
    }

    cli();

    return 0;
}
