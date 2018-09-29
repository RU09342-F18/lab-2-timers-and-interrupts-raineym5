#include <msp430.h>


/**
 * main.c
 */
unsigned volatile int delayval = 7, counter=0, butpress=0;//10 Hz

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
        P1IFG &= ~BIT1;
        if(P1IES & BIT1){

            P1IES &= ~BIT1;//enable logic high-low interrupt

            P1OUT |= BIT0;//turn on LED
            TA0R = 0;//set timer A0 to 0 (not needed but it gives cleaner operation)
            delayval=0;//set delayval to 0
            butpress=1;//set state machine bit
        }else{
            P1IES |= BIT1;//set low-high button interrupt
            P1OUT &= ~BIT0;//disable output
            butpress=0;
            counter=0;
        }

}
#pragma vector=TIMER0_B0_VECTOR         //indicate interrupt vector being used
__interrupt void Timer_B(void){

    TB0CCTL0 &= ~CCIFG;
    TB0CTL &= ~TBIFG;//disable interrupts
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
    counter=0;
    P1IE |= BIT1; // P1.3 interrupt enabled
    P1IES |= BIT1;//interrupt edge select set so the interrupt fires on logic high-low
    P1IFG &= ~BIT1; // P1.3 IFG cleared
    TB0CTL = (TBSSEL1)|(MC0);
    TB0CCR0 = 8192;               //set value for CCR0 interrupt to fire
    while(1){
        __enable_interrupt();
    }

}
