
#ifndef DONGCO_PI
#define DONGCO_PI

#define pprDc 388 // xung trên vòng dong co

#define vanToc 10
#define ppr 2155 // xung trên vòng
#define ppm 1227 // xung trên met

#define PAUSE 0x00
#define RESUME 0x01
#define STOP 0x10
#define SPEED 0x11

#define UP 0x02
#define DOWN 0x03
#define LEFT 0x04
#define RIGHT 0x05

#define UP_UNLIMIT 0x12
#define DOWN_UNLIMIT 0x13
#define LEFT_UNLIMIT 0x14
#define RIGHT_UNLIMIT 0x15
#define UP_LEFT_UNLIMIT 0x16
#define UP_RIGHT_UNLIMIT 0x17

#define RO_LEFT 0x20
#define RO_RIGHT 0x21
#define RO_LEFT_UNLIMIT 0x22
#define RO_RIGHT_UNLIMIT 0x23

#define CROSS_UP_LEFT 0x30
#define CROSS_UP_RIGHT 0x31
#define CROSS_DOWN_LEFT 0x32
#define CROSS_DOWN_RIGHT 0x33

#define START_BYTE 0x80
#define STOP_BYTE 0x81
#define STATUS 0x82

#include <RPi_Pico_TimerInterrupt.h>

class XMotor
{
private:
    static uint8_t status;
    static int pinp1, pinp2, pinp3, pinp4;
    static int pind1, pind2, pind3, pind4;
    static long xung1, xung2, xung3, xung4, valDirect, x;
    static bool Dir1, Dir2, Dir3, Dir4, isFree, Running, Update;
    static unsigned int Speed;
    static bool xungDc1(struct repeating_timer *t);
    static bool xungDc2(struct repeating_timer *t);
    static bool xungDc3(struct repeating_timer *t);
    static bool xungDc4(struct repeating_timer *t);

public:
    XMotor();
    void init(int pindir1, int pinpwm1, int pindir2, int pinpwm2, int pindir3, int pinpwm3, int pindir4, int pinpwm4);
    void disable();
    void stop();
    bool setMotor(uint8_t Control, uint8_t speed, uint16_t value);
    void goUp(unsigned long mm, unsigned int speed);
    void goDown(unsigned long mm, unsigned int speed);
    void goLeft(unsigned long mm, unsigned int speed);
    void goRight(unsigned long mm, unsigned int speed);
    void roLeftUnlimit(unsigned int speed);
    void roRightUnlimit(unsigned int speed);
    void roLeft(unsigned long deg, unsigned int speed);
    void roRight(unsigned long deg, unsigned int speed);
    void goUpUnlimit(unsigned int speed);
    void goDownUnlimit(unsigned int speed);
    void goLeftUnlimit(unsigned int speed);
    void goRightUnlimit(unsigned int speed);
    void upRightUnlimit(unsigned long T1, unsigned int speed);
    void upLeftUnlimit(unsigned long T1, unsigned int speed);
    void downRightUnlimit(unsigned long T1, unsigned int speed);
    void downLeftUnlimit(unsigned long T1, unsigned int speed);
    void crossUpLeft(unsigned long mm, unsigned int speed);
    void crossUpRight(unsigned long mm, unsigned int speed);
    void crossDownLeft(unsigned long mm, unsigned int speed);
    void crossDownRight(unsigned long mm, unsigned int speed);
    uint8_t getStatus();
    unsigned int getSpeed();
    unsigned long getPulse();
    void setSpeed(unsigned int speed);
    void setDir(int direction);
};

#endif
