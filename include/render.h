#ifndef RENDER_H
#define RENDER_H
#include <iostream>
#include "rapidxml_ext.hpp"
#include <string>
#include <unordered_map>
#include <numbers>
#include <cmath>
#define cimg_display 0
// #include "/usr/include/ImageMagick-6/Magick++.h"
// #include <Magick++.h>
// #define cimg_use_jpeg
// #define cimg_use_magick
#include "CImg.h"

// using namespace Magick;
using namespace rapidxml;
using namespace std;
using namespace numbers;
using namespace cimg_library;

void render(string file, vector<unordered_map<string, vector<unordered_map<string, double>>>> &points, unordered_map<string, double> bounds);

#endif //RENDER_H
