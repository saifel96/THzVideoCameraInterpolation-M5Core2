#include "NearestNeighbor.h"

NearestNeighbor::NearestNeighbor() {}

NearestNeighbor::~NearestNeighbor() {}

// Diese Methode führt die Interpolation eines Bildes mit der
// Nächster-Nachbar-Methode durch. Sie nimmt das Quellbild (src) und erzeugt
// eine vergrößerte oder verkleinerte Version (dst) basierend auf den neuen
// Abmessungen (dstWidth, dstHeight).
//
void NearestNeighbor::nearestNeighborInterpolate(uint8_t* src, int srcWidth,
                                                 int srcHeight, uint8_t* dst,
                                                 int dstWidth, int dstHeight) {
  // Diese Variablen berechnen die Skalierungsverhältnisse für die Breite
  // (xRatio) und Höhe (yRatio) zwischen dem Quell- und Zielbild.
  float xRatio = float(srcWidth) / dstWidth;
  float yRatio = float(srcHeight) / dstHeight;
  int nearestX, nearestY;

  // Diese Schleifen durchlaufen die Pixel des Zielbildes. Für jedes Pixel im
  // Zielbild wird das entsprechende Quellbildpixel (durch die
  // Nächster-Nachbar-Methode) ermittelt, indem die nächstgelegenen x- und
  // y-Koordinaten (nearestX, nearestY) im Quellbild berechnet werden.

  for (int i = 0; i < dstHeight; i++) {
    nearestY = int(i * yRatio);
    for (int j = 0; j < dstWidth; j++) {
      nearestX = int(j * xRatio);

      // Diese Abschnitte kopieren die RGB-Werte des nächstgelegenen Pixels im
      // Quellbild (src) in das Zielbild (dst). Der Index srcIndex wird für das
      // Quellbild und dstIndex für das Zielbild berechnet, und die
      // entsprechenden Farbwerte werden kopiert.
      int srcIndex = (nearestY * srcWidth + nearestX) * 3;
      int dstIndex = (i * dstWidth + j) * 3;
      dst[dstIndex] = src[srcIndex];
      dst[dstIndex + 1] = src[srcIndex + 1];
      dst[dstIndex + 2] = src[srcIndex + 2];
    }
  }
}
// Diese Methode dient als Schnittstelle zur Durchführung der
// Nächster-Nachbar-Interpolation. Sie erstellt ein neues Bild mit den
// angegebenen Abmessungen und verwendet die nearestNeighborInterpolate-Methode,
// um die Interpolation durchzuführen.

uint8_t* NearestNeighbor::interpolate(uint32_t oldWidth, uint32_t oldHeight,
                                      uint8_t* oldPixels, uint32_t newWidth,
                                      uint32_t newHeight) {
  // Allokiert Speicher für das neue Bild mit den spezifizierten Abmessungen
  // (newWidth x newHeight). Jedes Pixel besteht aus 3 Farbwerten (RGB).
  uint8_t* newPixels = new uint8_t[newWidth * newHeight * 3];
  // Führt die eigentliche Interpolation durch, indem die Methode
  // nearestNeighborInterpolate aufgerufen wird. Das neue Bild (newPixels) wird
  // basierend auf den Daten des ursprünglichen Bildes (oldPixels) erstellt.
  nearestNeighborInterpolate(oldPixels, oldWidth, oldHeight, newPixels,
                             newWidth, newHeight);
  return newPixels;
}
