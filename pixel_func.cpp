#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "pixel.h"
#include "pixel_func.h"

void add_pixel(std::string line, Pixel *p, std::vector<Pixel *> &pixel_list)
{
	int prev_find = 0;
	int last_find = line.find(",");
	int ct = 1;
	while(last_find != std::string::npos)
	{
		std::string sub = line.substr(prev_find, last_find-prev_find);
		switch(ct)
		{
			case 1:
				p->x = std::stoi(sub);
				break;
			case 2:
				p->y = std::stoi(sub);
				break;
			case 3:
				p->r = std::stof(sub);
				break;
			case 4:
				p->g = std::stof(sub);
				break;
		}
		prev_find = last_find+1;
		last_find = line.find(",",last_find+1);
		sub = line.substr(prev_find, line.length()+1-prev_find);
		p->b = std::stof(sub);
		ct++;
	}
	pixel_list.push_back(p);	
}

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
	std::cout<<"----------------" <<std::endl;
	std::cout<<"Average r is: " <<avg_r <<std::endl;
	std::cout<<"Average g is: " <<avg_g <<std::endl;
	std::cout<<"Average b is: " <<avg_b <<std::endl;	
	std::cout<<"----------------" <<std::endl;
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
			if((i-start) % 2 != 0)
			{
				half = ((max-start)/2)+start;	
			}
			half = ((i-start)/2)+start;
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
			max = pixel_list.size();
			if((max-start)%2!=0)
			{
				half = ((max-start-1)/2) +start;	
			}
 			half =((max-start)/2)+start;
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

std::string makedata(int x, int y)
{
	Pixel p1;
	std::ostringstream ss;
	
	srand((unsigned) time(NULL));
	for(int i = 0; i<x; i++)
	{
		for(int j = 0; j<y; j++)
		{
			p1.x = i;
			p1.y = j;
			p1.r = (float) rand()/ RAND_MAX;
			p1.g = (float) rand()/RAND_MAX;
			p1.b = (float) rand()/RAND_MAX;
			ss <<p1.x <<"," <<p1.y <<"," <<p1.r <<"," <<p1.g <<"," <<p1.b <<std::endl;
		}
	}
	return ss.str();
}

std::string outputdata(std::vector<Pixel*>& pixel_list)
{
	std::ostringstream os;
	for(int i = 0; i<pixel_list.size();i++)
	{
		os <<pixel_list[i]->x <<"," <<pixel_list[i]->y <<"," <<pixel_list[i]->r <<"," <<pixel_list[i]->g <<"," <<pixel_list[i]->b <<std::endl;
	}
	return os.str();
}
