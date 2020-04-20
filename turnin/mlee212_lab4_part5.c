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

enum States{start, wait, rel, check, reset, comp} state;

unsigned char lock = 0x00;
unsigned char tmpB = 0x00;
unsigned char seq[] = {0x04, 0x01, 0x02, 0x01};
unsigned char i = 0;

void Tick() {
	
	switch(state) {
		case start: 
			state = wait;
		break;
		case wait:
			if(PINA)
				state = rel;
			else
				state = wait;
		break;
		case rel:
			if((PINA & 0xFF) == 0x00)
				state = check;
			else
				state = rel;
		break;
		case check:
			if(lock == 0x80) 
				state = reset;
			else if (PINA == seq[i])
				if(i == 4) {
					state = comp;
				}
				else {
					i++;
					state = wait;
				}
			else
				state = check;
		break;
		case reset:
			if(PINA == 0x00)
				state = wait;
			else
				i = 0;
				state = reset;
		break;
		case comp:
			state = wait;
		break;
	}

	switch(state) {
		case start: tmpB = 0x00; break;
		case wait: break;
		case rel: break;
		case check: break;
		case reset: tmpB = 0x00; break;
		case comp:
			if(tmpB == 0x01) 
				tmpB = 0x00;
			else
				tmpB = 0x01;
		break;



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
	lock = PINA & 0x80;
	Tick();
	PORTB = tmpB;
    }
    return 1;
}
