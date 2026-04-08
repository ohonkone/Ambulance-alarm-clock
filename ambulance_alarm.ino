#include <LiquidCrystal.h>
#include <TimeLib.h> 

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

  unsigned long millisNow = millis();
  unsigned long lastBuzzer = 0;
  unsigned long lastBlink = 0;

  int interval = 0;
  int lap = 0;
  int alarmHours = 11;
  int alarmMinutes = 31;

  boolean alarmActive = false; 
  boolean alarmTriggered = false;

  const int blinkingRate = 450;
  // The pins for the buttons, buzzer, leds and motor
  const int hourButton = 16;
  const int minuteButton = 17;
  const int buzzerPin = 18;
  const int led1 = 20;
  const int led2 = 21;
  const int motorPin = 0;

void setup() {

  Serial.begin(9600);
  pinMode(hourButton, INPUT_PULLUP);
  pinMode(minuteButton, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(motorPin, OUTPUT);
  lcd.begin(16, 2);
  // Manually setting the time: (Hours, Minutes, Seconds, Day, Month, Year)
  setTime(11, 30, 50, 26, 3, 2026); 
}

void loop() {
  millisNow = millis();
  checkButtons();
  displayTime();
  checkAlarm();

  if(!alarmActive){
    displayAlarmSetting();
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(motorPin, LOW);
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

  // Stops the alarm, clear's the screen 
void stopAlarm(){
  alarmActive = false;
  alarmTriggered = true;
  lcd.clear();
  delay(200);
}

  // Displays time on the lcd screen uses printDigits function to add the leading zeros to the numbers
void displayTime(){
  lcd.setCursor(4, 0);
  printDigits(hour());
  lcd.print(":");
  printDigits(minute());
  lcd.print(":");
  printDigits(second());
}

  // Displays the alarm time on the bottom of the lcd screen
void displayAlarmSetting(){
  lcd.setCursor(2,1);
  lcd.print("Alarm: ");
  printDigits(alarmHours);
  lcd.print(":");
  printDigits(alarmMinutes);
}
// Adds the leading zeros (6 -> 06)
void printDigits(int digits) {
  if (digits < 10)
    lcd.print('0');
  lcd.print(digits);
}

  /* 
  Checks if the current time matches the alarmtime and if it does changes the alarmActive to true 
  and turns on the leds, buzzer and motor. When the alarm is active manages the motor and the 
  pulsing patterns for the LEDs and the buzzer. Resets the alarmTriggered when minute has passed.
  */

void checkAlarm() {
  if ((hour() == alarmHours && minute() == alarmMinutes && !alarmTriggered) || alarmActive) {
    if (!alarmActive) {
      lcd.clear();
      alarmActive = true;
      lap = 0;
    }

    lcd.setCursor(0,1);
    lcd.print("WAKEY WAKEYYYYYY");
    digitalWrite(motorPin, HIGH);
    
    if (millisNow - lastBuzzer >= interval) {

          lastBuzzer = millisNow;
          lap++;

          if (lap <= 8) {
            interval = 300; 
            digitalWrite(buzzerPin, !digitalRead(buzzerPin)); 
          } 
          else {
            interval = 1200; 
            digitalWrite(buzzerPin, LOW); 
            lap = 0; 
          }
        }
    
    if (millisNow - lastBlink >= blinkingRate){
      lastBlink = millisNow;
      digitalWrite(led2, digitalRead(led1));
      digitalWrite(led1, !digitalRead(led1));
    }
  }

  if (minute() != alarmMinutes) {
      alarmTriggered = false;
    }
}



