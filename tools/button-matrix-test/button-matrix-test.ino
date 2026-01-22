#include <Arduino.h>

int rowPins[4] = {16, 15, 14, 13};
int colPins[4] = {23, 19, 18, 17};

char keymap[4][4][4] = {
  { "S01", "S02", "S03", "S04" },
  { "S05", "S06", "S07", "S08" },
  { "S09", "S10", "S11", "S12" },
  { "S13", "S14", "S15", "S16" }
};

unsigned long lastPress = 0;
const unsigned long debounceTime = 80;

void setup() {
  Serial.begin(115200);
  Serial.println("4x4 Keypad Test gestartet");

  for (int r = 0; r < 4; r++) {
    pinMode(rowPins[r], OUTPUT);
    digitalWrite(rowPins[r], HIGH);
  }

  for (int c = 0; c < 4; c++) {
    pinMode(colPins[c], INPUT_PULLUP);
  }
}

void loop() {
  for (int r = 0; r < 4; r++) {
    digitalWrite(rowPins[r], LOW);

    for (int c = 0; c < 4; c++) {
      if (digitalRead(colPins[c]) == LOW) {
        if (millis() - lastPress > debounceTime) {
          Serial.print("Taste gedrückt: ");
          Serial.print(keymap[r][c]);
          Serial.print("   (Row ");
          Serial.print(r);
          Serial.print(", Col ");
          Serial.print(c);
          Serial.println(")");
          lastPress = millis();
        }
      }
    }

    digitalWrite(rowPins[r], HIGH);
  }
}
