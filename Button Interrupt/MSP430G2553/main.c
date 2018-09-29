#include <msp430.h> 


/**
 * main.c
 */
unsigned volatile int delayval = 7;counter=0;//10 Hz

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
        P1IFG &= ~BIT3;
        delayval=0;
        counter=0;
        P1OUT |= BIT0;

        while(!(P1IN & BIT3)){//counter used for incrememnting delayval. It's bad practice to use loops in interrupts, but since this is the only interrupt firing on this microcontroller in this program, it will not be interrupting another interrupt.
            delayval++;
            __delay_cycles(10000);
        }
        P1OUT &= ~(1<<BIT0);


}
void main(void)
{
    P1DIR = 0xf7;//11110111
    P2DIR = 0xff;
    P1OUT = 0x00;
    P2OUT = 0x00;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    P1IE |= BIT3; // P1.3 interrupt enabled
    P1IES |= BIT3;//interrupt edge select - fires on logic high-low
    P1IFG &= ~BIT3; // P1.3 IFG cleared
    while(1){
        __enable_interrupt(); // enable all interrupts
        if(counter == 0)//toggle LED when counter resets.
            P1OUT ^= BIT0;
        counter++;
        __delay_cycles(10000);
        if(counter >= delayval)//set LED to 0 when max value is reached. greater than or equal to iss used instead of equal to because if the register value changes due to, for example, cosmic rays, you'll want to change the value immediately instead of waiting for it to go to 65565, overflow, and go back up to delayval, and them finaly turn off the LED.
            counter=0;
    }
	
}
