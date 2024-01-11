#include <xc.h>
#include <pic18f4520.h>
#define _XTAL_FREQ 1000000

#pragma config OSC = INTIO67    // Oscillator Selection bits
#pragma config WDT = OFF        // Watchdog Timer Enable bit 
#pragma config PWRT = OFF       // Power-up Enable bit
#pragma config BOREN = ON       // Brown-out Reset Enable bit
#pragma config PBADEN = OFF     // Watchdog Timer Enable bit 
#pragma config LVP = OFF        // Low Voltage (single -supply) In-Circute Serial Pragramming Enable bit
#pragma config CPD = OFF        // Data EEPROM?Memory Code Protection bit (Data EEPROM code protection off)

int buffer = 21;
int counter = 50;
int status = 1;
int start = 0;
int statusSetting = 0;
int convertion (int degit);
int initializeTimer (int a);

void __interrupt(high_priority) H_ISR(){
    if(PIR1bits.TMR2IF == 1){
        if (start == 0) {
            if (buffer == 0) {
                start = 1;
                LATBbits.LB4 = 1;
                PORTC = 0b11111111;
                PORTD = 0b11111111;
            } else {
                buffer --;
                PORTC = convertion(buffer / 10);
                PORTD = convertion(buffer % 10);
            }
            PIR1bits.TMR2IF = 0;
            return;
        }
        
        if (PORTAbits.RA0 == 0) {
            counter = initializeTimer (status);
            PORTC = convertion(counter / 10);
            PORTD = convertion(counter % 10);
            statusSetting = 0;
            PIR1bits.TMR2IF = 0;
            LATAbits.LA1 = 0;
            return;
        } 
        if (PORTAbits.RA0 == 1) {
            if (statusSetting == 0) {
                statusSetting = 1;
                status ++;
            }
            LATAbits.LA1 = 0;
            if (counter == 0){
                LATAbits.LA1 = 1;
                status = 1;
                //__delay_ms(250);
            } else {
                counter --;
            }
            PORTC = convertion(counter / 10);
            PORTD = convertion(counter % 10);
        }
        PIR1bits.TMR2IF = 0;
    }
    return;
}

void main(void)
{
    ADCON1 = 0x0f;
    TRISAbits.RA0 = 1; // receive signal
    TRISAbits.RA1 = 0; // send signal
    PORTAbits.RA0 = 0;
    LATAbits.LA1 = 0;
    TRISBbits.RB4 = 0;
    LATBbits.LB4 = 0;
    TRISC = 0;
    TRISD = 0;
    RCONbits.IPEN = 1;
    INTCONbits.GIE = 1;
    PIR1bits.TMR2IF = 0;
    IPR1bits.TMR2IP = 1;
    PIE1bits.TMR2IE = 1;
    T2CON = 0b11111111;
    PR2 = 244;
    
    OSCCONbits.IRCF = 0b010;
    
    while(1){
        
    }
    return;
}

int convertion (int degit) {
    switch(degit) {
        case 0:
            degit = 0b00111111;
            break;
        case 1:
            degit = 0b00000110;
            break;
        case 2:
            degit = 0b01011011;
            break;
        case 3:
            degit = 0b01001111;
            break;
        case 4:
            degit = 0b01100110;
            break;
        case 5:
            degit = 0b01101101;
            break;
        case 6:
            degit = 0b01111101;
            break; 
        case 7:
            degit = 0b00000111;
            break;
        case 8:
            degit = 0b01111111;
            break;
        case 9:
            degit = 0b01101111;
            break;
    }
    
    return degit;
}

int initializeTimer (int a) {
    int b;
    switch(a) {
        case 1:
            b = 90;
            break;
        case 2:
            b = 80;
            break;
        case 3:
            b = 70;
            break;
        case 4:
            b = 60;
            break;
        case 5:
            b = 50;
            break;
        default:
            b = 50;
            break;
    }
    return b;
}