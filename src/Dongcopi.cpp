
#include "DongCoPi.h"

uint8_t XMotor::status;
int XMotor::pinp1, XMotor::pinp2, XMotor::pinp3, XMotor::pinp4;
int XMotor::pind1, XMotor::pind2, XMotor::pind3, XMotor::pind4;
long XMotor::xung1, XMotor::xung2, XMotor::xung3, XMotor::xung4, XMotor::valDirect, XMotor::x;
bool XMotor::Dir1, XMotor::Dir2, XMotor::Dir3, XMotor::Dir4, XMotor::isFree, XMotor::Running, XMotor::Update;
unsigned int XMotor::Speed;

RPI_PICO_Timer DongCo1(0);
RPI_PICO_Timer DongCo2(1);
RPI_PICO_Timer DongCo3(2);
RPI_PICO_Timer DongCo4(3);

XMotor::XMotor() {}

void XMotor::init(int pindir1, int pinpwm1, int pindir2, int pinpwm2, int pindir3, int pinpwm3, int pindir4, int pinpwm4)
{
    pind1 = pindir1;
    pind2 = pindir2;
    pind3 = pindir3;
    pind4 = pindir4;
    pinp1 = pinpwm1;
    pinp2 = pinpwm2;
    pinp3 = pinpwm3;
    pinp4 = pinpwm4;

    pinMode(pind1, OUTPUT);
    pinMode(pind2, OUTPUT);
    pinMode(pind3, OUTPUT);
    pinMode(pind4, OUTPUT);
    pinMode(pinp1, OUTPUT);
    pinMode(pinp2, OUTPUT);
    pinMode(pinp3, OUTPUT);
    pinMode(pinp4, OUTPUT);
    status = STOP;

    // Attach interrupts
    DongCo1.attachInterrupt(1, xungDc1);
    DongCo2.attachInterrupt(1, xungDc2);
    DongCo3.attachInterrupt(1, xungDc3);
    DongCo4.attachInterrupt(1, xungDc4);
}

void XMotor::disable()
{
    DongCo1.disableTimer();
    DongCo2.disableTimer();
    DongCo3.disableTimer();
    DongCo4.disableTimer();
}

