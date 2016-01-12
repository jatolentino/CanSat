#ifndef HARDWARE_H
#define HARDWARE_H

#define READ    RB0
#define SEP     RB1
#define LED     RB3
#define CAM_IF1 RB4
#define CAM_IF2 RB5

#define INPUT   1
#define OUTPUT  0
#define HIGH    1
#define LOW     0
#define ACK     0

#define GPS_LENGTH              76
#define EEPROM_INITIAL_ADDRESS  0x000000
#define EEPROM_FINAL_ADDRESS    0x01ffff

void hw_init(void);  // Initialize hardware

#endif // HARDWARE_H
