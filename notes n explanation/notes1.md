# Notes2
1. PA4 - Connected to switch 4.
   PA2 - Connected to LED.

2. USB interface uses PD4 and PD5.

3. The launchpad connects PB6 to PD0 and PB7 to PD1.
   If you wish to use both PB6 and PD0, you will 
   need to remove the R9 resistor. Similarly, to use both PB7 and PD1, remove the R10 resistor.

4. Read about pull up register (https://filderbaer.wordpress.com/2014/12/30/2-gpio-programming/)
   or simply (https://learn.sparkfun.com/tutorials/pull-up-resistors).


5. Switches uses pull-up register, hence are negative logic and require activation of internal pull-up register.
   (In particular, set bits 0 and 4 in GPIO_PORTF_PUR_R register)

// R1, R13 connect PF0, PF4 to SW2,SW1 
// R2, R11, R12 connects PF1, PF2, PF3 to the 3-color LED
// R25, R29 connect PB1, PB0 to the USB

6. To use LED, make PF1, PF2, PF3 output pin and output a one.