#include <Arduino.h>

// Pins anpassen!
#define PIN_CLK  20
#define PIN_DT   21
#define PIN_SW   10   // optional, falls dein Encoder einen Button hat

int lastStateCLK;
int counter = 0;

// Button-Entprellung
bool buttonState = HIGH;        // aktueller Zustand
bool lastButtonState = HIGH;    // vorheriger Zustand
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 30; // 30 ms Entprellzeit

void setup() {
  Serial.begin(115200);

  pinMode(PIN_CLK, INPUT_PULLUP);
  pinMode(PIN_DT, INPUT_PULLUP);
  pinMode(PIN_SW, INPUT_PULLUP);

  lastStateCLK = digitalRead(PIN_CLK);

  Serial.println("Rotary Encoder Test gestartet");
}

void loop() {
  int currentStateCLK = digitalRead(PIN_CLK);

  // Drehrichtung erkennen
  if (currentStateCLK != lastStateCLK) {
    if (digitalRead(PIN_DT) != currentStateCLK) {
      counter++;
      Serial.println("Drehrichtung: Rechts  |  Counter: " + String(counter));
    } else {
      counter--;
      Serial.println("Drehrichtung: Links   |  Counter: " + String(counter));
    }
  }

  lastStateCLK = currentStateCLK;


  // -----------------------------
  // BUTTON MIT FLANKENERKENNUNG
  // -----------------------------
  int reading = digitalRead(PIN_SW);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();  // Entprell-Timer starten
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Wenn der Zustand stabil ist:
    if (reading != buttonState) {
      buttonState = reading;

      // Nur beim Übergang HIGH → LOW auslösen
      if (buttonState == LOW) {
        Serial.println("Button gedrückt");
      }
    }
  }

  lastButtonState = reading;
}
