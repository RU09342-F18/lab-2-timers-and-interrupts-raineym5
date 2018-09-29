#include <msp430.h> 


/**
 * main.c
 */
unsigned volatile int delayval = 50;counter=0;

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
        P1IFG &= ~BIT1;
        delayval=0;
        counter=0;
        P1OUT |= BIT0;

        while(!(P1IN & BIT1)){
            delayval++;
            __delay_cycles(10000);
        }
        P1OUT &= ~(1<<BIT0);


}
void main(void)
{
    P1DIR = 0xfd;
    P2DIR = 0xff;
    P3DIR = 0xff;
    P4DIR = 0xff;
    P5DIR = 0xff;
    P6DIR = 0xff;
    P7DIR = 0xff;
    P1OUT = 0x02;
    P2OUT = 0x00;
    P3OUT = 0x00;
    P4OUT = 0x00;
    P5OUT = 0x00;
    P6OUT = 0x00;
    P7OUT = 0x00;
    P1REN = 0x02;
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1IE |= BIT1; // P1.3 interrupt enabled
    P1IES |= BIT1;
    P1IFG &= ~BIT1; // P1.3 IFG cleared
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
