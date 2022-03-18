import os
from time import sleep

class GPIO_Pin:
    def __init__(self, num, mode):
        if 0 <= num or num <= 40:
            self.num = num
        else:
            print('Invalid Pin Number -> Enter a number from 0 - 40')
        if mode == 'out' or mode == 'write':
            self.mode = 'out'
        elif mode == 'in' or mode == 'read':
            self.mode = 'in'
        else:
            print('Invalid Pin Mode -> Enter "out" or "write" for output, "in" or "read" for input')
        if self.num and self.mode:
            os.system(f'echo {str(self.num)} > /sys/class/gpio/export')
            sleep(0.05)
            os.system(f'echo {self.mode} > /sys/class/gpio/gpio{str(self.num)}/direction')

    def reset(self):
        os.system(f'echo 0 > /sys/class/gpio/gpio{str(self.num)}/value')
        os.system(f'echo in > /sys/class/gpio/gpio{str(self.num)}/direction')

    def write(self, value):
        if value == 0 or value == 'LOW':
            os.system(f'echo 0 > /sys/class/gpio/gpio{str(self.num)}/value')
        elif value == 1 or value == 'HIGH':
            os.system(f'echo 1 > /sys/class/gpio/gpio{str(self.num)}/value')
        else:
            print('Invalid value -> Enter 1 or "HIGH" for HIGH, 0 or "LOW" for LOW')

    def __del__(self):
        self.reset()
        os.system(f'echo {str(self.num)} > /sys/class/gpio/unexport')

    def set_mode(self, mode):
        self.mode = mode
        os.system(f'echo {str(self.mode)} > /sys/class/gpio/gpio{str(self.num)}/direction')

def main():
    pin = GPIO_Pin(13, 'out')
    number = 10
    for i in range(number):
        pin.write('HIGH')
        sleep(0.5)
        pin.write('LOW')
        sleep(0.5)

if __name__ == '__main__':
    main()