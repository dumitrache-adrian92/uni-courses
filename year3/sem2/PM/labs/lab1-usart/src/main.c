#include <util/delay.h>
#include <usart.h>

#define CLOCK_SPEED 12000000
#define BAUD 28800
#define MYUBRR CLOCK_SPEED/16/BAUD-1

#define MORSE_LUNG  3
#define MORSE_SCURT 1
#define ON '1'
#define OFF '0'
#define RED 'r'
#define GREEN 'g'
#define BLUE 'b'
#define PIETON "pieton"

static char state = OFF;

/* Literele alfabetului in cod Morse */
char* morse_alphabet[] = {
    (char*)"13",    // a
    (char*)"3111",  // b
    (char*)"3131",  // c
    (char*)"311",   // d
    (char*)"1",     // e
    (char*)"1131",  // f
    (char*)"331",	// g
    (char*)"1111",	// h
    (char*)"11",	// i
    (char*)"1333",	// j
    (char*)"313",	// k
    (char*)"1311",	// l
    (char*)"33",	// m
    (char*)"31",	// n
    (char*)"333",	// o
    (char*)"1331",	// p
    (char*)"3313",	// q
    (char*)"131",	// r
    (char*)"111",	// s
    (char*)"3",	    // t
    (char*)"113",	// u
    (char*)"1113",	// v
    (char*)"133",	// w
    (char*)"3113",	// x
    (char*)"3133",	// y
    (char*)"3311"	// z
};

/* apelati functia pentru a obtine un ton lung/scurt,
 * folosind macro-urile MORSE_LUNG si MORSE_SCURT
 */
void speaker_morse(int tip)
{
    int delay = 1;
    int i;
    DDRD |= (1 << PD4);     // PD4 trebuie sa fie output

    for (i = 0; i < tip * 50 / delay; i++)
    {
        PIND = (1 << PD4);  // alternam starea iesirii
        _delay_ms(1);
    }
}

void USART_exec(unsigned char command) {
    if (command == ON) {
        state = ON;
        PORTD &= ~(1 << PD7);
        PORTD &= ~(1 << PD5);
        PORTB &= ~(1 << PB3);
    } else if (command == OFF) {
        state = OFF;
        PORTD |= (1 << PD7);
        PORTD |= (1 << PD5);
        PORTB |= (1 << PB3);
    } else if (command == RED) {
        PORTD &= ~(1 << PD5);
        PORTD |= (1 << PD7);
        PORTB |= (1 << PB3);
    } else if (command == GREEN) {
        PORTD &= ~(1 << PD7);
        PORTD |= (1 << PD5);
        PORTB |= (1 << PB3);
    } else if (command == BLUE) {
        PORTB &= ~(1 << PB3);
        PORTD |= (1 << PD7);
        PORTD |= (1 << PD5);
    }
}

int main() {

    USART0_init(MYUBRR);

    DDRB  &= ~(1 << PB2);  // set button input
    PORTB |=  (1 << PB2);  // pull-up

    // set leds as outputs
    DDRD  |=  (1 << PD7);
    DDRD  |=  (1 << PD5);
    DDRB  |=  (1 << PB3);

    // turn off all leds
    PORTD |=  (1 << PD7);
    // PORTD |=  (1 << PD5);
    PORTB |=  (1 << PB3);

    // int8_t pressed = 0;

    // while (1) {
    //     int val = PINB & (1 << PB2);

    //     if (!val && !pressed) {
    //         pressed = 1;
    //         USART0_print("Buton apasat\n");
    //     } else if (val && pressed) {
    //         pressed = 0;
    //         USART0_print("Buton eliberat\n");
    //     }

    //     _delay_ms(50);
    // }

    // while (1) {
    //     uint8_t command = USART0_receive();

    //     USART_exec(command);

    //     _delay_ms(50);
    // }

    // while (1) {
    //     uint8_t letter = USART0_receive();

    //     char *morse = morse_alphabet[letter - 'a'];

    //     for (int i = 0; morse[i] != '\0'; i++) {
    //         if (morse[i] == '1') {
    //             speaker_morse(MORSE_SCURT);
    //         } else {
    //             speaker_morse(MORSE_LUNG);
    //         }
    //         _delay_ms(50);
    //     }

    //     _delay_ms(50);
    // }

    char message[7];
    int current_length = 0;
    message[0] = '\0';


    while (1) {
        uint8_t letter = USART0_receive();

        message[current_length] = letter;

        if (PIETON[current_length] != letter) {
            current_length = 0;
            message[0] = '\0';
            USART0_print("cerere incorecta\n");
        } else {
            current_length++;
        }

        if (current_length == 6) {
            PORTD &= ~(1 << PD7);
            _delay_ms(2000);
            PORTD |=  (1 << PD5);
            _delay_ms(5000);
            PORTD |=  (1 << PD7);
            PORTD &= ~(1 << PD5);
            current_length = 0;
            message[0] = '\0';
        }

        _delay_ms(50);
    }

	return 0;
}

// "pieton" -> "comanda"
// "piep" -> "cerere incorecta"