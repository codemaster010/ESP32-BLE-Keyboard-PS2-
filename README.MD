ESP32-BLE-Keyboard library with ESP32 Cheap Yellow Display Board – CYD (ESP32-2432S028R)

* Button color change with touch
* Fast access to valuable shorcuts
* Ble Connection to Raspberry Pi, Android and Windows (Not fully tested)
* Easy to read button labels can edit in the array
* Multiple functions to perform shorcuts
* Easy to load in arduino Ide
* Page top labels

  
To do, WIP: integrate 5 pages, navigation and correct shortcuts/functions into one .ino file.

![Alt text](https://github.com/codemaster010/ESP32-BLE-Keyboard-PS2-/blob/ESP32-BLE-Keyboard-CYD-ButtonShortcuts/ESP32_CYD_28R.jpg)


this library is a build of the esp32 BLE Library to use the CYD 2.8 inch Screen to give the screen the functionality of a remote bluetooth button system that sends shortcuts to the OS its connected to. not all features are fully tested so user warning is advised until its fully tested. each .ino file has a different system of buttons for example P1 is General shortcuts, P2 is firefox shortcuts, p3 is arduino ide, p4 is vs code and p5 is youtube shortcuts. my goal is to integrate 5 pages in the .ino file but there are more bugs to work out for that.

Legal Disclaimer: by using this software you hold the creater not accountable if any issues arise, all use of this software is up to the the user to know his or her countries laws. this software is intended for use as an aid to help with certain tasks on the computer.



Huge Thanks to https://github.com/witnessmenow/ESP32-Cheap-Yellow-Display for providing so much help and examples

-------------------------------------------------------------------------------------------------------------------------------------------

T-vK Credits from Readme for Ble Keyboard Library:
https://github.com/T-vK/ESP32-BLE-Keyboard
All original files are accompanied in folders
Credits to chegewara and the authors of the USB keyboard library as this project is heavily based on their work!
Also, credits to duke2421 who helped a lot with testing, debugging and fixing the device descriptor! And credits to sivar2311 for adding NimBLE support, greatly reducing the memory footprint, fixing advertising issues and for adding the setDelay method.
https://github.com/chegewara
https://github.com/sivar2311
https://github.com/T-vK/ESP32-BLE-Keyboard/issues/1

https://github.com/arduino-libraries/Keyboard/
License Keyboard Library for Arduino

Copyright (c) Arduino LLC. All right reserved.

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

