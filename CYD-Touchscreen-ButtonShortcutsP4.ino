// VS Code Shortcuts

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

// Array to store custom labels for each button with VS Code shortcuts
const char* buttonLabels[BUTTON_COUNT] = {
  "New File", "Open File", "Save", "Close", 
  "Undo", "Redo", "Replace", "Upload",
  "Terminal", "Debug", "Build", "PlatformIO"
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
    buttons[i].x = BUTTON_X_START + (i % 3) * (BUTTON_WIDTH + BUTTON_SPACING); // 3 columns
    buttons[i].y = BUTTON_Y_START + (i / 3) * (BUTTON_HEIGHT + BUTTON_SPACING);
    buttons[i].pressed = false;
    drawButton(i);
  }

  // Map each button to a specific keyboard function for VS Code
  buttonFunctions[0] = &newFileFunction;        // New File (Ctrl + N)
  buttonFunctions[1] = &openFileFunction;       // Open File (Ctrl + O)
  buttonFunctions[2] = &saveFunction;            // Save (Ctrl + S)
  buttonFunctions[3] = &closeFunction;           // Close Editor (Ctrl + W)
  buttonFunctions[4] = &undoFunction;            // Undo (Ctrl + Z)
  buttonFunctions[5] = &redoFunction;            // Redo (Ctrl + Y)
  buttonFunctions[6] = &replaceFunction;         // Replace (Ctrl + H)
  buttonFunctions[7] = &uploadFunction;          // Upload (Ctrl + Shift + P for command palette)
  buttonFunctions[8] = &terminalFunction;        // Open Terminal (Ctrl + Backspace)
  buttonFunctions[9] = &debugFunction;           // Start Debugging (F5)
  buttonFunctions[10] = &buildFunction;          // Build (Ctrl + Shift + B)
  buttonFunctions[11] = &platformIOFunction;     // Open PlatformIO Home (Ctrl + Shift + P)

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

// Keyboard function definitions for VS Code shortcuts
void newFileFunction() {
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press('n'); // Ctrl + N
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

void closeFunction() {
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press('w'); // Ctrl + W
  bleKeyboard.releaseAll();
}

void undoFunction() {
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press('z'); // Ctrl + Z
  bleKeyboard.releaseAll();
}

void redoFunction() {
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press('y'); // Ctrl + Y
  bleKeyboard.releaseAll();
}

void replaceFunction() {
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press('h'); // Ctrl + H
  bleKeyboard.releaseAll();
}

void uploadFunction() {
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press(KEY_LEFT_SHIFT);
  bleKeyboard.press('p'); // Ctrl + Shift + P to open command palette
  bleKeyboard.releaseAll();
}

void terminalFunction() {
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press(KEY_BACKSPACE); // Ctrl + Backspace
  bleKeyboard.releaseAll();
}

void debugFunction() {
  bleKeyboard.press(KEY_F5); // F5
  bleKeyboard.releaseAll();
}

void buildFunction() {
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press(KEY_LEFT_SHIFT);
  bleKeyboard.press('b'); // Ctrl + Shift + B
  bleKeyboard.releaseAll();
}

void platformIOFunction() {
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press(KEY_LEFT_SHIFT);
  bleKeyboard.press('p'); // Ctrl + Shift + P to open command palette
  bleKeyboard.releaseAll();
}
