# Project3_Fan_Control_System
##Embedded system project to control a fan using a PIC18F4620 MCU.

This control system has two modes:-
1- Automatic Control
2- Manual Control
##Automatic Control Operation:
The fan speed is determined based on the room temperature(T). The temperature is calculated from a sensor temperature readings called LM35.
The sensor is connected with the microcontroller on AN A/D channel pin and convert the analog readings to digital values values using the ADC module inside the MCU.
There is 3 speed levels 1, 2, 3. They are implemented using the CCP1 module inside the MCU.
There are 4 cases:
1- If (T < 18) => The fan speed will be 0 automatically.
2- If (18 <= T < 25) => The fan speed will be 1 automatically.
3- If (25 <= T < 35) => The fan speed will be 2 automatically.
4- If (T >= 35) => The fan speed will be 3 automatically.
##Manual Mode Operation:
The user select the fan speed whatever the temperature is. It also has 3 speed levels 1, 2, 3.

##System Interface:
This system is able to save the last mode choosen by the user before going to reset. This is done by saving the control_mode variable in the first location in the EEPROM.
User must press ##'1' on the keypad to select Automatic mode and ##'2' to select Manual mode.
In Manual mode, press
'1' => speed level 1
'2' => speed level 2
'3' => speed level 3
'4' => turn fan off
In both modes, Press '0' to return to the main menu and select the the control mode.
