#include <LedControl.h>

int DIN = 31;
int CS = 32;
int CLK = 33;
LedControl lc=LedControl(DIN, CLK, CS,0);

// Diagonal Right Arrow Pattern (8x8 matrix)
byte rightArrow[8] = {
  B00000001, // Tip of arrow
  B00000011, 
  B00000110,
  B00001100,
  B00011000,
  B00110000,
  B01100000,
  B11000000  // Base of arrow
};

// Diagonal Left Arrow Pattern (8x8 matrix)
byte leftArrow[8] = {
  B11110000, // Tip of arrow
  B11000000, 
  B10100000,
  B10010000,
  B00001000,
  B00000100,
  B00000010,
  B00000001  // Base of arrow
};

byte straightArrow[8] = {
  B00011000, // Middle column filled
  B00111100, // Wider middle section
  B01111110, // Even wider
  B11111111, // Full top row
  B00011000, // Narrow base
  B00011000,
  B00011000,
  B00011000
};

void matrixSetup() {
  lc.shutdown(0, false);   // Wake up display
  lc.setIntensity(0, 8);   // Set brightness (0-15)
  lc.clearDisplay(0);      // Clear the display
}

void showRightArrow() {
  for(int row = 0; row < 8; row++) {
    lc.setRow(0, row, rightArrow[row]);
  }
}

void showLeftArrow() {
  for(int row = 0; row < 8; row++) {
    lc.setRow(0, row, leftArrow[row]);
  }
}

void showStraightArrow() {
  for(int row = 0; row < 8; row++) {
    lc.setRow(0, row, straightArrow[row]);
  }
}
