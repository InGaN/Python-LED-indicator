import serial
import time


def set_led(r, g, b, blink_speed=0):
    serial_connection = serial.Serial('/dev/ttyACM0', 9600)

    serial_connection.write('r={}\n'.format(r).encode(encoding='UTF-8'))
    time.sleep(0.1)
    serial_connection.write('g={}\n'.format(g).encode(encoding='UTF-8'))
    time.sleep(0.1)
    serial_connection.write('b={}\n'.format(b).encode(encoding='UTF-8'))
    time.sleep(0.1)
    serial_connection.write('a={}\n'.format(blink_speed).encode(encoding='UTF-8'))
    time.sleep(0.1)


def main():
    print('Python LED indicator')

    set_led(123, 255, 60, 300)

    print('Program end')

if __name__ == '__main__':
    main()
