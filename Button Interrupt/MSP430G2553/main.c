#include <msp430.h> 


/**
 * main.c
 */
volatile int delayval = 0;counter=0;

void main(void)
{
    P1DIR = 0xf7;//11110111
    P2DIR = 0xff;
    P1OUT = 0x00;
    P2OUT = 0x00;
    P1OUT = 0x00;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    P1IE |= BIT3; // P1.3 interrupt enabled
    P1IFG &= ~BIT3; // P1.3 IFG cleared
    while(1){
        __enable_interrupt(); // enable all interrupts
        if(counter == 0)
            P1OUT ^= BIT0;
        counter++;
        __delay_cycles(10000);
        if(counter >= delayval)
            counter=0;
    }
	
}
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
        P1IFG &= ~BIT3;
        delayval=0;
        counter=0;
        P1OUT |= BIT0;

        while(!(P1IN & BIT3)){
            delayval++;
            __delay_cycles(10000);
        }
        P1OUT &= ~(1<<BIT0);


}
