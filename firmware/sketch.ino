

#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

const int LED_PIN = 3;
const int BUZZER_PIN = 5;
const int BUTTON_PIN = 2;
const int POT_PIN = A0;

bool running = false;
unsigned long startTime;
int durationMinutes;

void setup() {
    lcd.init();
    lcd.backlight();
    pinMode(LED_PIN, OUTPUT)
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(BUZZER_PIN, OUTPUT);

}


void loop() {
    if (!running) {
        durationMinutes = map(analogRead(POT_PIN), 0, 1023, 5, 60);
        lcd.setCursor(0, 0);
        lcd.print("<3 Vimali's Timer   ");
        lcd.setCursor(0, 1);
        lcd.print("Set: ");
        lcd.print(durationMinutes);
        lcd.print(" mins     ")

        if (digitalRead(BUTTON_PIN) == LOW) {
            startTime = millis();
            running = true;
            lcd.clear();
            delay(500);
        }
    } else {
        if (digitalRead(BUTTON_PIN) == LOW) {
            running = false;
            lcd.clear();
            delay(500);
      
            return;
        }
        
            unsigned long elapsed = (millis() - startTime) / 60000;
            int remaining = durationMinutes - (int)elapsed;

            if(remaining > 0) {
                lcd.setCursor(0, 0);
                lcd.print("Focusing for:   ");
                lcd.setCursor(0, 1);
                lcd.print(remaining);
                lcd.print(" minutes ");

                float val = (exp(sin(millis() / 2000.0 * PI)) - 0.36787944) * 108.0; analogWrite(LED_PIN, (int)val);
            } else {
                running = false;
                lcd.clear();
                lcd.print("Time's up!");
                tone(BUZZER_PIN, 1000, 1000);
                analogWrite (LED_PIN, 255);
                delay(2000);
                lcd.clear();
            }
        }
    }

