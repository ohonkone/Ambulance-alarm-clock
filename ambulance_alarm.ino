#include <Wire.h>
#include "DFRobot_RGBLCD1602.h"
#include <TimeLib.h> 

  DFRobot_RGBLCD1602 lcd(0x60, 16, 2);


  unsigned long millisNow = millis();
  unsigned long lastBuzzer = 0;
  unsigned long lastBlink = 0;
  unsigned long pressStartTime = 0;
  unsigned long lastScroll = 0;

  int scrollPos = 0;
  int interval = 0;
  int lap = 0;
  int alarmHours = 8;
  int alarmMinutes = 30;

  bool hourModeDone = false;
  bool alarmOff = true;
  bool buttonsWereDown = false;
  bool is12HourMode = false;
  bool alarmActive = false; 
  bool alarmTriggered = false;

  const int blinkingRate = 450;
  // The pins for the buttons, buzzer, leds and motor
  const int hourButton = 17;
  const int minuteButton = 16;
  const int buzzerPin = 21;
  const int led1 = 19;
  const int led2 = 20;
  const int motorPin = 0;
  
  String text = "                 WAKEY WAKEYYYYY!!  I'M OUTTA HERE!  CATCH ME IF U CAN!!                           U STILL IN THE BED???  GET UUUUPP!!!                   ";
  byte clockChar[8] = {
    0b00000,
    0b00100,
    0b01110, 
    0b01110, 
    0b01110, 
    0b11111,
    0b00100,
    0b00000
  };

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(hourButton, INPUT_PULLUP);
  pinMode(minuteButton, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(motorPin, OUTPUT);
  lcd.init();
  lcd.setRGB(255, 255, 255);

  // Creates the bell icon
  lcd.customSymbol(0, clockChar);
  // Manually setting the time: (Hours, Minutes, Seconds, Day, Month, Year)
  setTime(8, 29, 50, 26, 3, 2026); 
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
    lcd.setRGB(255, 255, 255);
  }

  delay(50); 
}

// Check's if the buttons are pressed and either adjust's the alarm time or stops the alarm
void checkButtons(){
  boolean hPressed = (digitalRead(hourButton) == LOW);
  boolean mPressed = (digitalRead(minuteButton) == LOW);

  if (hPressed && mPressed){
    if (alarmActive){
      stopAlarm();
    }
    else {
      if (!buttonsWereDown){
        pressStartTime = millisNow;
        buttonsWereDown = true;
        hourModeDone = false;
        alarmOff = !alarmOff;
      }

      if (millisNow - pressStartTime > 5000 && !hourModeDone) {
        is12HourMode = !is12HourMode;
        hourModeDone = true;
        lcd.clear();
      } 
    }    
  }
  else if (!alarmActive && hPressed){
    alarmHours = (alarmHours + 1) % 24;
    delay(200);
  }
  else if (!alarmActive && mPressed){
    alarmMinutes = (alarmMinutes + 1) % 60;
    delay(200);
  }
  if (!hPressed && !mPressed){
    buttonsWereDown = false;
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
  if (!is12HourMode){
    printDigits(hour());
    lcd.print(":");
    printDigits(minute());
    lcd.print(":");
    printDigits(second());
    lcd.print("     ");
  }
  else if (is12HourMode){
    lcd.setCursor(3, 0);
    int h = hourFormat12();
    printDigits(h);
    lcd.print(":");
    printDigits(minute());
    lcd.print(":");
    printDigits(second());
    lcd.print(" ");
    if (isAM()) lcd.print("AM");
    else lcd.print("PM");
  }
}

  // Displays the alarm time on the bottom of the lcd screen
void displayAlarmSetting(){

  if (!is12HourMode){
    lcd.setCursor(1,1);
    lcd.print("Alarm: ");
    printDigits(alarmHours);
    lcd.print(":");
    printDigits(alarmMinutes);
    lcd.print(" ");
    if (!alarmOff){
      lcd.write((uint8_t)0);
    }
    else lcd.print("  ");
  }
  if (is12HourMode){
    lcd.setCursor(0,1);
    lcd.print("Alarm ");

    int h1 = alarmHours;
    if (h1==0) h1 = 12;
    else if (h1>12) h1 -=12;

    printDigits(h1);
    lcd.print(":");
    printDigits(alarmMinutes);
    lcd.print(" ");
    if (alarmHours < 12) lcd.print("AM");
    else lcd.print("PM");
    if (!alarmOff){
      lcd.print(" ");
      lcd.write((uint8_t)0);
    }
    else {
      lcd.setCursor(15,1);
      lcd.print("  ");
    }

  }
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
  if (!alarmOff){
    if ((hour() == alarmHours && minute() == alarmMinutes && !alarmTriggered) || alarmActive) {
      if (!alarmActive) {
        lcd.clear();
        alarmActive = true;
        lap = 0;
        scrollPos = 0;
      }

      if (millisNow - lastScroll > 250){
        lcd.setCursor(0,1);
        String visible = text.substring(scrollPos, scrollPos+16);
        lcd.print(visible);
        scrollPos++;

        if (scrollPos > text.length()-16){
          scrollPos = 0;
        }
        lastScroll = millisNow;
      }

      digitalWrite(motorPin, HIGH);
      
      if (millisNow - lastBuzzer >= interval) {

            lastBuzzer = millisNow;
            lap++;

            if (lap <= 8) {
              interval = 20; 
              digitalWrite(buzzerPin, !digitalRead(buzzerPin)); 
            } 
            else {
              interval = 400; 
              digitalWrite(buzzerPin, LOW); 
              lap = 0; 
            }
          }
      
      if (millisNow - lastBlink >= blinkingRate){
        lastBlink = millisNow;
        digitalWrite(led2, digitalRead(led1));
        digitalWrite(led1, !digitalRead(led1));
        if (digitalRead(led1)){
          lcd.setRGB(0, 0, 255);
        }
        else {
          lcd.setRGB(255, 0, 0);
        }
      }
    }

    if (minute() != alarmMinutes) {
        alarmTriggered = false;
      }
  }
}
