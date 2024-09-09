#include "OptimizedBilinearInterpolator.h"

#include <algorithm>

OptimizedBilinearInterpolator::OptimizedBilinearInterpolator() {}

OptimizedBilinearInterpolator::~OptimizedBilinearInterpolator() {}

void OptimizedBilinearInterpolator::bilinearInterpolate(
    uint8_t* src, int srcWidth, int srcHeight, uint8_t* dst, int dstWidth,
    int dstHeight) {
  float xRatio = float(srcWidth - 1) / dstWidth;
  float yRatio = float(srcHeight - 1) / dstHeight;

  for (int i = 0; i < dstHeight; i++) {
    for (int j = 0; j < dstWidth; j++) {
      float x = j * xRatio;
      float y = i * yRatio;
      int xL = int(x);
      int xH = std::min(xL + 1, srcWidth - 1);
      int yL = int(y);
      int yH = std::min(yL + 1, srcHeight - 1);

      float xWeight = x - xL;
      float yWeight = y - yL;

      int srcIndexLL = (yL * srcWidth + xL) * 3;
      int srcIndexLH = (yL * srcWidth + xH) * 3;
      int srcIndexHL = (yH * srcWidth + xL) * 3;
      int srcIndexHH = (yH * srcWidth + xH) * 3;

      for (int k = 0; k < 3; k++) {
        float top =
            src[srcIndexLL + k] * (1 - xWeight) + src[srcIndexLH + k] * xWeight;
        float bottom =
            src[srcIndexHL + k] * (1 - xWeight) + src[srcIndexHH + k] * xWeight;
        dst[(i * dstWidth + j) * 3 + k] = std::min(
            255, std::max(0, int(top * (1 - yWeight) + bottom * yWeight)));
      }
    }
  }
}

uint8_t* OptimizedBilinearInterpolator::interpolate(uint32_t oldWidth,
                                                    uint32_t oldHeight,
                                                    uint8_t* oldPixels,
                                                    uint32_t newWidth,
                                                    uint32_t newHeight) {
  uint8_t* newPixels = new uint8_t[newWidth * newHeight * 3];
  bilinearInterpolate(oldPixels, oldWidth, oldHeight, newPixels, newWidth,
                      newHeight);
  return newPixels;
}
