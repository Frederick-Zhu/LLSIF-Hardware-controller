#include "TouchScreen.h"

#include <Arduino.h>

#if defined(_USING_HID)

#define LSB(_x) ((_x) & 0xFF)
#define MSB(_x) ((_x) >> 8)


static const uint8_t _hidReportDescriptor[] PROGMEM = {
    0x05, 0x0d,                 // USAGE_PAGE (Digitizers)
    0x09, 0x04,                 // USAGE (Touch Screen)
    0xa1, 0x01,                 // COLLECTION (Application)
    0x85, REPORTID_MTOUCH,      //   REPORT_ID (Touch)
    0x09, 0x22,                 //   USAGE (Finger)
    0xa1, 0x02,                 //     COLLECTION (Logical)
    0x09, 0x42,                 //       USAGE (Tip Switch)
    0x15, 0x00,                 //       LOGICAL_MINIMUM (0)
    0x25, 0x01,                 //       LOGICAL_MAXIMUM (1)
    0x75, 0x01,                 //       REPORT_SIZE (1)
    0x95, 0x01,                 //       REPORT_COUNT (1)
    0x81, 0x02,                 //       INPUT (Data,Var,Abs)
    0x09, 0x32,                 //       USAGE (In Range)
    0x81, 0x02,                 //       INPUT (Data,Var,Abs)
    0x95, 0x06,                 //       REPORT_COUNT (6)
    0x81, 0x03,                 //       INPUT (Cnst,Ary,Abs)
    0x75, 0x08,                 //       REPORT_SIZE (8)
    0x25, 0x0a,                 //       LOGICAL_MAXIMUM (10)
    0x09, 0x51,                 //       USAGE ( Contact Identifier)
    0x95, 0x01,                 //       REPORT_COUNT (1)
    0x81, 0x02,                 //       INPUT (Data,Var,Abs)
    0xa1, 0x00,                 //       COLLECTION (Physical)
    0x05, 0x01,                 //          USAGE_PAGE (Generic Desk..
    //    0x26, 0xff, 0x0f,           //          LOGICAL_MAXIMUM (4095)
    0x75, 0x10,                 //          REPORT_SIZE (16)
    0x55, 0x00,                 //          UNIT_EXPONENT (0)
    0x65, 0x00,                 //          UNIT(None)
    //    0x55, 0x0e,                 //          UNIT_EXPONENT (-2)
    //    0x65, 0x33,                 //          UNIT(Inch,EngLinear)
    0x09, 0x30,                 //          USAGE (X)
    0x26, 0x38, 0x04,           //          LOGICAL_MAXIMUM (1080)
//    0x26, 0xd0, 0x02,           //          LOGICAL_MAXIMUM (720)
    0x35, 0x00,                 //          PHYSICAL_MINIMUM (0)
    0x46, 0x38, 0x04,           //          PHYSICAL_MAXIMUM (1080)
//    0x46, 0xd0, 0x02,           //          PHYSICAL_MAXIMUM (720)
    0x81, 0x02,                 //          INPUT (Data,Var,Abs)
    0x09, 0x31,                 //          USAGE (Y)
    0x46, 0x80, 0x07,           //          PHYSICAL_MAXIMUM (1920)
    0x26, 0x80, 0x07,           //          LOGICAL_MAXIMUM (1920)
//    0x46, 0x00, 0x05,           //          PHYSICAL_MAXIMUM (1280)
//    0x26, 0x00, 0x05,           //          LOGICAL_MAXIMUM (1280)
    0x81, 0x02,                 //          INPUT (Data,Var,Abs)
    0x45, 0x00,                 //          PHYSICAL_MAXIMUM (0)reset
    0xc0,                       //       END_COLLECTION
    0xc0,                       //    END_COLLECTION
    //------------------------------------------
    0x05, 0x0d,                 //    USAGE_PAGE (Digitizers)
    0x09, 0x22,                 //    USAGE (Finger)
    0xa1, 0x02,                 //    COLLECTION (Logical)
    0x09, 0x42,                 //       USAGE (Tip Switch)
    0x15, 0x00,                 //       LOGICAL_MINIMUM (0)
    0x25, 0x01,                 //       LOGICAL_MAXIMUM (1)
    0x75, 0x01,                 //       REPORT_SIZE (1)
    0x95, 0x01,                 //       REPORT_COUNT (1)
    0x81, 0x02,                 //       INPUT (Data,Var,Abs)
    0x09, 0x32,                 //       USAGE (In Range)
    0x81, 0x02,                 //       INPUT (Data,Var,Abs)
    0x95, 0x06,                 //       REPORT_COUNT (6)
    0x81, 0x03,                 //       INPUT (Cnst,Ary,Abs)
    0x75, 0x08,                 //       REPORT_SIZE (8)
    0x25, 0x0a,                 //       LOGICAL_MAXIMUM (10)
    0x09, 0x51,                 //       USAGE ( Contact Identifier)
    0x95, 0x01,                 //       REPORT_COUNT (1)
    0x81, 0x02,                 //       INPUT (Data,Var,Abs)
    0xa1, 0x00,                 //       COLLECTION (Physical)
    0x05, 0x01,                 //          USAGE_PAGE (Generic Desk..
    //    0x26, 0xff, 0x0f,           //          LOGICAL_MAXIMUM (4095)
    0x75, 0x10,                 //          REPORT_SIZE (16)
    0x55, 0x00,                 //          UNIT_EXPONENT (0)
    0x65, 0x00,                 //          UNIT(None)
    //    0x55, 0x0e,                 //          UNIT_EXPONENT (-2)
    //    0x65, 0x33,                 //          UNIT(Inch,EngLinear)
    0x09, 0x30,                 //          USAGE (X)
        0x26, 0x38, 0x04,           //          LOGICAL_MAXIMUM (1080)
//    0x26, 0xd0, 0x02,           //          LOGICAL_MAXIMUM (720)
    0x35, 0x00,                 //          PHYSICAL_MINIMUM (0)
        0x46, 0x38, 0x04,           //          PHYSICAL_MAXIMUM (1080)
//    0x46, 0xd0, 0x02,           //          PHYSICAL_MAXIMUM (720)
    0x81, 0x02,                 //          INPUT (Data,Var,Abs)
    0x09, 0x31,                 //          USAGE (Y)
        0x46, 0x80, 0x07,           //          PHYSICAL_MAXIMUM (1920)
        0x26, 0x80, 0x07,           //          LOGICAL_MAXIMUM (1920)
//    0x46, 0x00, 0x05,           //          PHYSICAL_MAXIMUM (1280)
//    0x26, 0x00, 0x05,           //          LOGICAL_MAXIMUM (1280)
    0x81, 0x02,                 //          INPUT (Data,Var,Abs)
    0x45, 0x00,                 //          PHYSICAL_MAXIMUM (0)reset
    0xc0,                       //       END_COLLECTION
    0xc0,                       //   END_COLLECTION
    //------------------------------------------
    0x05, 0x0d,                 //   USAGE_PAGE (Digitizers)
    0x09, 0x54,                 //   USAGE (Contact Count)
    0x25, 0x0a,                 //   LOGICAL_MAXIMUM (10)
    0x95, 0x01,                 //   REPORT_COUNT (1)
    0x75, 0x08,                 //   REPORT_SIZE (8)
    0x81, 0x02,                 //   INPUT (Data,Var,Abs)
    //------------------------------------------
    0x85, REPORTID_MAX_COUNT,   //   REPORT_ID (Contact Count Max)
    0x09, 0x55,                 //   USAGE(Contact Count Maximum)
    0x95, 0x01,                 //   REPORT_COUNT (1)
    0x25, 0x0a,                 //   LOGICAL_MAXIMUM (10)
    0xb1, 0x03,                 //   FEATURE (Const,Var,Abs)
    0xc0,                       // END_COLLECTION
    //------------------------------------------
    0x09, 0x0E,                 // USAGE (Device Configuration)
    0xa1, 0x01,                 // COLLECTION (Application)
    0x85, REPORTID_FEATURE,     //   REPORT_ID (Configuration)
    0x09, 0x23,                 //   USAGE (Device Settings)
    0xa1, 0x02,                 //   COLLECTION (logical)
    0x09, 0x52,                 //    USAGE (Device Mode)
    0x09, 0x53,                 //    USAGE (Device Identifier)
    0x15, 0x00,                 //    LOGICAL_MINIMUM (0)
    0x25, 0x0a,                 //    LOGICAL_MAXIMUM (10)
    0x75, 0x08,                 //    REPORT_SIZE (8)
    0x95, 0x02,                 //    REPORT_COUNT (2)
    0xb1, 0x02,                 //   FEATURE (Data,Var,Abs
    0xc0,                       //   END_COLLECTION
    0xc0,                       // END_COLLECTION
    //------------------------------------------
    0x05, 0x01,                 // USAGE_PAGE (Generic Desktop)     0
    0x09, 0x02,                 // USAGE (Mouse)                    2
    0xa1, 0x01,                 // COLLECTION (Application)         4
    0x85, REPORTID_MOUSE,       //   REPORT_ID (Mouse)              6
    0x09, 0x01,                 //   USAGE (Pointer)                8
    0xa1, 0x00,                 //   COLLECTION (Physical)          10
    0x05, 0x09,                 //     USAGE_PAGE (Button)          12
    0x19, 0x01,                 //     USAGE_MINIMUM (Button 1)     14
    0x29, 0x02,                 //     USAGE_MAXIMUM (Button 2)     16
    0x15, 0x00,                 //     LOGICAL_MINIMUM (0)          18
    0x25, 0x01,                 //     LOGICAL_MAXIMUM (1)          20
    0x75, 0x01,                 //     REPORT_SIZE (1)              22
    0x95, 0x02,                 //     REPORT_COUNT (2)             24
    0x81, 0x02,                 //     INPUT (Data,Var,Abs)         26
    0x95, 0x06,                 //     REPORT_COUNT (6)             28
    0x81, 0x03,                 //     INPUT (Cnst,Var,Abs)         30
    0x05, 0x01,                 //     USAGE_PAGE (Generic Desktop) 32
    0x09, 0x30,                 //     USAGE (X)                    34
    0x09, 0x31,                 //     USAGE (Y)                    36
    0x75, 0x10,                 //     REPORT_SIZE (16)             38
    0x95, 0x02,                 //     REPORT_COUNT (2)             40
    0x15, 0x00,                 //     LOGICAL_MINIMUM (0)          42
    0x26, 0xff, 0x7f,           //     LOGICAL_MAXIMUM (32767)      44
    0x81, 0x02,                 //     INPUT (Data,Var,Abs)         47
    0xc0,                       //   END_COLLECTION                 49
    0xc0                        // END_COLLECTION                   50/51
};




