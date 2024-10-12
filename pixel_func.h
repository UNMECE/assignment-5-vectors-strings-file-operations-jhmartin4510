#include "pixel.h"
#include <string>
#include <vector>

#ifndef _PIXEL_FUNC_H_
#define _PIXEL_FUNC_H_

void average_colors(std::vector<Pixel*>& pixel_list);
void flip_vertically(std::vector<Pixel*>& pixel_list);
void add_pixel(std::string line, Pixel *p, std::vector<Pixel *> &pixel_list);
std::string makedata(int x, int y);
std::string outputdata(std::vector<Pixel*>& pixel_list);
#endif
