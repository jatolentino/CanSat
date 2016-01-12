#ifndef GPS_H
#define GPS_H

char I2C_StartCondition(void);  // Start I2C communication
char I2C_StopCondition(void);   // Stop I2C communication
char I2C_Write(char dat);       // Write a byte to I2C
char I2C_Read(char ack);        // Read a byte from I2C
void put_char(unsigned char dum);  // Output a single character
void put_string(const unsigned char *dum);  // Output a string

#endif // GPS_H
