// Youtube Shortcuts

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

// Array to store custom labels for each button with YouTube shortcuts
const char* buttonLabels[BUTTON_COUNT] = {
  "Play/Pa", "Vol U", "Vol D", "FullScr", 
  "Exit FS", "NextVid", "PrevVid", "Mute/Un",
  "CC", "Stats", "Seek F", "Seek B"
};

void setup() {
  lcd.begin(DISPLAY_CYD); // Initialize the LCD
  lcd.fillScreen(TFT_BLACK);
  lcd.setFont(FONT_12x16);
  lcd.setTextColor(TFT_GREEN, TFT_BLACK);
  lcd.println("YouTube Remote");

  // Initialize BLE keyboard
  bleKeyboard.begin();
  
  // Initialize buttons
  for (int i = 0; i < BUTTON_COUNT; i++) {
    buttons[i].x = BUTTON_X_START + (i % 3) * (BUTTON_WIDTH + BUTTON_SPACING); // 3 columns
    buttons[i].y = BUTTON_Y_START + (i / 3) * (BUTTON_HEIGHT + BUTTON_SPACING);
    buttons[i].pressed = false;
    drawButton(i);
  }

  // Map each button to a specific keyboard function for YouTube shortcuts
  buttonFunctions[0] = &playPauseFunction;         // Play/Pause (Spacebar)
  buttonFunctions[1] = &volumeUpFunction;          // Volume Up (KEY_PAGE_UP)
  buttonFunctions[2] = &volumeDownFunction;        // Volume Down (KEY_PAGE_DOWN)
  buttonFunctions[3] = &fullScreenFunction;        // Full Screen (KEY_F9)
  buttonFunctions[4] = &exitFullScreenFunction;    // Exit Full Screen (Esc)
  buttonFunctions[5] = &nextVideoFunction;         // Next Video (Shift + N)
  buttonFunctions[6] = &previousVideoFunction;     // Previous Video (Shift + P)
  buttonFunctions[7] = &muteUnmuteFunction;        // Mute/Unmute (M)
  buttonFunctions[8] = &toggleCaptionsFunction;    // Closed Captions (C)
  buttonFunctions[9] = &statsForNerdsFunction;     // Stats for Nerds (Ctrl + Shift + N)
  buttonFunctions[10] = &seekForwardFunction;      // Seek Forward (L)
  buttonFunctions[11] = &seekBackwardFunction;     // Seek Backward (J)

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

// Keyboard function definitions for YouTube shortcuts
void playPauseFunction() {
  bleKeyboard.press(' '); // Spacebar for Play/Pause
  bleKeyboard.releaseAll();
}

void volumeUpFunction() {
  bleKeyboard.press(KEY_PAGE_UP); // Volume Up
  bleKeyboard.releaseAll();
}

void volumeDownFunction() {
  bleKeyboard.press(KEY_PAGE_DOWN); // Volume Down
  bleKeyboard.releaseAll();
}

void fullScreenFunction() {
  bleKeyboard.press(KEY_F9); // F9 for Full Screen
  bleKeyboard.releaseAll();
}

void exitFullScreenFunction() {
  bleKeyboard.press(KEY_ESC); // Esc for Exit Full Screen
  bleKeyboard.releaseAll();
}

void nextVideoFunction() {
  bleKeyboard.press(KEY_LEFT_SHIFT);
  bleKeyboard.press('n'); // Shift + N for Next Video
  bleKeyboard.releaseAll();
}

void previousVideoFunction() {
  bleKeyboard.press(KEY_LEFT_SHIFT);
  bleKeyboard.press('p'); // Shift + P for Previous Video
  bleKeyboard.releaseAll();
}

void muteUnmuteFunction() {
  bleKeyboard.press('m'); // M for Mute/Unmute
  bleKeyboard.releaseAll();
}

void toggleCaptionsFunction() {
  bleKeyboard.press('c'); // C for Closed Captions
  bleKeyboard.releaseAll();
}

void statsForNerdsFunction() {
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press(KEY_LEFT_SHIFT);
  bleKeyboard.press('n'); // Ctrl + Shift + N for Stats for Nerds
  bleKeyboard.releaseAll();
}

void seekForwardFunction() {
  bleKeyboard.press('l'); // L for Seek Forward
  bleKeyboard.releaseAll();
}

void seekBackwardFunction() {
  bleKeyboard.press('j'); // J for Seek Backward
  bleKeyboard.releaseAll();
}
