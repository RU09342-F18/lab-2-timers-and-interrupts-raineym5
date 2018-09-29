#include <msp430.h>


/**
 * main.c
 */
unsigned volatile int delayval = 7, counter=0, butpress=0;//10 Hz

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
        P1IFG &= ~BIT3;
        if(P1IES & BIT3){

            P1IES &= ~BIT3;//enable logic high-low interrupt

            P1OUT |= BIT0;//turn on LED
            TA0R = 0;//set timer A0 to 0 (not needed but it gives cleaner operation)
            delayval=0;//set delayval to 0
            butpress=1;//set state machine bit
        }else{
            P1IES |= BIT3;//set low-high button interrupt
            P1OUT &= ~BIT0;//disable output
            butpress=0;
            counter=0;
        }

}
#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer_A0(void){
    //disable interrupts
    counter++;
    if(butpress == 1)//state machine bit. if one, number of timer overflows per led blink increases
        delayval++;
    else if(counter >= delayval){
        P1OUT ^= 0x01;
        counter = 0;
    }

}
void main(void)
{
    P1DIR = 0xf7;//11110111
    P2DIR = 0xff;//initialize outputs to 0
    P1OUT = 0x00;
    P2OUT = 0x00;
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1IE |= BIT3; // P1.3 interrupt enabled
    P1IES |= BIT3;//bit selection
    P1IFG &= ~BIT3; // P1.3 IFG cleared
    TA0CTL = (TASSEL1)|(MC0);    //set timer A control bits - source select and mode control
    CCTL0 = CCIE;               // CCR0 interrupt enabled
    CCR0 = 8192;               //set value for CCR0 interrupt to fire
    while(1){
        __enable_interrupt();
    }

}
