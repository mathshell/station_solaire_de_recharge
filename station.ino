#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Initialisation de l'écran OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Broches pour le relais et le bouton
const int RELAY_PIN = 7;
const int BUTTON_PIN = A1;

void setup() {
  // Initialisation de l'écran OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Erreur d'initialisation de l'écran OLED"));
    for(;;);
  }

  // Effacer le contenu de l'écran
  display.clearDisplay();
  display.display();

  // Définir le relais comme sortie
  pinMode(RELAY_PIN, OUTPUT);

  // Définir le bouton comme entrée avec une résistance de pull-up interne
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // Lecture de l'état du bouton (inverti car INPUT_PULLUP)
  int buttonState = !digitalRead(BUTTON_PIN);
  digitalWrite(RELAY_PIN, HIGH);  // Activer le relais
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.println("Relais : ON");
  display.display();
  // Si le bouton est enfoncé, activer le relais; sinon, le désactiver
  if (buttonState == HIGH) {
    digitalWrite(RELAY_PIN, HIGH);  // Activer le relais
    display.clearDisplay();
    display.setCursor(10, 10);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.println("Temps restant : 45min");
    display.display();
  
  } else {
    digitalWrite(RELAY_PIN, LOW);   // Désactiver le relais
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.println("Relais : OFF");
    display.display();
  }
  
  delay(100); // Délai pour éviter les rebonds du bouton
}
