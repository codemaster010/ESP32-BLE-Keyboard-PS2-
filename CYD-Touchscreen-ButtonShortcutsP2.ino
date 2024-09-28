// Firefox Shortcuts

#include "bb_spi_lcd.h"
#include "BleKeyboard.h" // BLE Keyboard library

BB_SPI_LCD lcd;
BleKeyboard bleKeyboard;

#define BUTTON_COUNT 12
#define BUTTON_WIDTH 90
#define BUTTON_HEIGHT 50
#define BUTTON_SPACING 5
#define BUTTON_X_START 20
#define BUTTON_Y_START 20

struct Button {
  int x, y;
  bool pressed;
};

Button buttons[BUTTON_COUNT];

// Array to map each button to a specific function
void (*buttonFunctions[BUTTON_COUNT])();

// Array to store custom labels for each button with new features
const char* buttonLabels[BUTTON_COUNT] = {
  "Select", "Copy All", "Close App", "Refresh", 
  "New Tab", "Open File", "Save", "Print", 
  "Find", "Zoom In", "Zoom Out", "Help"
};

void setup() {
  lcd.begin(DISPLAY_CYD); // Initialize the LCD
  lcd.fillScreen(TFT_BLACK);
  lcd.setFont(FONT_12x16);
  lcd.setTextColor(TFT_GREEN, TFT_BLACK);
  lcd.println("Command Center");

  // Initialize BLE keyboard
  bleKeyboard.begin();
  
  // Initialize buttons
  for (int i = 0; i < BUTTON_COUNT; i++) {
    buttons[i].x = BUTTON_X_START + (i % 3) * (BUTTON_WIDTH + BUTTON_SPACING);
    buttons[i].y = BUTTON_Y_START + (i / 3) * (BUTTON_HEIGHT + BUTTON_SPACING);
    buttons[i].pressed = false;
    drawButton(i);
  }

  // Map each button to a new specific keyboard function
  buttonFunctions[0] = &selectFunction;       // Select (Shift + Arrow keys)
  buttonFunctions[1] = &copyAllFunction;      // Copy All (Ctrl + A)
  buttonFunctions[2] = &closeAppFunction;      // Close App (Alt + F4)
  buttonFunctions[3] = &refreshFunction;       // Refresh (F5)
  buttonFunctions[4] = &newTabFunction;        // New Tab (Ctrl + T)
  buttonFunctions[5] = &openFileFunction;      // Open File (Ctrl + O)
  buttonFunctions[6] = &saveFunction;          // Save (Ctrl + S)
  buttonFunctions[7] = &printFunction;         // Print (Ctrl + P)
  buttonFunctions[8] = &findFunction;          // Find (Ctrl + F)
  buttonFunctions[9] = &zoomInFunction;        // Zoom In (Ctrl + =)
  buttonFunctions[10] = &zoomOutFunction;      // Zoom Out (Ctrl + -)
  buttonFunctions[11] = &helpFunction;         // Help (F1)

  lcd.rtInit(); // Initialize the resistive touch controller
}

void drawButton(int index) {
  if (buttons[index].pressed) {
    lcd.fillRect(buttons[index].x, buttons[index].y, BUTTON_WIDTH, BUTTON_HEIGHT, TFT_GREY);
  } else {
    lcd.fillRect(buttons[index].x, buttons[index].y, BUTTON_WIDTH, BUTTON_HEIGHT, TFT_BLUE);
  }
  
  lcd.setCursor(buttons[index].x + 5, buttons[index].y + 10);
  lcd.setTextColor(TFT_WHITE, buttons[index].pressed ? TFT_GREY : TFT_BLUE);
  lcd.printf("%s", buttonLabels[index]); // Use custom label
}

void loop() {
  TOUCHINFO ti;
  
  while (1) {
    lcd.rtReadTouch(&ti);
    for (int i = 0; i < BUTTON_COUNT; i++) {
      if (ti.count > 0 && ti.x[0] >= buttons[i].x && ti.x[0] <= (buttons[i].x + BUTTON_WIDTH) &&
          ti.y[0] >= buttons[i].y && ti.y[0] <= (buttons[i].y + BUTTON_HEIGHT)) {
        
        if (!buttons[i].pressed) {
          buttons[i].pressed = true;
          drawButton(i);
          Serial.printf("Button %d pressed\n", i + 1);
          
          // Trigger the associated keyboard function
          if (bleKeyboard.isConnected()) {
            buttonFunctions[i](); // Call the function associated with the button
          }
        }
      } else {
        if (buttons[i].pressed) {
          buttons[i].pressed = false;
          drawButton(i);
          Serial.printf("Button %d released\n", i + 1);
        }
      }
    }
    
    delay(50);
  }
}

// Keyboard function definitions with new features
void selectFunction() {
  // Simulate selecting text
  bleKeyboard.press(KEY_LEFT_SHIFT);
  bleKeyboard.press(KEY_LEFT_ARROW); // Shift + Arrow key to select
  bleKeyboard.releaseAll();
}

void copyAllFunction() {
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press('a'); // Ctrl + A
  bleKeyboard.releaseAll();
}

void closeAppFunction() {
  bleKeyboard.press(KEY_LEFT_ALT);
  bleKeyboard.press(KEY_F4); // Alt + F4
  bleKeyboard.releaseAll();
}

void refreshFunction() {
  bleKeyboard.press(KEY_F5); // F5
  bleKeyboard.releaseAll();
}

void newTabFunction() {
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press('t'); // Ctrl + T
  bleKeyboard.releaseAll();
}

void openFileFunction() {
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press('o'); // Ctrl + O
  bleKeyboard.releaseAll();
}

void saveFunction() {
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press('s'); // Ctrl + S
  bleKeyboard.releaseAll();
}

void printFunction() {
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press('p'); // Ctrl + P
  bleKeyboard.releaseAll();
}

void findFunction() {
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press('f'); // Ctrl + F
  bleKeyboard.releaseAll();
}

void zoomInFunction() {
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press('='); // Ctrl + = to zoom in
  bleKeyboard.releaseAll();
}

void zoomOutFunction() {
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press('-'); // Ctrl + - to zoom out
  bleKeyboard.releaseAll();
}

void helpFunction() {
  bleKeyboard.press(KEY_F1); // F1
  bleKeyboard.releaseAll();
}
