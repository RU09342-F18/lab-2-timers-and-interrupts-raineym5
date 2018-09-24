#include <msp430.h> 


/**
 * main.c
 */
unsigned volatile int counter=0;
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1DIR = 0xff;
    P2DIR = 0xff;
    P1OUT = 0x00;
    P2OUT = 0x00;
    CCTL0 = CCIE;               // CCR0 interrupt enabled
    CCR0 = 65535;
    counter=0;


    TA0CTL = (TASSEL1)|(MC0);

    while(1){
        __enable_interrupt();
    }

}

#pragma vector=TIMER0_A0_VECTOR         //indicate interrupt vector being used
__interrupt void Timer_A(void){


        TA0CCTL0 &= ~CCIFG;
        TA0CTL &= ~TAIFG;
        counter++;
        if(counter%3 == 0)
            P1OUT ^= 0x01;
        if(counter%5 == 0)
            P1OUT ^= 0x40;
        if(counter == 15)
            counter = 0;

}
