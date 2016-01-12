#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "hardware.h"
#include "eeprom.h"
#include "gps.h"

// Configuration bits
__CONFIG(FOSC_HS & WDTE_OFF & PWRTE_OFF & BOREN_OFF & LVP_OFF & CPD_OFF & WRT_OFF & CP_OFF);
#define _XTAL_FREQ  10000000

void main(void)
{
    char cnt;
    unsigned char ret;
    char GPS[GPS_LENGTH], num_sat;
    char f_GPS = 0;
    char gps_wp = 0;
    char rxbuf;

    __delay_ms(10);
    hw_init();  // Initialize hardware

    for(cnt = 0; cnt < GPS_LENGTH; cnt++) GPS[cnt] = 0;

    LED = HIGH;
    __delay_ms(500);
    LED = LOW;

    if (READ == LOW) {
        ret = I2C_StartCondition();
        ret = I2C_Write(0b00010000);  // Write some I2C commands
        ret = I2C_Write(0x73);
        ret = I2C_Write(0x00);
        ret = I2C_StopCondition();
        __delay_ms(10);

        while(1) {
            if (PIR1bits.RCIF) {
                PIR1bits.RCIF = 0;
                if (RCSTAbits.FERR || RCSTAbits.OERR) {
                    RCSTAbits.CREN = 0;
                    __delay_us(10);
                    RCSTAbits.CREN = 1;
                    rxbuf = '?';
                } else {
                    rxbuf = RCREG;
                }

                if (rxbuf == '?') {
                    LED = HIGH;
                    __delay_ms(50);
                    LED = LOW;
                    __delay_ms(50);
                }

                if (rxbuf == '$') {
                    gps_wp = 0;
                    f_GPS = 1;
                }

                if (f_GPS == 1) {
                    GPS[gps_wp] = rxbuf;
                    if (GPS[gps_wp] == 0x0a) {
                        GPS[gps_wp + 1] = '\0';
                        f_GPS = 2;
                    } else {
                        gps_wp++;
                    }
                }
            }

            if (f_GPS == 2) {
                num_sat = (GPS[45] - 0x30) * 10 + (GPS[46] - 0x30);
                if (num_sat > 4) {
                    num_sat = 4;
                    LED = HIGH;
                }

                EEPROM_Write(GPS);  // Write to EEPROM
                if (SEP == HIGH) put_string(GPS);
                f_GPS = 0;

                LED = HIGH;
                LED = LOW;
            }
        }
    } else {
        while(1) {
            put_string("Start EEPROM Read\n");
            EEPROM_Read();
            put_string("End EEPROM Read\n");
        }
    }
}
