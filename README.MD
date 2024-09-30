ESP32-BLE-Keyboard library with ESP32 Cheap Yellow Display Board – CYD (ESP32-2432S028R)

* Button color change with touch
* Fast access to valuable shorcuts
* Ble Connection to Raspberry Pi, Android and Windows (Not fully tested)
* Easy to read button labels can edit in the array
* Multiple functions to perform shorcuts
* Easy to load in arduino Ide
* Page top labels
* Accurate buttons
* Great response times

Install using arduino ide 1.8.19   | use library ble keyboard is by author Tv-k and install library bb_spi_lcd.h by larry bank through Arduino IDE library manager

![Alt text](https://github.com/codemaster010/ESP32-BLE-Keyboard-PS2-/blob/ESP32-BLE-Keyboard-CYD-ButtonShortcuts/ESP32_CYD_28R.jpg)

To do, WIP: integrate 5 pages, navigation and correct shortcuts/functions into one .ino file.

this library is a build of the esp32 BLE Library to use the CYD 2.8 inch Screen to give the screen the functionality of a remote bluetooth button system that sends shortcuts to the OS,robotics or what ever its connected to. not all features are fully tested so user warning is advised until its fully tested. each .ino file has a different system of buttons for example P1.ino is General shortcuts, P2 is firefox shortcuts, p3 is arduino ide, p4 is vs code and p5 is youtube shortcuts. my goal is to integrate 5 pages in the .ino file but there are more bugs to work out for that.

Credits:

Huge Thanks to https://github.com/witnessmenow/ESP32-Cheap-Yellow-Display for providing so much help and examples

-------------------------------------------------------------------------------------------------------------------------------------------
Previous credits from fork:

T-vK Credits from Readme for Ble Keyboard Library:
https://github.com/T-vK/ESP32-BLE-Keyboard
All original files are accompanied in folders
Credits to chegewara and the authors of the USB keyboard library as this project is heavily based on their work!
Also, credits to duke2421 who helped a lot with testing, debugging and fixing the device descriptor! And credits to sivar2311 for adding NimBLE support, greatly reducing the memory footprint, fixing advertising issues and for adding the setDelay method.
https://github.com/chegewara
https://github.com/sivar2311
https://github.com/T-vK/ESP32-BLE-Keyboard/issues/1

--------------------------------------------------------------------------------------------------------------------------------------------

https://github.com/arduino-libraries/Keyboard/
License Keyboard Library for Arduino

Copyright (c) Arduino LLC. All right reserved.

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Here is a more comprehensive and detailed legal disclaimer for your software:

Legal Disclaimer:

By using this software, you acknowledge and agree to the following:

No Warranty or Liability:
This software is provided "as-is," without any express or implied warranties, including but not limited to warranties of merchantability, fitness for a particular purpose, or non-infringement. The creator expressly disclaims any liability for any direct, indirect, incidental, special, or consequential damages, including but not limited to data loss, device malfunction, financial losses, or other issues resulting from the use or misuse of this software. Users agree that any reliance on this software is entirely at their own risk.

Intended Use:
This software is designed for personal, educational, or professional purposes as a tool to assist with tasks related to computers, operating systems, and robotics. It is not intended for use in safety-critical, life-support, or high-risk environments, such as those involving medical devices, aerospace, or industrial machinery where failure or malfunction could lead to death, injury, or environmental harm. Users should assess the suitability of this software for their particular use case.

Compliance with Laws:
Users are solely responsible for ensuring that their use of this software is in full compliance with all applicable local, state, national, and international laws, regulations, and standards, including but not limited to those related to software licensing, data privacy, intellectual property, and cybersecurity. The creator disclaims any responsibility for violations of such laws or regulations resulting from the use of this software. Users are advised to consult legal or compliance professionals to ensure their usage is lawful.

Assumption of Risk:
By using this software, users assume all responsibility for any consequences arising from its use, including but not limited to:
Hardware or software malfunctions, failures, or damage to devices.
Unintended or undesired interactions with other software or systems.
Legal issues or liabilities resulting from improper or unauthorized use of the software.
Potential security vulnerabilities or data breaches resulting from incorrect implementation or usage.
Users must take appropriate precautions, including regular backups, to protect against data loss or hardware damage.

modifications and Third-Party Integrations:
Any modifications, alterations, or additions made to this software by the user or third parties are done at the user's own risk. The creator disclaims any responsibility for issues arising from such modifications or from the integration of this software with third-party hardware or software. Users are responsible for ensuring the compatibility and stability of any such integrations.

No Technical Support Guarantee:
The creator is under no obligation to provide technical support, updates, patches, or bug fixes. Any such assistance, if offered, is provided at the creator’s discretion and without any guarantees.

Indemnification:
Users agree to indemnify, defend, and hold harmless the creator from and against any claims, liabilities, damages, losses, and expenses (including legal fees) arising out of or in any way connected with their use or misuse of the software, including violations of any third-party rights or applicable laws.

