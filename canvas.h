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

    int width() {return mW;}
    int height() {return mH;}

    std::string toString();

    // retrieve color value by index
    Color pixelAt(int i);

    // retrieve color value by x,y coordinate 
    // (x goes left to right, y goes top to bottom)
    Color pixelAt(int x, int y);

    void writePixel(int x, int y, const Color& c);
    
    float clamp(const float v);
    std::string toPPM();

};