void XMotor::stop()
{
    xung1 = 0;
    xung2 = 0;
    xung3 = 0;
    xung4 = 0;
    Running = false;
    status = STOP;
}
bool XMotor::setMotor(uint8_t Control, uint8_t speed, uint16_t value)
{
    switch (Control)
    {
    case STOP:
        Serial.println("CALL STOP");
        stop();
        break;
    case UP:
        Serial.println("CALL UP");
        goUp(value, speed);
        break;
    case DOWN:
        Serial.println("CALL DOWN");
        goDown(value, speed);
        break;
    case LEFT:
        Serial.println("CALL LEFT");
        goLeft(value, speed);
        break;
    case RIGHT:
        Serial.println("CALL RIGHT");
        goRight(value, speed);
        break;
    case UP_UNLIMIT:
        Serial.println("CALL UP UNLIMIT");
        goUpUnlimit(speed);
        break;
    case DOWN_UNLIMIT:
        Serial.println("CALL DOWN UNLIMIT");
        goDownUnlimit(speed);
        break;
    case LEFT_UNLIMIT:
        Serial.println("CALL LEFT UNLIMIT");
        goLeftUnlimit(speed);
        break;
    case RIGHT_UNLIMIT:
        Serial.println("CALL RIGHT UNLIMIT");
        goRightUnlimit(speed);
        break;
    case UP_LEFT_UNLIMIT:
        Serial.println("CALL UP LEFT UNLIMIT");
        upLeftUnlimit(value, speed);
        break;
    case UP_RIGHT_UNLIMIT:
        Serial.println("CALL UP RIGHT UNLIMIT");
        upRightUnlimit(value, speed);
        break;
    case RO_LEFT:
        Serial.println("CALL RO LEFT");
        roLeft(value, speed);
        break;
    case RO_RIGHT:
        Serial.println("CALL RO RIGHT");
        roRight(value, speed);
        break;
    case RO_LEFT_UNLIMIT:
        Serial.println("CALL RO LEFT UNLIMIT");
        roLeftUnlimit(speed);
        break;
    case RO_RIGHT_UNLIMIT:
        Serial.println("CALL RO RIGHT UNLIMIT");
        roRightUnlimit(speed);
        break;
    case CROSS_UP_LEFT:
        Serial.println("CALL CROSS UP LEFT");
        crossUpLeft(value, speed);
        break;
    case CROSS_UP_RIGHT:
        Serial.println("CALL CROSS UP RIGHT");
        crossUpRight(value, speed);
        break;
    case CROSS_DOWN_LEFT:
        Serial.println("CALL CROSS DOWN LEFT");
        crossDownLeft(value, speed);
        break;
    case CROSS_DOWN_RIGHT:
        Serial.println("CALL CROSS DOWN RIGHT");
        crossDownRight(value, speed);
        break;
    case SPEED:
        Serial.println("CALL SET SPEED");
        setSpeed(speed);
        break;
    default:
        return false;
    }
    return true;
}
void XMotor::roLeft(unsigned long deg, unsigned int speed)
{
    Update = false;
    status = RO_LEFT;
    setDir(RO_LEFT);
    xung1 = (deg * ppr) / 360;
    xung2 = (deg * ppr) / 360;
    xung3 = (deg * ppr) / 360;
    xung4 = (deg * ppr) / 360;
    Running = false;
    setSpeed(speed);
    Update = true;
}
void XMotor::roRight(unsigned long deg, unsigned int speed)
{
    Update = false;
    status = RO_RIGHT;
    setDir(RO_RIGHT);
    xung1 = (deg * ppr) / 360;
    xung2 = (deg * ppr) / 360;
    xung3 = (deg * ppr) / 360;
    xung4 = (deg * ppr) / 360;
    setSpeed(speed);
    Running = false;
    Update = true;
}
void XMotor::roLeftUnlimit(unsigned int speed)
{
    Update = false;
    status = RO_LEFT_UNLIMIT;
    setDir(RO_LEFT_UNLIMIT);
    xung1 = 0;
    xung2 = 0;
    xung3 = 0;
    xung4 = 0;
    Running = true;
    setSpeed(speed);
    Update = true;
}
void XMotor::roRightUnlimit(unsigned int speed)
{
    Update = false;
    status = RO_RIGHT_UNLIMIT;
    setDir(RO_RIGHT_UNLIMIT);
    xung1 = 0;
    xung2 = 0;
    xung3 = 0;
    xung4 = 0;
    Running = true;
    setSpeed(speed);
    Update = true;
}
void XMotor::goUp(unsigned long mm, unsigned int speed)
{
    Update = false;
    status = UP;
    setDir(UP);
    xung1 = (mm * ppm) / 1000;
    xung2 = (mm * ppm) / 1000;
    xung3 = (mm * ppm) / 1000;
    xung4 = (mm * ppm) / 1000;
    Running = false;
    setSpeed(speed);

    Update = true;
}
void XMotor::goDown(unsigned long mm, unsigned int speed)
{
    Update = false;
    status = DOWN;
    setDir(DOWN);
    xung1 = (mm * ppm) / 1000;
    xung2 = (mm * ppm) / 1000;
    xung3 = (mm * ppm) / 1000;
    xung4 = (mm * ppm) / 1000;
    Running = false;
    setSpeed(speed);
    Update = true;
}
void XMotor::goLeft(unsigned long mm, unsigned int speed)
{
    Update = false;
    status = LEFT;
    setDir(LEFT);
    x = (mm * ppm) / 1000;
    xung1 = x - (x * 8 / 100);
    xung2 = x - (x * 8 / 100);
    xung3 = x;
    xung4 = x;
    Running = false;
    setSpeed(speed);
    Update = true;
}
void XMotor::goRight(unsigned long mm, unsigned int speed)
{

    Update = false;
    status = RIGHT;
    setDir(RIGHT);
    x = (mm * ppm) / 1000;
    xung1 = x - (x * 8 / 100);
    xung2 = x - (x * 8 / 100);
    xung3 = x;
    xung4 = x;
    Running = false;
    setSpeed(speed);
    Update = true;
}
void XMotor::goUpUnlimit(unsigned int speed)
{
    Update = false;
    status = UP_UNLIMIT;
    setDir(UP_UNLIMIT);
    xung1 = 0;
    xung2 = 0;
    xung3 = 0;
    xung4 = 0;
    Running = true;
    setSpeed(speed);
    Update = true;
}
void XMotor::goDownUnlimit(unsigned int speed)
{
    Update = false;
    status = DOWN_UNLIMIT;
    setDir(DOWN_UNLIMIT);
    xung1 = 0;
    xung2 = 0;
    xung3 = 0;
    xung4 = 0;
    Running = true;
    setSpeed(speed);
    Update = true;
}
void XMotor::goLeftUnlimit(unsigned int speed)
{
    Update = false;
    status = LEFT_UNLIMIT;
    setDir(LEFT_UNLIMIT);
    x = 1000;
    xung1 = x + 400;
    xung2 = x;
    xung3 = x + 400;
    xung4 = x;
    Running = true;
    setSpeed(speed);
    Update = true;
}
void XMotor::goRightUnlimit(unsigned int speed)
{
    Update = false;
    status = RIGHT_UNLIMIT;
    setDir(RIGHT_UNLIMIT);
    x = 1000;
    xung1 = x;
    xung2 = x + 400;
    xung3 = x;
    xung4 = x + 400;
    Running = true;
    setSpeed(speed);
    Update = true;
}
void XMotor::upRightUnlimit(unsigned long T1, unsigned int speed)
{
    if (T1 > speed)
    {
        T1 = speed;
    }
    valDirect = T1;
    Update = false;
    status = UP_RIGHT_UNLIMIT;
    setDir(UP_RIGHT_UNLIMIT);
    xung1 = 0;
    xung2 = 0;
    xung3 = 0;
    xung4 = 0;
    Running = true;
    setSpeed(speed);
    Update = true;
}
void XMotor::upLeftUnlimit(unsigned long T1, unsigned int speed)
{
    if (T1 > speed)
    {
        T1 = speed;
    }
    valDirect = T1;
    Update = false;
    status = UP_LEFT_UNLIMIT;
    setDir(UP_LEFT_UNLIMIT);
    xung1 = 0;
    xung2 = 0;
    xung3 = 0;
    xung4 = 0;
    Running = true;
    setSpeed(speed);
    Update = true;
}
void XMotor::crossUpLeft(unsigned long mm, unsigned int speed)
{
    Update = false;
    status = CROSS_UP_LEFT;
    setDir(CROSS_UP_LEFT);
    xung1 = 0;
    xung2 = (mm * ppm) / 1000;
    xung3 = 0;
    xung4 = (mm * ppm) / 1000;
    Running = false;
    setSpeed(speed);
    Update = true;
}
void XMotor::crossUpRight(unsigned long mm, unsigned int speed)
{
    Update = false;
    status = CROSS_UP_RIGHT;
    setDir(CROSS_UP_RIGHT);
    xung1 = (mm * ppm) / 1000;
    xung2 = 0;
    xung3 = (mm * ppm) / 1000;
    xung4 = 0;
    Running = false;
    setSpeed(speed);
    Update = true;
}
void XMotor::crossDownLeft(unsigned long mm, unsigned int speed)
{
    Update = false;
    status = CROSS_DOWN_LEFT;
    setDir(CROSS_DOWN_LEFT);
    xung1 = (mm * ppm) / 1000;
    xung2 = 0;
    xung3 = (mm * ppm) / 1000;
    xung4 = 0;
    Running = false;
    setSpeed(speed);
    Update = true;
}
void XMotor::crossDownRight(unsigned long mm, unsigned int speed)
{
    Update = false;
    status = CROSS_DOWN_RIGHT;
    setDir(CROSS_DOWN_RIGHT);
    xung1 = 0;
    xung2 = (mm * ppm) / 1000;
    xung3 = 0;
    xung4 = (mm * ppm) / 1000;
    Running = false;
    setSpeed(speed);
    Update = true;
}
uint8_t XMotor::getStatus()
{
    return status;
}
unsigned int XMotor::getSpeed()
{
    return Speed;
}
unsigned long XMotor::getPulse()
{
    unsigned int xungMax;
    if (xung1 > xungMax)
        xungMax = xung1;
    if (xung2 > xungMax)
        xungMax = xung2;
    if (xung3 > xungMax)
        xungMax = xung3;
    if (xung4 > xungMax)
        xungMax = xung4;
    return xungMax;
}
void XMotor::setSpeed(unsigned int speed)
{
    XMotor::Speed = speed;
    uint8_t STT = getStatus();
    if (STT == UP_LEFT_UNLIMIT)
    {
        DongCo1.setFrequency((pprDc * (speed + valDirect)) / 60, XMotor::xungDc1);
        DongCo2.setFrequency((pprDc * (speed - valDirect)) / 60, XMotor::xungDc2);
        DongCo3.setFrequency((pprDc * (speed - valDirect)) / 60, XMotor::xungDc3);
        DongCo4.setFrequency((pprDc * (speed + valDirect)) / 60, XMotor::xungDc4);
    }
    else if (STT == UP_RIGHT_UNLIMIT)
    {
        DongCo1.setFrequency((pprDc * (speed - valDirect)) / 60, XMotor::xungDc1);
        DongCo2.setFrequency((pprDc * (speed + valDirect)) / 60, XMotor::xungDc2);
        DongCo3.setFrequency((pprDc * (speed + valDirect)) / 60, XMotor::xungDc3);
        DongCo4.setFrequency((pprDc * (speed - valDirect)) / 60, XMotor::xungDc4);
    }
    else if (STT == LEFT_UNLIMIT || STT == LEFT || STT == RIGHT || STT == RIGHT_UNLIMIT)
    {

        DongCo1.setFrequency((((pprDc * speed) / 60) * xung1) / x, XMotor::xungDc1);
        DongCo2.setFrequency((((pprDc * speed) / 60) * xung2) / x, XMotor::xungDc2);
        DongCo3.setFrequency((((pprDc * speed) / 60) * xung3) / x, XMotor::xungDc3);
        DongCo4.setFrequency((((pprDc * speed) / 60) * xung4) / x, XMotor::xungDc4);
    }
    else
    {
        DongCo1.setFrequency((pprDc * speed) / 60, XMotor::xungDc1);
        DongCo2.setFrequency((pprDc * speed) / 60, XMotor::xungDc2);
        DongCo3.setFrequency((pprDc * speed) / 60, XMotor::xungDc3);
        DongCo4.setFrequency((pprDc * speed) / 60, XMotor::xungDc4);
    }
}
void XMotor::setDir(int direction)
{
    bool dir1, dir2, dir3, dir4;

    if (direction == UP || direction == UP_UNLIMIT || direction == UP_LEFT_UNLIMIT || direction == UP_RIGHT_UNLIMIT || direction == CROSS_UP_LEFT || direction == CROSS_UP_RIGHT)
    {
        dir1 = false;
        dir2 = true;
        dir3 = true;
        dir4 = false;
    }
    else if (direction == DOWN || direction == DOWN_UNLIMIT || direction == CROSS_DOWN_LEFT || direction == CROSS_DOWN_RIGHT)
    {
        dir1 = true;
        dir2 = false;
        dir3 = false;
        dir4 = true;
    }
    else if (direction == LEFT || direction == LEFT_UNLIMIT)
    {
        dir1 = true;
        dir2 = true;
        dir3 = false;
        dir4 = false;
    }
    else if (direction == RIGHT || direction == RIGHT_UNLIMIT)
    {
        dir1 = false;
        dir2 = false;
        dir3 = true;
        dir4 = true;
    }
    else if (direction == RO_LEFT || direction == RO_LEFT_UNLIMIT)
    {
        dir1 = false;
        dir2 = false;
        dir3 = false;
        dir4 = false;
    }
    else if (direction == RO_RIGHT || direction == RO_RIGHT_UNLIMIT)
    {
        dir1 = true;
        dir2 = true;
        dir3 = true;
        dir4 = true;
    }
    else
    {
        dir1 = true;
        dir2 = false;
        dir3 = true;
        dir4 = false;
    }
    digitalWrite(pind1, dir1);
    digitalWrite(pind2, dir2);
    digitalWrite(pind3, dir3);
    digitalWrite(pind4, dir4);
}
bool XMotor::xungDc1(struct repeating_timer *t)
{
    if (XMotor::xung1 > 0 || XMotor::Running)
    {
        if (XMotor::xung1 > 0)
        {
            digitalWrite(XMotor::pinp1, !digitalRead(XMotor::pinp1));
            XMotor::xung1--;
        }
        else
        {
            digitalWrite(XMotor::pinp1, !digitalRead(XMotor::pinp1));
        }
    }
    else
    {
        if (XMotor::Update && XMotor::xung1 == 0 && XMotor::xung2 == 0 && XMotor::xung3 == 0 && XMotor::xung4 == 0)
        {
            XMotor::status = STOP;
        }
    }
    return true;
}

