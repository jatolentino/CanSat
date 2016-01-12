#include "eeprom.h"
#include "hardware.h"
#include <xc.h>

void EEPROM_Write(char str[]) {
    static long addr = EEPROM_INITIAL_ADDRESS;
    long addr_eep;
    char ctrl, ret;
    char i = 0;

    while(str[i] != '\0') {
        if (addr <= EEPROM_FINAL_ADDRESS) {
            switch (addr & 0x030000) {
                case 0x000000:
                    ctrl = 0b10100000; addr_eep = addr; break;
                case 0x010000:
                    ctrl = 0b10101000; addr_eep = addr - 0x010000; break;
                default:
                    put_string("Invalid EEPROM Address\n");
            }

            // Write to EEPROM
            START_EEPROM_WRITE:
            ret = I2C_StartCondition();
            if (ret == -1) goto START_EEPROM_WRITE;

            ret = I2C_Write(ctrl);
            if (ret == -1) goto START_EEPROM_WRITE;

            ret = I2C_Write((char)((addr_eep & 0x00ff00) >> 8));
            if (ret == -1) goto START_EEPROM_WRITE;

            ret = I2C_Write((char)(addr_eep & 0x0000ff));
            if (ret == -1) goto START_EEPROM_WRITE;

            ret = I2C_Write(str[i]);
            if (ret == -1) goto START_EEPROM_WRITE;

            ret = I2C_StopCondition();
            if (ret == -1) goto START_EEPROM_WRITE;
            else {
                i++;
                addr++;
            }

            __delay_ms(5);
        }
    }
}

char EEPROM_Read(void) {
    long addr, addr_eep;
    char ctrl, data;
    char ret;

    __delay_ms(1000);

    for(addr = EEPROM_INITIAL_ADDRESS; addr <= EEPROM_FINAL_ADDRESS; addr++) {
        START_EEPROM_READ:

        LED = ~LED;

        switch (addr & 0x030000) {
            case 0x000000:
                ctrl = 0b10100000; addr_eep = addr; break;
            case 0x010000:
                ctrl = 0b10101000; addr_eep = addr - 0x010000; break;
            default:
                put_string("Invalid EEPROM Address\n");
        }

        ret = I2C_StartCondition();
        if (ret == -1) goto START_EEPROM_READ;

        ret = I2C_Write(ctrl);
        if (ret == -1) goto START_EEPROM_READ;

        ret = I2C_Write((char)((addr_eep & 0x00ff00) >> 8));
        if (ret == -1) goto START_EEPROM_READ;

        ret = I2C_Write((char)(addr_eep & 0x0000ff));
        if (ret == -1) goto START_EEPROM_READ;

        I2C_StopCondition(); // Stop the I2C transaction

        // Read data from EEPROM
        switch (addr & 0x030000) {
            case 0x000000:
                ctrl = 0b10100001; break;
            case 0x010000:
                ctrl = 0b10101001; break;
            default:
                put_string("Invalid EEPROM Address\n");
        }

        ret = I2C_StartCondition();
        if (ret == -1) goto START_EEPROM_READ;

        ret = I2C_Write(ctrl);
        if (ret == -1) goto START_EEPROM_READ;

        // Read a byte from EEPROM
        data = I2C_Read(1); // Acknowledge (1 means more data will be read)
        NOP();

        ret = I2C_StopCondition();
        if (ret == -1) goto START_EEPROM_READ;

        put_char(data); // Output the read byte
        __delay_ms(10); // Delay between reads
    }

    return 0;
}

