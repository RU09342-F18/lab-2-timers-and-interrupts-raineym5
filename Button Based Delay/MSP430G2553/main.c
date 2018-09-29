#include <msp430.h>


/**
 * main.c
 */
unsigned volatile int delayval = 7, counter=0, butpress=0;//10 Hz

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
        P1IFG &= ~BIT3;
        if(P1IES && BIT3){

            P1IES |= BIT3;
            P1OUT |= BIT0;
            TAR = 0;
            delayval=0;
            butpress=1;
            counter=0;
        }else{
            P1OUT &= ~(1<<BIT0);
            P1IES &= ~BIT3;
            butpress=0;
        }



}
#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer_A0(void){
    //disable interrupts
    counter++;
    if(butpress)
        delayval++;
    else if(counter >= delayval){
        P1OUT ^= 0x01;
        counter = 0;
    }

}
void main(void)
{
    P1DIR = 0xf7;//11110111
    P2DIR = 0xff;
    P1OUT = 0x00;
    P2OUT = 0x00;
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1IE |= BIT3; // P1.3 interrupt enabled
    P1IES |= BIT3;//bit selection
    P1IFG &= ~BIT3; // P1.3 IFG cleared
    TA0CTL = (TASSEL1)|(MC0);    //set timer A control bits - source select and mode control
    CCTL0 = CCIE;               // CCR0 interrupt enabled
    CCR0 = 65535;               //set value for CCR0 interrupt to fire
    while(1){
        __enable_interrupt();
    }

}
