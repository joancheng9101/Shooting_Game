#include "setting_hardaware/setting.h"
#include <stdlib.h>
#include "stdio.h"
#include "string.h"
#define _XTAL_FREQ 1000000
// using namespace std;

char str[200];
int score = 0;
int state = 0;
int stop = 0;
int down = 0;
int d1 = 0;
int d2 = 0;
int d3 = 0;
int d4 = 0;
int d5 = 0;
int d6 = 0;
int ready =0;
int button = 0;

void add_score(void){
    switch(state){
        case(0):
            score = 0;
            break;
        case(1):
            score++;
            break;
        case(2):
            score += 2;
            break;
        case(3):
            score += 3;
            break;
        case(4):
            score += 4;
            break;
        default :
            score += 4;
            break;
    }
    strcpy(str,"\rscore : ");
    UART_Write_Text(str);
    ClearBuffer();
    sprintf(str,"%d",score);
    UART_Write_Text(str);
    ClearBuffer();
}

void main(void) 
{
    SYSTEM_Initialize() ;
    LATDbits.LD0 = 1; 
    __delay_ms(100);
    LATDbits.LD0 = 0;
    strcpy(str,"Welcome to the shooting game!\n\r");
    UART_Write_Text(str);
    ClearBuffer();
    strcpy(str,"Press the button to start shooting!\n\r");
    UART_Write_Text(str);
    ClearBuffer();
    strcpy(str,"Don't forget to keep an eye on the time!\n\r");
    UART_Write_Text(str);
    ClearBuffer();
    score = 0;
    button = 1;
    while(1) {
        if(down == 6){
            strcpy(str,"\n\rGood Job !\n\r");
            UART_Write_Text(str);
            ClearBuffer();
            strcpy(str,"Press the button to continue the challenge!\n\r");
            UART_Write_Text(str);
            ClearBuffer();
            strcpy(str,"Don't forget to keep an eye on the time!\n\r");
            UART_Write_Text(str);
            ClearBuffer();
            stop = 0;
            down = 0;
            ready = 0;
            button = 1;
            LATDbits.LD1 = 0; 
             __delay_ms(5000);
            LATDbits.LD0 = 1;
            __delay_ms(100);
            LATDbits.LD0 = 0; 
        }
        if(stop == 1 && down != 6){
            strcpy(str,"\rGame Over !\n\r");
            UART_Write_Text(str);
            ClearBuffer();
            strcpy(str,"Press the button to restart!\n\r");
            UART_Write_Text(str);
            ClearBuffer();
            strcpy(str,"Don't forget to keep an eye on the time!\n\r");
            UART_Write_Text(str);
            ClearBuffer();
            stop = 0;
            down = 0;
            score = 0;
            state = 0;
            ready = 0;
            button = 1;
            LATDbits.LD1 = 0; 
             __delay_ms(5000);
            LATDbits.LD0 = 1; 
            __delay_ms(100);
            LATDbits.LD0 = 0;
        }
        if(PORTBbits.RB1 == 1 && stop == 0){
            stop = 1;
            __delay_ms(1000);
        }
        if(PORTAbits.RA0 == 0 && stop == 0 && d1 == 0 && ready==1){
            d1 = 1;
            down ++;
            add_score();
        }
         if(PORTAbits.RA1 == 0 && stop == 0 && d2 == 0 && ready==1){
            d2 = 1;
            down ++;
            add_score();
        }
         if(PORTAbits.RA2 == 0 && stop == 0 && d3 == 0 && ready==1){
            d3 = 1;
            down ++;
            add_score();
        }
        if(PORTAbits.RA3 == 0 && stop == 0 && d4 == 0 && ready==1){
            d4 = 1;
            down ++;
            add_score();
        }
        if(PORTAbits.RA4 == 0 && stop == 0 && d5 == 0 && ready==1){
            d5 = 1;
            down ++;
            add_score();
        }
        if(PORTAbits.RA5 == 0 && stop == 0 && d6 == 0 && ready==1){
            d6 = 1;
            down ++;
            add_score();
        }
    }
    return;
}

void __interrupt(high_priority) Hi_ISR(void)
{
    if(INTCONbits.INT0F == 1){
        if(button){
            strcpy(str,"START\n\r");
            UART_Write_Text(str); 
            ClearBuffer();
            strcpy(str,"\rscore : ");
            UART_Write_Text(str);
            ClearBuffer();
            sprintf(str,"%d",score);
            UART_Write_Text(str);
            ClearBuffer();
            //LATDbits.LD0 = 0; 
            ready = 1;
            stop =0;
            if(state < 5){
                state ++;
                d1 = 0;
                d2 = 0;
                d3 = 0;
                d4 = 0;
                d5 = 0;
                d6 = 0;
            }else{
                d1 = 0;
                d2 = 0;
                d3 = 0;
                d4 = 0;
                d5 = 0;
                d6 = 0;
            }
            LATDbits.LD1 = 1; 
            INTCONbits.INT0F = 0;
            button = 0;
        }else{
            INTCONbits.INT0F = 0;
        }
    }
}