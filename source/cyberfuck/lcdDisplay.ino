#include <LiquidCrystal.h>

LiquidCrystal lcd(27, 26, 25, 24, 23, 22);

void lcdSetup() {
  lcd.begin(16, 2);
  lcd.print("CyberFuck");
}

void lcdLoop() {
  
  lcd.setCursor(0, 1);
  lcd.clear();

  if(obstacleAvoidanceEnabled == true)
  {
    lcd.print("Autopilot enabled");
  }
  else{
    lcd.print("Autopilot Disabled");
  }
}
