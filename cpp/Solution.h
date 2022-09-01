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
      int32_t imageWidth = image.resolution.width;
      int32_t imageHeight = image.resolution.height;
      int pixelsCount = image.pixels.size();

      for (int pixelIndex = 0; pixelIndex < pixelsCount; pixelIndex++) {
          Pixel currentPixel = image.pixels.at(pixelIndex);

          if (currentPixel.red >= 200) {
              std::list<int> matchedPixelsIndexes;

              addBasePatternPixels(image.pixels, pixelIndex, matchedPixelsIndexes, imageWidth);

              for each (EyePattern pattern in EYE_PATTERNS)
              {
                  checkPattern(image.pixels, pixelIndex, matchedPixelsIndexes, imageWidth, imageHeight, pattern);
              }

              for each (int matchedPixelIndex in matchedPixelsIndexes)
              {
                  Pixel& currentPixel = image.pixels.at(matchedPixelIndex);

                  if (currentPixel.red >= 200) {  // The same pixel might have been added multiple times by different patterns
                      currentPixel.red -= 150;
                  }
              }
          }
      }
  }

  void addBasePatternPixels(std::vector<Pixel>& pixels, size_t startingPixelIndex, std::list<int>& matchedPixelsIndexes, int32_t width) {
      for (size_t row = 0; row < 5; row++)
      {
          for (size_t col = 0; col < 5; (row == 0 || row == 4) ? col++ : col += 4)
          {
              int currentPixelIndex = getPixelIndexByOffset(startingPixelIndex, row, col, width);
              Pixel currentPixel = pixels.at(currentPixelIndex);
              matchedPixelsIndexes.push_back(currentPixelIndex);
          }
      }
  }

  void checkPattern(std::vector<Pixel>& pixels, size_t startingPixelIndex, std::list<int>& matchedPixelsIndexes, int32_t width, int32_t height, EyePattern pattern) {
      int currentPatternMatchesCount = 0;

      for (size_t row = 1; row < 4; row++)
      {
          for (size_t col = 1; col < 4; col++)
          {
              const char currentPatternChar = pattern.at(row)[col];
              int currentPixelIndex = getPixelIndexByOffset(startingPixelIndex, row, col, width);
              Pixel currentPixel = pixels.at(currentPixelIndex);

              if (currentPatternChar == ' ') {
                  continue;
              }

              if (currentPixel.red >= 200) {
                  matchedPixelsIndexes.push_back(currentPixelIndex);
                  currentPatternMatchesCount++;
              }
              else {
                  // Remove pixels that match parts of current pattern
                  while (currentPatternMatchesCount--) {
                      matchedPixelsIndexes.pop_back();
                  }

                  return;
              }
          }
      }
  }

  int32_t getPixelIndexByOffset(int32_t startingIndex, int32_t rowOffset, int32_t columnOffset, int32_t imageWidth) {
      return (startingIndex + columnOffset) + (rowOffset * imageWidth);
  }
};

#endif /* SOLUTION_H_ */
