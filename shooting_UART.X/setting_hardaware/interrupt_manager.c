#include <xc.h>

void INTERRUPT_Initialize (void)
{
//    RCONbits.IPEN = 1;      //enable Interrupt Priority mode
//    INTCONbits.GIEH = 1;    //enable high priority interrupt
//    INTCONbits.GIEL = 1;     //disable low priority interrupt
    RCONbits.IPEN = 1; // Interrupt Priority Enable bit
    INTCONbits.INT0F = 0;
    INTCONbits.INT0E = 1;
    INTCONbits.GIE = 1;
}

