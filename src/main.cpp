// Diese Header-Dateien sind erforderlich, um die Funktionen und Klassen des
// Codes zu nutzen. Dazu gehören Bibliotheken für das M5Core2-Display,
// Bildverarbeitung und verschiedene Interpolationsmethoden.

#include <M5Core2.h>
#include <image.h>

#include <cstdint>

#include "Bilnear.h"
#include "BiubicInterpolator.hpp"
#include "NearestNeighbor.h"
#include "OptimizedBilinearInterpolator.h"
#include "TemperatureInterpolator.h"
/* Definiert maximale Displaybreite und -höhe sowie die ursprünglichen und neuen
 * Bildabmessungen. Diese Werte werden für die Interpolation und Anzeige
 * verwendet.*/

#define MAX_DISP_WIDTH 240
#define MAX_DISP_HEIGHT 135

const int origWidth = 32;
const int origHeight = 24;

const int displayWidth = 240;
const int displayHeight = 135;

TFT_eSprite img = TFT_eSprite(&M5.Lcd);

// NearestNeighbor interpolator;
BiubicInterpolator interpolator;
// Bilnear interpolator;
// TemperatureInterpolator interpolator;  // die Isolierte Interpolation  von
// T-lite Code Source

void rgb888_to_rgb565_row(uint8_t *rgb888Row, uint16_t *rgb565Row, int width);

int rotationSetting = 1;  // Set rotation: 0 (0°), 1 (90°), 2 (180°), 3 (270°)

// Die setup-Funktion initialisiert die serielle Kommunikation, das M5-LCD und
// das Sprite. Der Bildschirm wird mit schwarzer Farbe gefüllt, die Farbentiefe
// auf 16 Bit gesetzt und die Rotation angewendet.
void setup() {
  Serial.begin(115200);
  M5.begin();
  M5.Lcd.fillScreen(TFT_BLACK);
  img.setColorDepth(16);
  M5.Lcd.setRotation(rotationSetting);  // Apply the desired rotation
  img.createSprite(displayWidth, displayHeight);
}

uint_fast64_t startTime;
uint_fast64_t endTime;

void loop() {
  startTime = millis();  // Hier wird die aktuelle Zeit in Millisekunden
                         // gespeichert, um die Leistung zu messen.

  img.fillSprite(TFT_BLACK);

  // Ruft die interpolate-Methode des TemperatureInterpolator-Objekts auf, um
  // das ursprüngliche Bild (imagePixels) auf die neuen Abmessungen zu
  // interpolieren. Das Ergebnis wird in newpixels gespeichert.

  uint8_t *newpixels = interpolator.interpolate(
      origWidth, origHeight, imagePixels, displayWidth, displayHeight);

  //Überprüft, ob die Interpolation erfolgreich war. Wenn nicht, wird eine
  // Fehlermeldung auf dem Sprite angezeigt, und die Funktion wird beendet.
  if (newpixels == nullptr) {
    img.printf("Interpolation failed!");
    return;
  }

  // Buffer for a single row conversion from RGB888 to RGB565
  uint16_t *rowPixels565 = new uint16_t[displayWidth];

  //Überprüft die erfolgreiche Speicherzuweisung für rowPixels565. Wenn die
  // Zuweisung fehlschlägt, wird eine Fehlermeldung angezeigt, und der zuvor
  // allokierte Speicher für newpixels wird freigegeben, um einen Speicherleck
  // zu vermeiden.
  if (rowPixels565 == nullptr) {
    img.printf("Memory allocation for rowPixels565 failed!");
    delete[] newpixels;  // Clean up to avoid memory leak
    return;
  }

  // Convert and push each row separately
  // Diese Schleife konvertiert jede Zeile des neuen Bildes (newpixels) von
  // RGB888 in RGB565 und zeigt sie auf dem Sprite an. Die Zeilen werden von
  // unten nach oben angezeigt, um die Koordinaten des M5-Displays zu
  // berücksichtigen.
  for (int y = 0; y < displayHeight; y++) {
    rgb888_to_rgb565_row(newpixels + y * displayWidth * 3, rowPixels565,
                         displayWidth);
    img.pushImage(0, displayHeight - y - 1, displayWidth, 1, rowPixels565);
  }

  endTime = millis();
  img.setCursor(10, 10);
  img.setTextColor(TFT_RED);
  img.printf("FPS: %f", 1000.0 / (endTime - startTime));
  int cpuFreq = getCpuFrequencyMhz();    // Get the CPU frequency in MHz
  img.setCursor(displayWidth - 80, 10);  // Top right position
  img.setTextColor(TFT_BLUE);
  img.printf("CPU: %d MHz", cpuFreq);
  img.pushSprite(0, 0);

  delete[] newpixels;
  delete[] rowPixels565;
}

// Optimized function for row-by-row RGB888 to RGB565 conversion
void rgb888_to_rgb565_row(uint8_t *rgb888Row, uint16_t *rgb565Row, int width) {
  for (int i = 0; i < width; i++) {
    int index = i * 3;  // Index for RGB888

    // Get RGB components
    uint8_t b = rgb888Row[index];
    uint8_t g = rgb888Row[index + 1];
    uint8_t r = rgb888Row[index + 2];

    // Convert to RGB565
    rgb565Row[i] = img.color565(r, g, b);
  }
}
