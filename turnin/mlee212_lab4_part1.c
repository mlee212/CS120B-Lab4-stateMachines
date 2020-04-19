/*	Author: mlee212
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{start, s_0not, s_0pressed, s_1not, s_1pressed} state;

unsigned char tmpA = 0x00;
unsigned char tmpB = 0x00;

void Tick() {
	
	switch(state) {
		case start: state = s_0not; break;
		case s_0not: 
			if((PINA & 0x01) == 0x01) 
				state = s_0pressed;
			else
				state = s_0not;
			break;
		case s_0pressed: 
			if((PINA & 0x01) == 0x00) 
				state = s_1not;
			else
				state = s_0pressed;
			break;
		case s_1not: 
			if((PINA & 0x01) == 0x01) 
				state = s_1pressed;
			else
				state = s_1not;
			break;
		case s_1pressed:
			if((PINA & 0x01) == 0x01) 
				state = s_0not;
			else
				state = s_1pressed;
			break;
	}

	switch(state) {
		case start: PORTB = 0x01; break;
		case s_0not: PORTB = 0x02; break;
		case s_0pressed: PORTB = 0x02; break;
		case s_1not: PORTB = 0x01; break;
		case s_1pressed: PORTB = 0x01; break;
	}
	
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    
    state = start;
    
    while (1) {
	tmpA = PINA & 0x01;
	Tick();
	PORTB = tmpB;
    }
    return 1;
}
