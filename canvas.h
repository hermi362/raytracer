#pragma once

#include "color.h"
#include <string>

// Canvas is a 2D array of Color values.
class Canvas {
  private:
    Color* mCanvas;
    int mW, mH;  // width and height of canvas
  public:
    Canvas(int w, int h);
    ~Canvas();

    int width() const {return mW;}
    int height() const {return mH;}

    std::string toString() const;

    // retrieve color value by index
    Color pixelAt(int i) const;

    // retrieve color value by x,y coordinate 
    // (x goes left to right, y goes top to bottom)
    Color pixelAt(int x, int y) const;

    void writePixel(int x, int y, const Color& c);
    
    std::string toPPM();

    // limit input value to range 0.0~1.0
    float clamp(const float v) const {
      if (v > 1.0) return 1.0;
      if (v < 0.0) return 0.0;
      return v;
    }
};




