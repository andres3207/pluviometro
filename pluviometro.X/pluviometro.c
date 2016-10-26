/* 
 * File:   pluviometro.c
 * Author: andres
 *
 * Created on 26 de octubre de 2016, 06:57
 */
// PIC18F45K20 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config CP = OFF         // FLASH Program Memory Code Protection bits (Code protection off)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low Voltage In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection (Code Protection off)
#pragma config WRT = ON         // FLASH Program Memory Write Enable (Unprotected program memory may be written to by EECON control)
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
unsigned i=0;
unsigned dato_an_h,dato_an_l;
unsigned dato_an,dato_an2;

struct{
    unsigned short   R10ml;
    unsigned short   R15ml;
    unsigned short   R20ml;
    unsigned short   R25ml;
    unsigned short   R30ml;
    unsigned short   R35ml;
    unsigned short   R40ml;
    unsigned short   R45ml;
    unsigned short   R50ml;
    unsigned short   R55ml;
    unsigned short   R60ml;
} Rv;

struct{
    unsigned short   L5ml;
    unsigned short   L10ml;
    unsigned short   L15ml;
    unsigned short   L20ml;
    unsigned short   L25ml;
    unsigned short   L30ml;
    unsigned short   L35ml;
    unsigned short   L40ml;
    unsigned short   L45ml;
    unsigned short   L50ml;
    unsigned short   L55ml;
    unsigned short   L60ml;
} limites;


unsigned short Rf1,Rf2;

unsigned vf2;
float tmp;

void Port_Config(void);
void ADC_Config(void);
void Rv_Config(void);

int main(int argc, char** argv) {

    Port_Config();
    Rv_Config();
    ADC_Config();
    dato_an=0;
    while(1){
        i++;
        dato_an2=dato_an;
 if(dato_an2<limites.L5ml){
     PORTC=0;
     PORTB=0;
 }else if(limites.L5ml<dato_an2<limites.L10ml){
     PORTC=1;
     PORTB=0;
 }else if(limites.L10ml<dato_an2<limites.L15ml){
     PORTC=2;
     PORTB=0;
 }else if(limites.L15ml<dato_an2<limites.L20ml){
     PORTC=4;
     PORTB=0;
 }else if(limites.L20ml<dato_an2<limites.L25ml){
     PORTC=8;
     PORTB=0;
 }else if(limites.L25ml<dato_an2<limites.L30ml){
     PORTC=16;
     PORTB=0;
 }else if(limites.L30ml<dato_an2<limites.L35ml){
     PORTC=32;
     PORTB=0;
 }else if(limites.L35ml<dato_an2<limites.L40ml){
     PORTC=64;
     PORTB=0;
 }else if(limites.L40ml<dato_an2<limites.L45ml){
     PORTC=128;
     PORTB=0;
 }else if(limites.L45ml<dato_an2<limites.L50ml){
     PORTC=0;
     PORTB=1;
 }else if(limites.L50ml<dato_an2<limites.L55ml){
     PORTC=0;
     PORTB=2;
 }else{
     PORTC=0;
     PORTB=4;
 }
    }
    return (EXIT_SUCCESS);
}

/********** CONFIGURACIONES *********/

void Port_Config(void){
    TRISAbits.TRISA3=1; // Vref+
    TRISAbits.TRISA2=1; // Vref-
    TRISAbits.TRISA0=1; // Entrada analogica
    TRISC=0;
    TRISB=0;
}

void ADC_Config(void){
    ADCON1=0x8F;
    ADCON0=0x00;
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    PIR1bits.ADIF=0;
    PIE1bits.ADIE=1;
    ADCON0bits.ADON=1;
    ADCON0bits.GO=1;
}

void Rv_Config(void){
    Rv.R10ml=15;
    Rv.R15ml=15;
    Rv.R20ml=15;
    Rv.R25ml=15;
    Rv.R30ml=15;
    Rv.R35ml=15;
    Rv.R40ml=15;
    Rv.R45ml=15;
    Rv.R50ml=15;
    Rv.R55ml=15;
    Rv.R60ml=15;
    Rf1=100;
    Rf2=100;
    
//    tmp=(1023*2*100)/(11*15+200);
    tmp=204600.0/(11.0*15.0+200.0);
    
    limites.L5ml=204600.0/((float)(Rv.R10ml+Rv.R15ml+Rv.R20ml+Rv.R25ml+Rv.R30ml+Rv.R35ml+Rv.R40ml+Rv.R45ml+Rv.R50ml+Rv.R55ml+Rv.R60ml)+200.0);
    limites.L10ml=204600.0/((float)(Rv.R15ml+Rv.R20ml+Rv.R25ml+Rv.R30ml+Rv.R35ml+Rv.R40ml+Rv.R45ml+Rv.R50ml+Rv.R55ml+Rv.R60ml)+200.0);
    limites.L15ml=204600.0/((float)(Rv.R20ml+Rv.R25ml+Rv.R30ml+Rv.R35ml+Rv.R40ml+Rv.R45ml+Rv.R50ml+Rv.R55ml+Rv.R60ml)+200.0);
    limites.L20ml=204600.0/((float)(Rv.R25ml+Rv.R30ml+Rv.R35ml+Rv.R40ml+Rv.R45ml+Rv.R50ml+Rv.R55ml+Rv.R60ml)+200.0);
    limites.L25ml=204600.0/((float)(Rv.R30ml+Rv.R35ml+Rv.R40ml+Rv.R45ml+Rv.R50ml+Rv.R55ml+Rv.R60ml)+200.0);
    limites.L30ml=204600.0/((float)(Rv.R35ml+Rv.R40ml+Rv.R45ml+Rv.R50ml+Rv.R55ml+Rv.R60ml)+200.0);
    limites.L35ml=204600.0/((float)(Rv.R40ml+Rv.R45ml+Rv.R50ml+Rv.R55ml+Rv.R60ml)+200.0);
    limites.L40ml=204600.0/((float)(Rv.R45ml+Rv.R50ml+Rv.R55ml+Rv.R60ml)+200.0);
    limites.L45ml=204600.0/((float)(Rv.R50ml+Rv.R55ml+Rv.R60ml)+200.0);
    limites.L50ml=204600.0/((float)(Rv.R55ml+Rv.R60ml)+200.0);
    limites.L55ml=204600.0/((float)(Rv.R60ml)+200.0);
    limites.L60ml=204600.0/(200.0);
}

/***********************************/


/************* INTERRUPCIONES ***************/
void interrupt interrupciones(void)
{
 if (ADIE && ADIF) {
 ADIF=0;
 dato_an_h=ADRESH;
 dato_an_l=ADRESL;
 dato_an=256*dato_an_h+dato_an_l;
 ADCON0bits.GO=1;
 
 return;
 }
 
 
 }
 /******************************************/