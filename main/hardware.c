#include "hardware.h"
#include <xc.h>

void hw_init(void) {
    // Initialize all hardware settings
    TRISA0 = INPUT; TRISA1 = INPUT; TRISA5 = INPUT;
    TRISE0 = INPUT; TRISE1 = INPUT; TRISE2 = INPUT;

    TRISA2 = OUTPUT; RA2 = LOW;
    TRISA3 = OUTPUT; RA3 = LOW;
    TRISA4 = OUTPUT; RA4 = LOW;

    TRISB0 = INPUT; TRISB1 = INPUT; TRISB2 = OUTPUT; RB2 = LOW;
    TRISB3 = OUTPUT; RB3 = LOW; TRISB4 = OUTPUT; RB4 = LOW;
    TRISB5 = OUTPUT; RB5 = LOW; TRISB6 = OUTPUT; RB6 = LOW;
    TRISB7 = OUTPUT; RB7 = LOW;

    TRISC0 = OUTPUT; RC0 = LOW; TRISC1 = OUTPUT; RC1 = LOW;
    TRISC2 = OUTPUT; RC2 = LOW; TRISC3 = INPUT;
    TRISC4 = INPUT; TRISC5 = OUTPUT; RC5 = LOW;
    TRISC6 = INPUT; TRISC7 = INPUT;

    TRISD0 = OUTPUT; RD0 = LOW; TRISD1 = OUTPUT; RD1 = LOW;
    TRISD2 = OUTPUT; RD2 = LOW; TRISD3 = OUTPUT; RD3 = LOW;
    TRISD4 = OUTPUT; RD4 = LOW; TRISD5 = OUTPUT; RD5 = LOW;
    TRISD6 = OUTPUT; RD6 = LOW; TRISD7 = OUTPUT; RD7 = LOW;

    // UART settings
    TXSTAbits.CSRC = 0;
    TXSTAbits.TX9 = 0;
    TXSTAbits.TXEN = 1;
    TXSTAbits.SYNC = 0;
    TXSTAbits.BRGH = 1;
    TXSTAbits.TRMT = 0;
    TXSTAbits.TX9D = 0;

    RCSTAbits.SPEN = 1;
    RCSTAbits.RX9 = 0;
    RCSTAbits.SREN = 0;
    RCSTAbits.CREN = 1;
    RCSTAbits.ADDEN = 0;
    RCSTAbits.FERR = 0;
    RCSTAbits.OERR = 0;
    RCSTAbits.RX9D = 0;

    SPBRG = 64;  // Baud rate setting

    // ADC settings
    ADCON0bits.ADCS1 = 1;
    ADCON0bits.ADCS0 = 0;
    ADCON0bits.CHS = 0;
    ADCON0bits.GO = 0;
    ADCON0bits.ADON = 0;

    ADCON1 = 0b10000000;  // Digital inputs
    PIE1bits.SSPIE = 0;
    SSPSTATbits.SMP = 0;
    SSPSTATbits.CKE = 0;

    SSPCONbits.SSPEN = 1;
    SSPCONbits.SSPM = 0b1000;

    SSPADD = 12;  // I2C address

    __delay_ms(10);
}
