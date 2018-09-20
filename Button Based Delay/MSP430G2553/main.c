#include <msp430.h>

#define BUT1 0
/**
 * main.c
 */
void main(void){
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	int counter=0,delayval=0;
	P1DIR = 0xf7;//11110111
	P2DIR = 0xff;
    P1OUT = 0x00;
    P2OUT = 0x00;
    P1OUT = 0x00;
	while(1){
        if(counter == 0)
            P1OUT ^= BIT0;
        counter++;
        __delay_cycles(10000);
        if(counter >= delayval)
            counter=0;
		if(!(P1IN & BIT3)){
			delayval=0;
			counter=0;
            P1OUT |= BIT0;
			while(!(P1IN & BIT3)){
				delayval++;
	    		__delay_cycles(10000);
	    	}
            P1OUT &= ~(1<<BIT0);
		}

	}

}
