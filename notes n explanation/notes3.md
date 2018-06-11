# Notes3

``` PortF Init```
> Use datasheet to get the address of:
1. DIR Register (direction)
2. DEN Register (Digital Enable)
3. Port Clock
4. Lock Register *Unlocking is only needed for pins PC0-3, PD7 and PF0.*
5. Port Control Register.(allow changes to PF4-0) See screen shot and data sheet.
6. AM_SEL AnalogMode
7. AF_SEL AlternateFunction
8. PullUp Register

## Steps
1. Activate the clock of the Port.
2. Unlock the port; unlocking is needed only for pins PC0-3, PD7 and PF0.
3. Disable analog function of the pin
4. Clear bits in **PCTL** to select **regular digital** function.
5. Set its direction register.
6. Clear bit in alternate direction register.
7. Enable Digital Register.