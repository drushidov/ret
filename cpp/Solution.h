#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <cstdint>
#include <list>

#include "utils/Image.h"
#include "utils/FunctionTracer.h"
#include "utils/EyePatterns.h"

class Solution {
public:
  void compute([[maybe_unused]]std::vector<PackedImage> &images) {
    FunctionTracer<std::chrono::milliseconds> tracer("compute", "ms");

    for (int i = 0; i < images.size(); i++) {
        PackedImage& image = images.at(i);
        computeImage(image);
    }
  }

  void compute([[maybe_unused]]std::vector<StrideImage> &images) {
    FunctionTracer<std::chrono::milliseconds> tracer("compute", "ms");
    //TODO: fill solution
  }

  void computeImage(PackedImage& image) {
      int32_t width = image.resolution.width;
      int32_t height = image.resolution.height;
      int pixelsCount = image.pixels.size();

      for (int i = 0; i < pixelsCount; i++) {
          Pixel currentPixel = image.pixels.at(i);

          if (currentPixel.red >= 200) {
              std::list<int> matchedPixelsIndexes;

              for each (EyePattern pattern in EYE_PATTERNS)
              {
                  checkPattern(image.pixels, i, matchedPixelsIndexes, width, height, pattern);
              }

              for each (int matchedPixelIndex in matchedPixelsIndexes)
              {
                  if (image.pixels.at(matchedPixelIndex).red >= 200) {  // The same pixel might have been added multiple times by different patterns
                      image.pixels.at(matchedPixelIndex).red -= 150;
                  }
              }
          }
      }
  }

  void checkPattern(std::vector<Pixel>& pixels, size_t startingPixelIndex, std::list<int>& matchedPixelsIndexes, int32_t width, int32_t height, EyePattern pattern) {
      if (width - (startingPixelIndex % width) < 5) {
          // Not enough horizontal space for pattern.
          return;
      }

      int currentPatternMatchesCount = 0;

      for (size_t i = 0; i < 5; i++)
      {
          for (size_t j = 0; j < 5; j++)
          {
              const char currentPatternChar = pattern.at(i)[j];
              int currentPixelIndex = (startingPixelIndex + j) + (i * width);
              Pixel currentPixel = pixels.at(currentPixelIndex);

              if (currentPatternChar == ' ') {
                  continue;
              }

              if (currentPixel.red >= 200) {
                  matchedPixelsIndexes.push_back(currentPixelIndex);
                  currentPatternMatchesCount++;
              }
              else {
                  // Remove pixels that match parts of current pattern.
                  while (currentPatternMatchesCount--) {
                      matchedPixelsIndexes.pop_back();
                  }

                  return;
              }
          }
      }
  }
};

#endif /* SOLUTION_H_ */
