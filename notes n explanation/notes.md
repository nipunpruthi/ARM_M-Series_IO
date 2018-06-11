# Notes:
1. The regular function of a pin is to perform I/O, however, most pins have an alternative function.
   e.g. PA1 and PA0 can be either regular parallel port or an asynchronous serial port(UART).

1. The ability to manage time as an input measurement and an output parameter has made a significant impact on the market share growth of micro-controller.

3. JTAG(Joint Test Action Group) is a standard test access port used to program and debug micro-controller board.
   JTAG uses 5 pins.

4.  PINS on TM4C can be assigned to as many as eight different I/O function. (Digital I/O, Analog I/O, timer or Serial I/O).

5. Two buses used for I/O. Digital I/O is connected to both.

6. Each pin has a configuration bit in the GPIOAMSEL register. We set this port pin to connect the port pin to the ADC or analog comparator.

7. For Digital function each pin also has four bits in GPIOPCTL register, which we set to specify the alternative function
   for that pin.(**PC0 to PC3 are reserved for JTAG debugger**)

> Notice, most alternate function modules (e.g., U0Rx) only exist on one pin (PA0). While other functions could be mapped 
   to two or three pins (e.g., CAN0Rx could be mapped to one of the following: PB4, PE4, or PF0.)

> If we wished to use UART7 on pins PE0 and PE1, we would set bits 1,0 in the GPIO_PORTE_DEN_R register (enable digital), 
   clear bits 1,0 in the GPIO_PORTE_AMSEL_R register (disable analog), set the PMCx bits in the GPIO_PORTE_PCTL_R register 
   for PE0, PE1 to 0001 (enable UART functionality), and set bits 1,0 in the GPIO_PORTE_AFSEL_R register 
   (enable alternate function).

> If we wished to sample an analog signal on PD0, we would set bit 0 in the alternate function select register, clear bit 0
    in the digital enable register (disable digital), set bit 0 in the analog mode select register (enable analog), and 
    activate one of the ADCs to sample channel 7.
