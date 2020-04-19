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

enum States{start, wait, s0, s0release, s1, s1release, reset} state;

unsigned char but1 = 0x00;
unsigned char but2 = 0x00;
unsigned char but3 = 0x00;
unsigned char lock = 0x00;
unsigned char tmpB = 0x00;

void Tick() {
	
	switch(state) {
		case start: 
			state = wait; 
		break;
		case wait:
			if((PINA & 0x07) == 0x01 || (PINA & 0x07) == 0x02 || (PINA & 0x07) == 0x04) {
				if(but3 == 0x04)
					state = s0;
				else if(lock == 0x80)
					state = reset;
				else
				state = wait;
			}
			else
				state = wait;
		break;
		case s0:
			if((PINA & 0x07) == 0x01 || (PINA & 0x07) == 0x02 || (PINA & 0x07) == 0x04) {
				if(but3 == 0x00)
					state = s0release;
				else if(lock == 0x80)
					state = reset;
				else
					state = s0;
			}
			else
				state = s0;

		break;
		case s0release:
			if((PINA & 0x07) == 0x01 || (PINA & 0x07) == 0x02 || (PINA & 0x07) == 0x04) {
				if(but2 == 0x02)
					state = s1;
				else if(lock == 0x80)
					state = s1release;
				else
				state = s0release;
			}
			else
				state = s0release;

		break;
		case s1:
			if((PINA & 0x07) == 0x01 || (PINA & 0x07) == 0x02 || (PINA & 0x07) == 0x04) {
				if(but2 == 0x00)
					state = s1release;
				else if(lock == 0x80)
					state = reset;
				else
					state = s1;
			}
			else
				state = s1;

		break;
		case s1release:
			if(lock == 0x80)
				state = reset;
			else
				state = s1release;
		break;
		case reset:
			if(lock == 0x00)
				state = wait;
			else
				state = reset;
		break;

	}

	switch(state) {
		case start: tmpB = 0x00; break;
		case wait: tmpB = 0x00; break;
		case s0: break;
		case s0release: break;
		case s1: tmpB = 0x01; break;
		case s1release: tmpB = 0x01; break;
		case reset: tmpB = 0x00;  break;




	}
	
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    
    state = start;
    
    tmpB = 0x00;
    
    while (1) {
	but1 = PINA & 0x01;
	but2 = PINA & 0x02;
	but3 = PINA & 0x04;
	lock = PINA & 0x80;
	Tick();
	PORTB = tmpB;
    }
    return 1;
}
