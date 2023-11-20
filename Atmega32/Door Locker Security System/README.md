# Door Locker Security System

##Project Overview
The Door Locker Security System is a ATmega32 microcontroller-based security system designed to control access to a secured area using a password-protected mechanism. The project utilizes two ATmega32 microcontrollers operating at a frequency of 8MHz and is structured based on a layered architecture for modularity and efficient design.

- HMI_ECU (Human-Machine Interface)
The HMI_ECU is responsible for user interaction. It receives inputs from the keypad and displays relevant messages on the LCD screen. Its primary purpose is to bridge the communication between the user and the system.

- CONTROL_ECU (Control Electronic Control Unit)
The CONTROL_ECU is the brain of the system, responsible for processing and decision-making. It handles tasks such as password validation, door opening, and system alarm activation. This unit ensures the security and proper functioning of the Door Locker Security System.

##System Operation Sequence
Step 1 : Create a System Password:
			1) The LCD should display "ENTER NEW PASS".
			2) Enter a password consists of 5 numbers, Display * in the screen for each number.
			3) Press enter button (ON Button).
			4) Ask the user to renter the same password for confirmation by display this message "REENTER NEW PASS".
			5) Enter a password consists of 5 numbers, Display * in the screen for each number.
			6) Press enter button (ON Button).
			7) HMI_ECU should send the two passwords to the Control_ECU through the UART.
			8) If the two passwords are matched then the system has a password now and save it inside the EEPORM and go to Step 2.
			9) If the two passwords are unmatched then repeat step 1 again.
Step 2 : Main Options:
			1) The LCD will always display the main system option.
				"+ : OPEN DOOR"
				"- : CHANGE PASS"
			2) If the user selects the option to open the door go to Step 3
			3) If the user chooses to change the password go to Step 4
Step 3 : Open Door:
			1) The LCD should display "ENTER PASSWORD".
			2) Enter the password then press enter button (ON Button).
			3) HMI_ECU should send the Password to the Control_ECU and it should compare it with the one saved in the EEPROM.
			4) If two passwords are matched:
				- rotates motor for 15-seconds CW and display a message on the screen "DOOR IS OPENING".
				- hold the motor for 3-seconds.
				- rotates motor for 15-seconds A-CW and display a message on the screen "DOOR IS CLOSEING".
Step 4 : Change Password:
			1) The LCD should display "ENTER PASSWORD".
			2) Enter the password then press enter button (ON Button).
			3) HMI_ECU should send the Password to the Control_ECU and it should compare it with the one saved in the EEPROM.
			4) If two passwords are matched:
				- Repeat Step 1.
Step 5 : if the two passwords are unmatched at step 3 (Open Door) or step 4 (Change Password).
			1) Ask the user one more time for the password.
			2) Enter the password then press enter button (ON Button).
			3) HMI_ECU should send the Password to the Control_ECU and it should compare it with the one saved in the EEPROM.
			4) If two passwords are matched then open the door or change the password in steps 3 and 4.
			5) If the two passwords are not matched again then ask the user one last time for the password.
			6) If two passwords are matched then open the door or change the password in steps 3 and 4.
			7) If the two passwords are not matched for the third consecutive time then:
				- Activate Buzzer for 1-minute.
				- Display error message on LCD for 1 minute.
				- System should be locked no inputs from Keypad will be accepted during this time period.
				- Go to Step 2 the main options again.
				
##Components
1. ATmega32 Microcontrollers
2. LCD 2x16
3. 4x4 Keypad
4. External EEPROM
5. Buzzer
6. DC Motor

##Future Enhancements
Explore potential enhancements such as Remember The System Login , additional security layers.

