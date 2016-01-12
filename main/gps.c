#include "gps.h"
#include "hardware.h"
#include <xc.h>

char I2C_StartCondition(void) {
    SSPCON2bits.SEN = 1;
    while(1) {
        if (PIR1bits.SSPIF == 1) {
            PIR1bits.SSPIF = 0;
            return(1);
        }
        if (PIR2bits.BCLIF == 1) {
            PIR2bits.BCLIF = 0;
            return(-1);
        }
    }
}

char I2C_StopCondition(void) {
    SSPCON2bits.PEN = 1;
    while(1) {
        if (PIR1bits.SSPIF == 1) {
            PIR1bits.SSPIF = 0;
            return(1);
        }
        if (PIR2bits.BCLIF == 1) {
            PIR2bits.BCLIF = 0;
            return(-1);
        }
    }
}

char I2C_Write(char dat) {
    SSPBUF = dat;
    while(!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;
    return((SSPCON2bits.ACKSTAT == 1) ? -1 : 1);
}

char I2C_Read(char ack) {
    SSPCON2bits.RCEN = 1;
    while(!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;
    SSPCON2bits.ACKDT = ack;
    SSPCON2bits.ACKEN = 1;
    while(!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;
    return(SSPBUF);
}

void put_char(unsigned char dum) {
    while(!PIR1bits.TXIF);
    TXREG = dum;
}

void put_string(const unsigned char *dum) {
    int cnt = 0;
    while(dum[cnt] != '\0') put_char(dum[cnt++]);
}
