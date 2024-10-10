#include <iostream>
#include <vector>
#include <string>
#include "pixel.h"
#include "pixel_func.h"

void average_colors(std::vector<Pixel*>& pixel_list)
{	
	double r =0;
	double g =0;
	double b =0;
	for(int i =0; i<pixel_list.size();i++)
	{
		r += pixel_list[i]->r;
		g += pixel_list[i]->g;
		b += pixel_list[i]->b;
	}
	double avg_r = r/(pixel_list.size());
	double avg_g = g/(pixel_list.size());
	double avg_b = b/(pixel_list.size());
	std::cout<<"Average r is: " <<avg_r <<std::endl;
	std::cout<<"Average g is: " <<avg_g <<std::endl;
	std::cout<<"Average b is: " <<avg_b <<std::endl;	
}

void flip_vertically(std::vector<Pixel*>& pixel_list)
{
	Pixel p;
	int start = 0;
	int half = 0;
	int next = pixel_list[0]->x;
	int max = 0;
	for(int i = 0; i<pixel_list.size(); i++)
	{
		if(pixel_list[i]->x != next)
		{
			max = i-1;
			std::cout<<"Max index for where " <<next <<" is found is " <<max <<std::endl;
			if((i-start) % 2 != 0)
			{
				half = ((max-start)/2)+start;	
			}
			half = ((i-start)/2)+start;
			std::cout<<"half way index is " <<half <<std::endl;
			for(int j = 0;start<half;start++, j++)
			{
				p = *pixel_list[start];
				pixel_list[start]->r = pixel_list[max-j]->r;
				pixel_list[start]->g = pixel_list[max-j]->g;
				pixel_list[start]->b = pixel_list[max-j]->b;
				pixel_list[max-j]->r = p.r;
				pixel_list[max-j]->g = p.g;
				pixel_list[max-j]->b = p.b;
			}
			start = i;
		}
		else if(i==(pixel_list.size()-1))
		{
			std::cout<<"start index is equal to: " <<start <<std::endl;
			max = pixel_list.size();
			std::cout<<"max index is equal to: " <<max <<std::endl;
			if((max-start)%2!=0)
			{
				half = ((max-start-1)/2) +start;	
			}
 			half =((max-start)/2)+start;
			std::cout<<"half is equal to : " <<half <<std::endl;
			for(int j = 1;start<half;start++, j++)
			{
				p = *pixel_list[start];
				pixel_list[start]->r = pixel_list[max-j]->r;
				pixel_list[start]->g = pixel_list[max-j]->g;
				pixel_list[start]->b = pixel_list[max-j]->b;
				pixel_list[max-j]->r = p.r;
				pixel_list[max-j]->g = p.g;
				pixel_list[max-j]->b = p.b;
			}
		}
		next = pixel_list[i]->x;
	}	
}
/*
void add_pixel(std::vector<Pixel> &pixel_list, int x, int y, float r, float g, float b)
{
	Pixel *p = new Pixel;
	p->x = x;
	p->y = y;
	p->r = r;
	p->g = g;
	p->b = b;
	pixel_list.push_back(p);	
	delete p;
}*/
