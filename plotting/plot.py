import serial
import matplotlib.pyplot as plt
import numpy as np
import json
import time

ser = serial.Serial()
ser.baudrate = 76800
ser.port = 'COM13'
ser.timeout = 2

filename = "responseSat.txt"

print("starting")

dict_list = []

now = time.time()
last = now

READ_SERIAL = False

if (READ_SERIAL):
    ser.open()
    try:
        while (now - last < 1):
            now = time.time()
            #print("now - last: " + str(now-last))
            try:
                d = ser.readline().decode('utf-8')
                print(d)
                dict = json.loads(d)
                print(dict)
                last = time.time()
                dict_list.append(dict)
                
            except Exception as err:
                print(err)
                
    except KeyboardInterrupt:
        ser.close()
    
    print("write to file")

    file = open(filename, "w+")
    file.write(json.dumps(dict_list))
    file.close()
    print("close file")

PLOT_FROM_FILE = True
if (PLOT_FROM_FILE):
    file = open(filename, "r")
    dict_list = json.loads(file.read())
    times = []
    right_ref = []
    left_ref = []
    right_speed = []
    left_speed = []
    right_u = []
    left_u = []

    for item in dict_list:
        times.append(item['t'])
        #ticks_right.append(item['r'])
        #ticks_left.append(item['l'])
        left_speed.append(item['l']['y'])
        left_ref.append(item['l']['ref'])
        left_u.append(item['l']['ulim'])
        right_speed.append(item['r']['y'])
        right_ref.append(item['r']['ref'])
        right_u.append(item['r']['ulim'])

    fig, ax = plt.subplots(2,2, sharex='col')
    ax[0][0].plot(times, left_speed, label="left rotational velocity")
    ax[0][0].plot(times, left_ref, label="left reference")
    ax[1][0].plot(times, left_u, label="left control action")
    ax[0][0].legend()
    ax[1][0].legend()
    ax[0][0].set(xlabel="time [ms]", ylabel="rotational velocity")
    ax[1][0].set(xlabel="time [ms]", ylabel="u")
    ax[0][1].plot(times, right_speed, label="right rotational velocity")
    ax[0][1].plot(times, right_ref, label="right reference")
    ax[1][1].plot(times, right_u, label="right control action")
    ax[0][1].legend()
    ax[1][1].legend()
    ax[0][1].set(xlabel="time [ms]", ylabel="rotational velocity")
    ax[1][1].set(xlabel="time [ms]", ylabel="u")
    ax[0][0].grid(True)
    ax[1][0].grid(True)
    ax[0][1].grid(True)
    ax[1][1].grid(True)
    plt.show()
