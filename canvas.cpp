#include "canvas.h"
#include <cassert>

Canvas::Canvas(int w, int h) {
  mW = w;
  mH = h;
  mCanvas = new Color[w*h];

  // initialize every pixel to 0,0,0
  for (int i=0; i<w*h; ++i) {
    mCanvas[i].setColor(0,0,0);
  }
}

Canvas::~Canvas() {
    delete[] mCanvas;
}

std::string Canvas::toString() {
    const auto N = 50;
    char buffer[N];
    snprintf(buffer, N, "Canvas[%d,%d] (%d bytes)\n", 
      mW, mH, int(sizeof(Color) * mW * mH ));
    return buffer;
}

Color Canvas::pixelAt(int i) {
  assert(i < mW*mH);
  return mCanvas[i];
}
Color Canvas::pixelAt(int x, int y) {
  assert(x < mW  &&  y < mH);
  return mCanvas[y*mW + x];
}
void Canvas::writePixel(int x, int y, const Color& c) {
  assert(x < mW  &&  y < mH);
  mCanvas[y*mW + x] = c;
}

// limit input value to range 0.0~1.0
float Canvas::clamp(const float v) {
  if (v > 1.0) return 1.0;
  if (v < 0.0) return 0.0;
  return v;
}

std::string Canvas::toPPM() {
  std::string buffer;

  // header start
  buffer += "P3\n";
  buffer += std::to_string(mW) + ' ' + std::to_string(mH) + '\n';
  buffer += "255\n";
  // header end
  
  for (int i=0 ; i<mW*mH ; ++i) {
    // printf("i=%d\n", i);   // DEBUG
    const Color c = pixelAt(i);
    const int r = clamp(c.r) * 255;  // clamp color value v to range 0-255
    const int g = clamp(c.g) * 255;
    const int b = clamp(c.b) * 255;
    buffer += std::to_string(r) + ' ' + std::to_string(g) + ' ' + std::to_string(b) + ' ';

    // add a newline char every 5 colors, to keep line length below 70.
    if ((i+1) % 5 == 0) {
      buffer += '\n'; 
    }
  }

  return buffer + '\n';
}