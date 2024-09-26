#include <BleKeyboard.h>
#include "fabgl.h"

// Define PS/2 Keyboard pins for TTGO VGA ESP32 v1.4
#define PS2_KEYBOARD_DATA_PIN 32
#define PS2_KEYBOARD_CLOCK_PIN 33

// Initialize the BLE Keyboard
BleKeyboard bleKeyboard("ESP32 BLE Keyboard", "TTGO_ESP32", 100);

// Initialize the fabgl PS2 controller
fabgl::PS2Controller PS2Controller;

// Key press tracking
bool keyPressed[256] = { false };  // Array to track the state of each key (pressed or not)

// Timing variables
unsigned long lastKeyPressTime[256] = { 0 };
const unsigned long debounceDelay = 50;  // Debounce time for key press in milliseconds
const unsigned long holdTime = 200;     // Time to consider a key press as long in milliseconds

void setup()
{
  Serial.begin(115200);
  delay(500);  // Avoid garbage into the UART
  Serial.println("Reset");

  // Initialize PS2 Keyboard
  PS2Controller.begin(PS2Preset::KeyboardPort0);

  // Initialize BLE Keyboard
  bleKeyboard.begin();

  Serial.println("Keyboard and Bluetooth setup completed");
}

void loop()
{
  auto keyboard = PS2Controller.keyboard();

  // Handle Serial Commands
  if (Serial.available() > 0) {
    char c = Serial.read();
    switch (c) {
      case '1':
        keyboard->setLayout(&fabgl::USLayout);
        Serial.println("US Layout set");
        break;
      case '2':
        keyboard->setLayout(&fabgl::UKLayout);
        Serial.println("UK Layout set");
        break;
      case '3':
        keyboard->setLayout(&fabgl::GermanLayout);
        Serial.println("DE Layout set");
        break;
      case 'r':
        keyboard->reset();
        Serial.println("Keyboard reset");
        break;
    }
  }

  // Handle PS/2 Keyboard Input
  if (keyboard->virtualKeyAvailable()) {
    fabgl::VirtualKeyItem item;
    if (keyboard->getNextVirtualKey(&item)) {
      unsigned long currentTime = millis();
      char key = item.ASCII ? item.ASCII : item.vk;

      // Handle key press registration
      if (item.ASCII) {
        if (!keyPressed[key] && (currentTime - lastKeyPressTime[key] > debounceDelay)) {
          if (bleKeyboard.isConnected()) {
            bleKeyboard.write(item.ASCII);  // Send ASCII character over BLE
          }
          lastKeyPressTime[key] = currentTime;
          keyPressed[key] = true;
        }
      } else {
        // Handle special virtual keys
        switch (item.vk) {
          case fabgl::VK_BACKSPACE:
            if (!keyPressed[KEY_BACKSPACE] && (currentTime - lastKeyPressTime[KEY_BACKSPACE] > debounceDelay)) {
              if (bleKeyboard.isConnected()) {
                bleKeyboard.write(KEY_BACKSPACE);
              }
              lastKeyPressTime[KEY_BACKSPACE] = currentTime;
              keyPressed[KEY_BACKSPACE] = true;
            }
            break;
          case fabgl::VK_RETURN:
            if (!keyPressed[KEY_RETURN] && (currentTime - lastKeyPressTime[KEY_RETURN] > debounceDelay)) {
              if (bleKeyboard.isConnected()) {
                bleKeyboard.write(KEY_RETURN);
              }
              lastKeyPressTime[KEY_RETURN] = currentTime;
              keyPressed[KEY_RETURN] = true;
            }
            break;
          case fabgl::VK_ESCAPE:
            if (!keyPressed[KEY_ESC] && (currentTime - lastKeyPressTime[KEY_ESC] > debounceDelay)) {
              if (bleKeyboard.isConnected()) {
                bleKeyboard.write(KEY_ESC);
              }
              lastKeyPressTime[KEY_ESC] = currentTime;
              keyPressed[KEY_ESC] = true;
            }
            break;
          case fabgl::VK_F1:
            if (!keyPressed[KEY_F1] && (currentTime - lastKeyPressTime[KEY_F1] > debounceDelay)) {
              if (bleKeyboard.isConnected()) {
                // Simulate Ctrl + V (paste)
                bleKeyboard.press(KEY_LEFT_CTRL);
                bleKeyboard.press('v');  // 'v' key for paste
                bleKeyboard.releaseAll();
              }
              lastKeyPressTime[KEY_F1] = currentTime;
              keyPressed[KEY_F1] = true;
            }
            break;
          case fabgl::VK_LEFT:
            if (!keyPressed[KEY_LEFT_ARROW] && (currentTime - lastKeyPressTime[KEY_LEFT_ARROW] > debounceDelay)) {
              if (bleKeyboard.isConnected()) {
                bleKeyboard.write(KEY_LEFT_ARROW);
              }
              lastKeyPressTime[KEY_LEFT_ARROW] = currentTime;
              keyPressed[KEY_LEFT_ARROW] = true;
            }
            break;
          case fabgl::VK_UP:
            if (!keyPressed[KEY_UP_ARROW] && (currentTime - lastKeyPressTime[KEY_UP_ARROW] > debounceDelay)) {
              if (bleKeyboard.isConnected()) {
                bleKeyboard.write(KEY_UP_ARROW);
              }
              lastKeyPressTime[KEY_UP_ARROW] = currentTime;
              keyPressed[KEY_UP_ARROW] = true;
            }
            break;
          case fabgl::VK_RIGHT:
            if (!keyPressed[KEY_RIGHT_ARROW] && (currentTime - lastKeyPressTime[KEY_RIGHT_ARROW] > debounceDelay)) {
              if (bleKeyboard.isConnected()) {
                bleKeyboard.write(KEY_RIGHT_ARROW);
              }
              lastKeyPressTime[KEY_RIGHT_ARROW] = currentTime;
              keyPressed[KEY_RIGHT_ARROW] = true;
            }
            break;
          case fabgl::VK_DOWN:
            if (!keyPressed[KEY_DOWN_ARROW] && (currentTime - lastKeyPressTime[KEY_DOWN_ARROW] > debounceDelay)) {
              if (bleKeyboard.isConnected()) {
                bleKeyboard.write(KEY_DOWN_ARROW);
              }
              lastKeyPressTime[KEY_DOWN_ARROW] = currentTime;
              keyPressed[KEY_DOWN_ARROW] = true;
            }
            break;
          // Add more cases as needed for other keys
        }
      }
    }
  }

  // Release key states after debounce delay
  unsigned long currentTime = millis();
  for (int i = 0; i < 256; ++i) {
    if (keyPressed[i] && (currentTime - lastKeyPressTime[i] > holdTime)) {
      keyPressed[i] = false;
    }
  }
}
