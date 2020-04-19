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

enum States{start, wait, add, sub, reset, addW, subW} state;

unsigned char but1 = 0x00;
unsigned char but2 = 0x00;
unsigned char sum = 0x00;

void Tick() {
	
	switch(state) {
		case start: 
			state = wait; 
		break;
		case wait:
			if((but1 + but2) == 0x03)
				state = reset;
			else if((but1 + but2) == 0x01)
				state = add;
			else if((but1 + but2) == 0x02)
				state = sub;
			else
				state = wait;
		break;
		case add:
			if((but1 + but2) == 0x03)
				state = reset;
			else
				state = addW;
		break;
		case sub:
			if((but1 + but2) == 0x03)
				state = reset;
			else
				state = subW;

			
		break;
		case reset:
			if((but1 + but2) == 0x00)
				state = wait;
			else
				state = reset;
		break;

		case addW:
			if((but1 + but2) == 0x00)
				state = wait;
			else
				state = addW;
		break;

		case subW:
			if((but1 + but2) == 0x00)
				state = wait;
			else
				state = subW;
		break;


	}

	switch(state) {
		case start: sum = 0x07; break;
		case wait:  break;
		case add: 
			if(sum < 0x09)
				sum = sum + 0x01;
		break;
		case sub:
			if(sum > 0x00)
				sum = sum - 0x01;
		break;
		case reset: sum = 0;  break;
		case addW: break;
		case subW: break;




	}
	
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    
    state = start;
    sum = 7;
    while (1) {
	but1 = PINA & 0x01;
	but2 = PINA & 0x02;
	Tick();
	PORTC = sum;
    }
    return 1;
}
