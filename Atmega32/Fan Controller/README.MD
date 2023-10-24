# Fan Controller
This project is a Fan Controller implemented in C and programmed onto an Atmega32 microcontroller.

## Description
The Fan Controller project is a system designed to control the speed of a fan based on the temperature measured by an LM35 sensor. The project utilizes an Atmega32 microcontroller along with various peripherals such as GPIO, ADC, and PWM.
The system works by continuously monitoring the temperature using the LM35 sensor. Based on the temperature reading, the microcontroller adjusts the speed of the fan through the PWM (Pulse Width Modulation) technique. The fan speed is displayed on the LCD, allowing the user to easily monitor the cooling system's performance.

## Features

- Temperature sensing using the LM35 sensor.
- Real-time display of temperature and fan speed on the LCD.
- Automatic fan speed adjustment based on temperature.
- PWM control for precise fan speed regulation.
- Simple and user-friendly interface.

## Software Requirements

The software for the Fan Controller project can be developed using any suitable Integrated Development Environment (IDE) that supports Atmega32 microcontroller programming. You will also need the appropriate microcontroller programming toolchain and libraries.

The software should include the following functionalities:

- Initialize the necessary peripherals such as ADC, GPIO, and PWM.
- Implement functions to read temperature from the LM35 sensor.
- Develop logic to adjust the fan speed based on temperature readings.
- Configure the LCD module to display temperature and fan speed.
- Continuously monitor the temperature and update the fan speed accordingly.
- Handle any necessary error conditions or exceptional scenarios.

## Hardware Requirements

To build and run the Fan Controller project, you will need the following components:

- Atmega32 microcontroller.
- LM35 temperature sensor.
- 16x2 LCD module.
- DC motor.
- Power supply for the microcontroller and the motor.

## Conclusion

The Fan Controller project provides an efficient and automated solution for controlling fan speed based on temperature readings. By following the instructions provided in this readme file, you should be able to build and run the project successfully. Feel free to customize and enhance the project according to your requirements.

![alt text]()