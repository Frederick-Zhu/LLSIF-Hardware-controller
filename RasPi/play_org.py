#!/usr/bin/python
# -*- coding: utf-8 -*-

import json
import threading
import time
import RPi.GPIO as GPIO
import sys

__author__ = 'ZHU ZICHEN'
# __configname = 'test.json'

__configname = ''

Pos2Pin = {
    1: 2,
    2: 3,
    3: 4,
    4: 17,
    5: 27,
    6: 22,
    7: 10,
    8: 9,
    9: 11
}

# PosStatus = {
#     1: 1,
#     2: 1,
#     3: 1,
#     4: 1,
#     5: 1,
#     6: 1,
#     7: 1,
#     8: 1,
#     9: 1
# }

A = 0
B = 0


# def pr():
#     print PosStatus[1], PosStatus[2], PosStatus[3], PosStatus[4], PosStatus[5], PosStatus[6], PosStatus[7], PosStatus[
#         8], PosStatus[9]


def TouchDownA(Pos, Time=0.04):
    global A
    global T
    A = 1
    # PosStatus[Pos] = 0
    GPIO.output(Pos2Pin[Pos], 0)
    print Pos, time.time() - T
    # pr()
    global a
    a = threading.Timer(Time, TouchUpA, args=[Pos])
    a.start()


def TouchUpA(Pos):
    global A
    A = 0
    # PosStatus[Pos] = 1
    GPIO.output(Pos2Pin[Pos], 1)
    # pr()


def TouchDownB(Pos, Time=0.04):
    global B
    global T
    B = 1
    # PosStatus[Pos] = 0
    GPIO.output(Pos2Pin[Pos], 0)
    print Pos, time.time() - T
    # pr()
    global b
    b = threading.Timer(Time, TouchUpB, args=[Pos])
    b.start()


def TouchUpB(Pos):
    global B
    B = 0
    # PosStatus[Pos] = 1
    GPIO.output(Pos2Pin[Pos], 1)
    # pr()




def d(configname):
    global T
    try:
        f = open(name=configname, mode='r')
        try:
            t = json.load(fp=f)
            print configname, 'DATA OK!'
            # for i in range(0, len(t['data'])):
            #     print i, t['data'][i]['timing_sec'], t['data'][i]['effect'], t['data'][i]['effect_value'], t['data'][i]['position']
        except ValueError:
            print "Value ERROR!"
    except IOError:
        print 'IO ERROR!'

    count = 0

    print 'Pos:', t['response_data']['live_info'][0]['notes_list'][count]['position']
    print 'Begin?'
    raw_input()
    T = time.time() - t['response_data']['live_info'][0]['notes_list'][count]['timing_sec']
    print 'T:', T

    if A == 0:
        if t['response_data']['live_info'][0]['notes_list'][count]['effect'] == 3:
            a = threading.Timer(0.0, TouchDownA, args=[t['response_data']['live_info'][0]['notes_list'][count]['position'],
                                                       t['response_data']['live_info'][0]['notes_list'][count][
                                                           'effect_value']])
            a.start()
        else:
            a = threading.Timer(0.0, TouchDownA, args=[t['response_data']['live_info'][0]['notes_list'][count]['position']])
            a.start()
    elif B == 0:
        if t['response_data']['live_info'][0]['notes_list'][count]['effect'] == 3:
            b = threading.Timer(0.0, TouchDownB, args=[t['response_data']['live_info'][0]['notes_list'][count]['position'],
                                                       t['response_data']['live_info'][0]['notes_list'][count][
                                                           'effect_value']])
            b.start()
        else:
            b = threading.Timer(0.0, TouchDownB, args=[t['response_data']['live_info'][0]['notes_list'][count]['position']])
            b.start()
    count += 1
    while count < len(t['response_data']['live_info'][0]['notes_list']):
        while time.time() - T > t['response_data']['live_info'][0]['notes_list'][count]['timing_sec']:
            if A == 0:
                if t['response_data']['live_info'][0]['notes_list'][count]['effect'] == 3:
                    a = threading.Timer(0.0, TouchDownA,
                                        args=[t['response_data']['live_info'][0]['notes_list'][count]['position'],
                                              t['response_data']['live_info'][0]['notes_list'][count]['effect_value']])
                    a.start()
                else:
                    a = threading.Timer(0.0, TouchDownA,
                                        args=[t['response_data']['live_info'][0]['notes_list'][count]['position']])
                    a.start()
            elif B == 0:
                if t['response_data']['live_info'][0]['notes_list'][count]['effect'] == 3:
                    b = threading.Timer(0.0, TouchDownB,
                                        args=[t['response_data']['live_info'][0]['notes_list'][count]['position'],
                                              t['response_data']['live_info'][0]['notes_list'][count]['effect_value']])
                    b.start()
                else:
                    b = threading.Timer(0.0, TouchDownB,
                                        args=[t['response_data']['live_info'][0]['notes_list'][count]['position']])
                    b.start()
            count += 1
            break



GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
for item in Pos2Pin:
    GPIO.setup(Pos2Pin[item], GPIO.OUT)
    GPIO.output(Pos2Pin[item], 1)
    print 'Open GPIO', Pos2Pin[item], 'success!'

num = len(sys.argv)

if num == 1:
    d('test.json')
else:
    while num > 1:
        d(sys.argv[num-1])
        num -= 1