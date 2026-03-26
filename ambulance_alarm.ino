#include <LiquidCrystal.h>
#include <TimeLib.h> 

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

  int alarmHours = 11;
  int alarmMinutes = 31;

  boolean alarmActive = false; 
  boolean alarmTriggered = false;

  const int hourButton = 16;
  const int minuteButton = 17;
  //const int buzzerPin = ??;

void setup() {
  pinMode(hourButton, INPUT_PULLUP);
  pinMode(minuteButton, INPUT_PULLUP);
  //pinMode(buzzerPin, OUTPUT);
  lcd.begin(16, 2);
  // Manually setting the time: (Hours, Minutes, Seconds, Day, Month, Year)
  setTime(11, 30, 31, 26, 3, 2026); 
}

void loop() {
  checkButtons();
  displayTime();
  checkAlarm();

  if(!alarmActive){
    displayAlarmSetting();
  }

  delay(50); 
}

// Check's if the buttons are pressed and either adjust's the alarm time or stops the alarm
void checkButtons(){
  boolean hPressed = (digitalRead(hourButton) == LOW);
  boolean mPressed = (digitalRead(minuteButton) == LOW);

  if (hPressed && mPressed && alarmActive){
    stopAlarm();
  }
  else if (!alarmActive && hPressed){
    alarmHours = (alarmHours + 1) % 24;
    delay(200);
  }
  else if (!alarmActive && mPressed){
    alarmMinutes = (alarmMinutes + 1) % 60;
    delay(200);
  }
}

void stopAlarm(){
  alarmActive = false;
  alarmTriggered = true;
  lcd.clear();
}

void displayTime(){
  lcd.setCursor(4, 0);
  printDigits(hour());
  lcd.print(":");
  printDigits(minute());
  lcd.print(":");
  printDigits(second());
}

void displayAlarmSetting(){
  lcd.setCursor(2,1);
  lcd.print("Alarm: ");
  printDigits(alarmHours);
  lcd.print(":");
  printDigits(alarmMinutes);
}
// Adds the leading zeros 
void printDigits(int digits) {
  if (digits < 10)
    lcd.print('0');
  lcd.print(digits);
}

void checkAlarm() {
  if (hour() == alarmHours && minute() == alarmMinutes && !alarmTriggered) {
    if (!alarmActive) {
      lcd.clear();
      alarmActive = true;
    }

    lcd.setCursor(0,1);
    lcd.print("WAKEY WAKEYYYYYY");
    // buzzer, ledit, ajaminen eteenpäin
  }

  if (minute() != alarmMinutes) {
      alarmTriggered = false;
    }
}
