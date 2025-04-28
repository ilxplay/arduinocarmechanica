#include <LedControl.h>

int DIN = 26;
int CS = 27;
int CLK = 28;
LedControl lc=LedControl(DIN, CS, CLK,0);

// Diagonal Right Arrow Pattern (8x8 matrix)
byte rightArrow[8] = {
  B00001000, // Tip of arrow
  B00001100, 
  B00001110,
  B11111111,
  B11111111,
  B00001110,
  B00001100,
  B00001000,  // Base of arrow
};

// Diagonal Left Arrow Pattern (8x8 matrix)
byte leftArrow[8] = {
  B00010000, // Tip of arrow
  B00110000, 
  B01110000,
  B11111111,
  B11111111,
  B01110000,
  B00110000,
  B00010000  // Base of arrow
};

byte straightArrow[8] = {
   B00011000, // Middle column filled
   B00111100, // Wider middle section
   B01111110, // Even wider
   B11111111, // Full top row
   B00011000, // Narrow base
   B00011000,
   B00011000,
   B00011000,
};

byte backArrow[8] = {
   B00011000, // Middle column filled
   B00011000, // Wider middle section
   B00011000, // Even wider
   B00011000, // Full top row
   B11111111, // Narrow base
   B01111110,
   B00111100,
   B00011000,
};

byte sussy[8] = {
   B11111111,
   B11111111,
   B00111100,
   B00011000,
   B00011000,
   B00011000,
   B00011000,
   B00011000,
};

void matrixSetup() {
  lc.shutdown(0, false);   // Wake up display
  lc.setIntensity(0, 8);   // Set brightness (0-15)
  lc.clearDisplay(0);
  
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

void showBackwardArrow() {
  for(int row = 0; row < 8; row++) {
    lc.setRow(0, row, backArrow[row]);
  }
}

void showSussyArrow() {
  for(int row = 0; row < 8; row++) {
    lc.setRow(0, row, sussy[row]);
  }
}