bool XMotor::xungDc2(struct repeating_timer *t)
{
    if (XMotor::xung2 > 0 || XMotor::Running)
    {
        if (XMotor::xung2 > 0)
        {
            digitalWrite(XMotor::pinp2, !digitalRead(XMotor::pinp2));
            XMotor::xung2--;
        }
        else
        {
            digitalWrite(XMotor::pinp2, !digitalRead(XMotor::pinp2));
        }
    }
    else
    {
        if (XMotor::Update && XMotor::xung1 == 0 && XMotor::xung2 == 0 && XMotor::xung3 == 0 && XMotor::xung4 == 0)
        {
            XMotor::status = STOP;
        }
    }
    return true;
}

bool XMotor::xungDc3(struct repeating_timer *t)
{
    if (XMotor::xung3 > 0 || XMotor::Running)
    {
        if (XMotor::xung3 > 0)
        {
            digitalWrite(XMotor::pinp3, !digitalRead(XMotor::pinp3));
            XMotor::xung3--;
        }
        else
        {
            digitalWrite(XMotor::pinp3, !digitalRead(XMotor::pinp3));
        }
    }
    else
    {
        if (XMotor::Update && XMotor::xung1 == 0 && XMotor::xung2 == 0 && XMotor::xung3 == 0 && XMotor::xung4 == 0)
        {
            XMotor::status = STOP;
        }
    }
    return true;
}

bool XMotor::xungDc4(struct repeating_timer *t)
{
    if (XMotor::xung4 > 0 || XMotor::Running)
    {
        if (XMotor::xung4 > 0)
        {
            digitalWrite(XMotor::pinp4, !digitalRead(XMotor::pinp4));
            XMotor::xung4--;
        }
        else
        {
            digitalWrite(XMotor::pinp4, !digitalRead(XMotor::pinp4));
        }
    }
    else
    {
        if (XMotor::Update && XMotor::xung1 == 0 && XMotor::xung2 == 0 && XMotor::xung3 == 0 && XMotor::xung4 == 0)
        {
            XMotor::status = STOP;
        }
    }
    return true;
}