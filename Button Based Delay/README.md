# Button Blink
This is a relatively straight forward program that simply toggles two on-board LEDs. It was built in CCS version 8.1.0.00011, and the code was compiled using GCC version 7.3.1.24 on Linux

## MSP430G2553
For this board, the code sets all GPIO's to outputs to 0, and toggles waits for a button input on pin P1.3. Once the button is pressed, the LED is turned on, and a counter begins incrementing. When the button is released, the counter is stopped. A new counter increments. When the new counter equals the old counter value, the LED is toggled. This provides a 50% duty cycle square wave with a period very close to what was provided by the button (in this case, within 10000 clock cycles). Instead of delay_cycles, this program uses the timer module for delays.

In layman's terms, light blinks and you say how fast. 
## MSP430F5529
For this board, the code sets all GPIO's to outputs to 0, and toggles waits for a button input on pin P1.1.
This is done exactly like the program on the MSP430G2553 board, except it toggles an LED on P1.0.
