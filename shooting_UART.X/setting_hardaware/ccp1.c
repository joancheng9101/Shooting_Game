#include <xc.h>
#define _XTAL_FREQ 1000000

void CCP1_Initialize() {
     // Timer2 -> On, prescaler -16
    T2CONbits.TMR2ON = 0b1;
    T2CONbits.T2CKPS = 0b10;
    T2CONbits.T2OUTPS = 0b0001;
    CCP1CONbits.CCP1M = 0b1100;
     // CCP1/RC2 -> Output
    TRISC = 0;
    LATC = 0;
    
    // Set up PR2, CCP to decide PWM period and Duty Cycle
    /** 
     * PWM period
     * = (PR2 + 1) * 4 * Tosc * (TMR2 prescaler)
     * = (0x9b + 1) * 4 * 1µs * 32
     * = 0.019968s ~= 20ms
     */
    PR2 = 0x9b;
    
    //-90
    CCPR1L = 0x0b;
    CCP1CONbits.DC1B = 0b10;
     __delay_ms(200);
    
//    TRISCbits.TRISC2=0;	// RC2 pin is output.
//    CCP1CON=9;		// Compare mode, initialize CCP1 pin high, clear output on compare match
//    PIR1bits.CCP1IF=0;
//    IPR1bits.CCP1IP = 1;
}
