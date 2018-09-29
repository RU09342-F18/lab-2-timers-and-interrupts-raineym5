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
    P3DIR = 0xff;
    P4DIR = 0xff;
    P5DIR = 0xff;
    P6DIR = 0xff;
    P7DIR = 0xff;
    P1OUT = 0x01;
    P2OUT = 0x00;
    P3OUT = 0x00;
    P4OUT = 0x00;
    P5OUT = 0x00;
    P6OUT = 0x00;
    P7OUT = 0x00;
    TBCCTL0 = CCIE;               // CCR0 interrupt enabled
    TBCCR0 = 65535;             //set compare 0 timer
    counter=0;


    TB0CTL = (TBSSEL1)|(MC0);

    while(1){
        __enable_interrupt();
    }

}

#pragma vector=TIMER0_B0_VECTOR         //indicate interrupt vector being used
__interrupt void Timer_B(void){


        TB0CCTL0 &= ~CCIFG;
        TB0CTL &= ~TBIFG;
        counter++;
        if(counter%3 == 0)
            P1OUT ^= 0x01;
        if(counter%5 == 0)
            P4OUT ^= 0x80;
        if(counter == 15)
            counter = 0;

}
