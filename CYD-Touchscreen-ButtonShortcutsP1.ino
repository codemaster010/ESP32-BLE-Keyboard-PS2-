// General Shortcuts

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

// Array to store custom labels for each button
const char* buttonLabels[BUTTON_COUNT] = {
  "Copy", "Paste", "Select", "Cut", "Undo", "Redo", 
  "Vol U", "Vol D", "Mute", "Play/P", "Next", "Back"
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

  // Map each button to a specific keyboard function
  buttonFunctions[0] = &copyFunction;
  buttonFunctions[1] = &pasteFunction;
  buttonFunctions[2] = &selectAllFunction;
  buttonFunctions[3] = &cutFunction;
  buttonFunctions[4] = &undoFunction;
  buttonFunctions[5] = &redoFunction;
  buttonFunctions[6] = &volumeUpFunction;
  buttonFunctions[7] = &volumeDownFunction;
  buttonFunctions[8] = &muteFunction;
  buttonFunctions[9] = &playPauseFunction;
  buttonFunctions[10] = &nextTrackFunction;
  buttonFunctions[11] = &previousTrackFunction;

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

// Keyboard function definitions
void copyFunction() {
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press('c');
  bleKeyboard.releaseAll();
}

void pasteFunction() {
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press('v');
  bleKeyboard.releaseAll();
}

void selectAllFunction() {
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press('a');
  bleKeyboard.releaseAll();
}

void cutFunction() {
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press('x');
  bleKeyboard.releaseAll();
}

void undoFunction() {
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press('z');
  bleKeyboard.releaseAll();
}

void redoFunction() {
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press(KEY_LEFT_SHIFT);
  bleKeyboard.press('z');
  bleKeyboard.releaseAll();
}

void volumeUpFunction() {
  bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
}

void volumeDownFunction() {
  bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
}

void muteFunction() {
  bleKeyboard.write(KEY_MEDIA_MUTE);
}

void playPauseFunction() {
  bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
}

void nextTrackFunction() {
  bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
}

void previousTrackFunction() {
  bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
}
 
