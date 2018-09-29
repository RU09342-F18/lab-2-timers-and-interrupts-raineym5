#include <msp430.h>


/**
 * main.c
 * MOST OF THIS IS PSEUDO-CODE I WILL UPDATE THIS TOMORROW
 */
unsigned volatile int delayval = 7;counter=0;//10 Hz

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
        P1IFG &= ~BIT3;
        //if bit selection is low to high
        P1OUT |= BIT0;
        delayval=0;
        counter=0;
        //reset timer

        //else
        P1OUT &= ~(1<<BIT0);

        //invert bit selection for but0


}
#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer_A0(void){
    //disable interrupts
    delayval++
    if(delayval == 100)
        P1OUT ^= 0x01;

}
void main(void)
{
    P1DIR = 0xf7;//11110111
    P2DIR = 0xff;
    P1OUT = 0x00;
    P2OUT = 0x00;
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1IE |= BIT3; // P1.3 interrupt enabled
    P1IES |= BIT3;
    P1IFG &= ~BIT3; // P1.3 IFG cleared
    while(1){
        __enable_interrupt();
    }

}
