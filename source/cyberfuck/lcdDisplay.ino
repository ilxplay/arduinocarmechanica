#include <LiquidCrystal.h>
//LiquidCrystal lcd(19, 18, 17, 16, 15, 14); //mega
LiquidCrystal lcd(12, 11, 10, 9, 8, 7); //uno
void lcdSetup() {
lcd.begin(16, 2);
lcd.print("CyberFuck");
}

/*
void lcdLoop() {
}
*/

