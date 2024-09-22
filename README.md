This keyboard library is meant for using the PS/2 port thats connected to a esp32 using FabGL libraries and scancode. i did not see the ability to use all keys with keyboard library setup for ps/2 port in any other builds so that is the main purpose to make it easy for old keyboards before usb hid. this verion should be able to be updated with more precise key presses and scancodes in the future

* Numlock/Capslock/Scrolllock leds work

* Keyboard arrows letters and numbers all work
  
* Crtl and F1 copy to and F2 paste the clipboard F3 F4 vol up down works.
 
* This code was tested on TTGO VGA V1.4 Controller PS/2 port but should work with esp32, might need resistors..
  
* There are a some issues that need to be worked out on the timing. the F keys can all be programed to have macro functions with vk. main issues is occasional letter doubling need for vk to use Enter
  
* Control acts as the VK switch key and have to use it to use enter for some reason. Enter can be programed into a F key as a workaround with the use of crtl(VK Virtual Key).
  
* Not all characters features work on number pad. this code could be redone without FabGL to use PS/2 port and be much more precise with button up and down pushes.
* Works on linux, Android and Windows

* Need to integrate mouse into project

* FabGl library for scancodes, ps/2 and other features https://github.com/fdivitto/FabGL
* https://github.com/T-vK/ESP32-BLE-Keyboard libraries 

* Used both above libraries together and chatgpt with lots of debugging to make this happen

I recommend the LILYGO® TTGO VGA V1.4 Controller to make it easy or wire up the ps/2 wiring correctly with needed resistors ect. the pins in the code are  PS2_KEYBOARD_DATA_PIN 32
and PS2_KEYBOARD_CLOCK_PIN 33 set for the ttgo VGA v1.4 controller https://www.lilygo.cc/products/fabgl-vga32 (no affiliation)
![20240921_040127](https://github.com/user-attachments/assets/38654779-f7c5-438c-9aa3-c6c1fbf4c5e9)
