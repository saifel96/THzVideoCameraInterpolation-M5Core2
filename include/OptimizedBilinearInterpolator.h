#ifndef OPTIMIZED_BILINEAR_INTERPOLATOR_H
#define OPTIMIZED_BILINEAR_INTERPOLATOR_H

#include <cstdint>

class OptimizedBilinearInterpolator {
 public:
  OptimizedBilinearInterpolator();
  ~OptimizedBilinearInterpolator();
  uint8_t* interpolate(uint32_t oldWidth, uint32_t oldHeight,
                       uint8_t* oldPixels, uint32_t newWidth,
                       uint32_t newHeight);

 private:
  void bilinearInterpolate(uint8_t* src, int srcWidth, int srcHeight,
                           uint8_t* dst, int dstWidth, int dstHeight);
};

#endif  // OPTIMIZED_BILINEAR_INTERPOLATOR_H
