#ifndef RENDER_H
#define RENDER_H
#include <iostream>
#include "rapidxml_ext.hpp"
#include <string>
#include <unordered_map>
#include <numbers>
#include <cmath>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace rapidxml;
using namespace std;
using namespace numbers;

void render(string file, vector<unordered_map<string, vector<unordered_map<string, double>>>> &points, unordered_map<string, double> bounds);

#endif //RENDER_H