/*
 
 
 data[0] = 0x00;             //D0 Tip Switch  D1 In Range
 data[1] = Contact_ID_A;     //Contact Identifier
 data[2] = 0x00;             //XL
 data[3] = 0x00;             //XH
 data[4] = 0x00;             //YL
 data[5] = 0x00;             //YH
 //------------------------
 data[6] = 0x00;
 data[7] = Contact_ID_B;
 data[8] = 0x00;
 data[9] = 0x00;
 data[10] = 0x00;
 data[11] = 0x00;
 //-------------------------
 data[12] = 0x00;            //Contact Count
 
 
 */






TouchScreen_::TouchScreen_(void) {
    const static HID_Descriptor cb = {
        .length = sizeof(_hidReportDescriptor),
        .descriptor = _hidReportDescriptor,
    };
    static HIDDescriptorListNode node(&cb);
    HID.AppendDescriptor(&node);
    
    TouchUpAll();
    
    pointA.flag = false;
    pointA.x = 0;
    pointA.y = 0;
    pointB.flag = false;
    pointB.x = 0;
    pointB.y = 0;
    
    
    randomSeed(analogRead(A0));
}





void TouchScreen_::SendPoint(void) {
    uint8_t buffer[13];
    
    if (pointA.flag == true) {
        buffer[0] = 0x03;
    }
    else {
        buffer[0] = 0x00;
    }
    buffer[1] = Contact_ID_A;
    buffer[2] = LSB(pointA.x - 10 + random(21));
    buffer[3] = MSB(pointA.x - 10 + random(21));
    buffer[4] = LSB(pointA.y - 10 + random(21));
    buffer[5] = MSB(pointA.y - 10 + random(21));
    if (pointB.flag == true) {
        buffer[6] = 0x03;
    }
    else {
        buffer[6] = 0x00;
    }
    buffer[7] = Contact_ID_B;
    buffer[8] = LSB(pointB.x - 10 + random(21));
    buffer[9] = MSB(pointB.x - 10 + random(21));
    buffer[10] = LSB(pointB.y - 10 + random(21));
    buffer[11] = MSB(pointB.y - 10 + random(21));
    buffer[12] = 0x02;
    
    HID.SendReport(REPORTID_MTOUCH, buffer, 13);
}




void TouchScreen_::begin(void) {
}

void TouchScreen_::end(void) {
}


void TouchScreen_::TouchDownAll(uint16_t ax, uint16_t ay, uint16_t bx, uint16_t by) {
    pointA.flag = true;
    pointA.x = ax + 1;
    pointA.y = ay + 1;
    pointB.flag = true;
    pointB.x = bx + 1;
    pointB.y = by + 1;
    
    SendPoint();
}


void TouchScreen_::TouchUpAll(void) {
    pointA.flag = false;
    pointA.flag = false;
    
    SendPoint();
}

void TouchScreen_::TouchDownA(uint16_t inx, uint16_t iny) {
    pointA.flag = true;
    pointA.x = inx + 1;
    pointA.y = iny + 1;
    
    SendPoint();
}

void TouchScreen_::TouchUpA(void) {
    pointA.flag = false;
    
    SendPoint();
}


void TouchScreen_::TouchDownB(uint16_t inx, uint16_t iny) {
    pointB.flag = true;
    pointB.x = inx + 1;
    pointB.y = iny + 1;
    
    SendPoint();
}

void TouchScreen_::TouchUpB(void) {
    pointB.flag = false;
    
    SendPoint();
}


TouchScreen_ TouchScreen;

#endif
