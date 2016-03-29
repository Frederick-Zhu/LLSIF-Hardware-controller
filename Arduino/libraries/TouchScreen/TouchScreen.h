#ifndef TOUCHSCREEN_h
#define TOUCHSCREEN_h

#include "HID_ts.h"

#if !defined(_USING_HID)

#warning "Using legacy HID core (non pluggable)"

#else

//================================================================================
//================================================================================
//  TouchScreen


#define REPORTID_MTOUCH 0x01    //ID
#define REPORTID_MAX_COUNT 0x02 //ID
#define REPORTID_FEATURE 0x03   //ID
#define REPORTID_MOUSE 0x04     //ID

#define Contact_ID_A 0x01
#define Contact_ID_B 0x02

#define MAX_Contact 2

#define TOUCH_DOWN_FLAG 0x03
#define TOUCH_UP_FLAG 0x00



//Point Data

#define P1 811, 220
#define P2 553, 272
#define P3 335, 418
#define P4 187, 636
#define P5 135, 896
#define P6 187, 1155
#define P7 335, 1372
#define P8 553, 1519
#define P9 810, 1571









typedef struct {
    bool flag;
    uint16_t x;
    uint16_t y;
}point;



class TouchScreen_
{
private:
//    uint8_t data[13];
    point pointA;
    point pointB;
    void SendPoint(void);
public:
    TouchScreen_(void);
    void begin(void);
    void end(void);
    void TouchDownA(uint16_t x, uint16_t y);
    void TouchDownB(uint16_t x, uint16_t y);
    void TouchDownAll(uint16_t ax, uint16_t ay, uint16_t bx, uint16_t by);
    void TouchUpA(void);
    void TouchUpB(void);
    void TouchUpAll(void);
    void clean(void);
    
//    void test1(void);
//    void test2(void);
//    void test3(void);
//    void test4(void);
};



extern TouchScreen_ TouchScreen;
extern HID_ HID;

#endif
#endif