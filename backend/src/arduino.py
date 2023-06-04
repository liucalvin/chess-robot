import serial
import time


def _read_until_empty(arduino, sleep_time=0.1):
    time.sleep(sleep_time)
    messages = []
    message = arduino.read_until()
    while message:
        print(message.decode())
        messages.append(message)
        message = arduino.read_until()

    return messages


def write_to_arduino(sleep_time=0.1, handshake_code="8"):
    with serial.Serial(port='COM3', baudrate=9600, timeout=1) as arduino:
        arduino.close()
        arduino.open()

        time.sleep(sleep_time)

        timeout = arduino.timeout
        arduino.timeout = sleep_time

        _ = arduino.read_all()
        arduino.flush()
        _read_until_empty(arduino)

        arduino.write(bytes(handshake_code, 'utf-8'))
        _read_until_empty(arduino)

        arduino.write(bytes("8", 'utf-8'))
        _read_until_empty(arduino)

        arduino.write(bytes("601", 'utf-8'))
        _read_until_empty(arduino)

        arduino.write(bytes("1002", 'utf-8'))
        _read_until_empty(arduino)

        arduino.write(bytes("9", 'utf-8'))
        _read_until_empty(arduino)

        arduino.timeout = timeout


def control_arduino(sleep_time=1, current_position_code="5", handshake_code="8", reset_code="9"):
    with serial.Serial(port='COM3', baudrate=9600, timeout=1) as arduino:
        arduino.close()
        arduino.open()

        time.sleep(sleep_time)

        timeout = arduino.timeout
        arduino.timeout = sleep_time

        _ = arduino.read_all()
        arduino.flush()
        _read_until_empty(arduino)

        arduino.write(bytes(handshake_code, 'utf-8'))
        _read_until_empty(arduino)

        continue_play = True
        while (continue_play):
            selection = input("""
              Enter selection. 
              Press C for current motor positions, or Q to quit.
            """)
            if selection == "Q":
                continue_play = False
                print("Resetting motors to defualt positions")
                arduino.write(bytes(reset_code, 'utf-8'))
                _read_until_empty(arduino)
            elif selection == "C":
                print("Current motor positions:")
                arduino.write(bytes(current_position_code, 'utf-8'))
                _read_until_empty(arduino)
            else:
                arduino.write(bytes(selection, 'utf-8'))
                _read_until_empty(arduino)

        arduino.timeout = timeout


# write_to_arduino()
control_arduino()

