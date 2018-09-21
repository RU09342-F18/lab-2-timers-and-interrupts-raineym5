#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
    P1DIR = 0xff;
    P2DIR = 0xff;
    P1OUT = 0x00;
    P2OUT = 0x00;
    P1OUT = 0x00;
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    //TACTL = (1<<TASSEL0)|(0x11<<ID0)|(1<<MC0)|()
    //Help, TI documentation sucks. I just need the register names, but names, and what they do
    //TA0R
    //TA0CTL
    //TA0IV
    while(1){
        __enable_interrupt();
    }

}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TimerA0(void){
        TA1CCTL0 &= ~CCIFG;
        TA1CTL &= ~TAIFG;



}
