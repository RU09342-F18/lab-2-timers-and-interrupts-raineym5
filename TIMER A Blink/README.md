# Button Blink
This is a straight forward program that simply toggles two on-board LEDs. It was built in CCS version 8.1.0.00011, and the code was compiled using GCC version 7.3.1.24 on Linux

## MSP430G2553
For this board, the code sets all GPIO's to outputs to 0 and initializes timer A0 comparator interrupt. with 65535 as a comparison value. When the ISR is fired, a counter is incremented. When this counter mod 3 == 0, it toggles an LED on P1.0. When the counter mod 5 == 0, it toggles an led on pin p1.4.


## MSP430F5529
For this board, the code does exactly the same thing, except toggling LEDs on pins P1.0 and P4.7.

Modulus is used in this instance for simplicity, and because there is no time constraint for which the code needs to run within. In future implementations, the code will use a counter that compares at 3 and 5 and resets on 5.
