#include <vector>
#include "pixel.h"

#ifndef _PIXEL_FUNC_H_
#define _PIXEL_FUNC_H_

void average_colors(std::vector<Pixel*>& pixel_list);
void flip_vertically(std::vector<Pixel*>& pixel_list);
void add_pixel(std::vector<Pixel> &pixel_list, int x, int y, float r, float g, float b);
#endif
