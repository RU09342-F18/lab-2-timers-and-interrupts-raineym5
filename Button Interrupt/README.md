# Button Blink
This is a straight forward program that simply toggles two on-board LEDs. It was built in CCS version 8.1.0.00011, and the code was compiled using GCC version 7.3.1.24 on Linux

## MSP430G2553
For this board, the code sets all GPIO's to outputs to 0, and toggles waits for a button input on pin P1.3. On the logic high to low transition, an interrupt is fired and the ISR is executed. In the ISR there is a loop that counts until the button is released. This is typically a no-no, but since this is the only interrupt being used on the microcontroller in this program, it is safe to do so.

In layman's terms, light blinks and you say how fast. Using interrupts this time. neat.
## MSP430F5529
For this board, the code sets all GPIO's to outputs to 0, and toggles waits for a button input on pin P1.3. Everything else is the same on this board.
