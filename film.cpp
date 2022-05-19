#include "film.h"
#include <cassert>

Film::Film(int w, int h) {
  mW = w;
  mH = h;
  mFilm = new Color[w*h];

  // initialize every pixel to 0,0,0
  for (int i=0; i<w*h; ++i) {
    mFilm[i].setColor(0,0,0);
  }
}

Film::~Film() {
    delete[] mFilm;
}

std::string Film::toString() const {
    const auto N = 50;
    char buffer[N];
    snprintf(buffer, N, "Film[%d,%d] (%d bytes)\n", 
      mW, mH, int(sizeof(Color) * mW * mH ));
    return buffer;
}

Color Film::pixelAt(int i) const {
  assert(i < mW*mH);
  return mFilm[i];
}
Color Film::pixelAt(int x, int y) const {
  assert(x < mW  &&  y < mH);
  return mFilm[y*mW + x];
}
void Film::writePixel(int x, int y, const Color& c) {
  assert(x < mW  &&  y < mH);
  mFilm[y*mW + x] = c;
}


std::string Film::toPPM() {
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