#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "pixel.h"
#include "pixel_func.h"
/*This function adds a pixel* to the pixel_list vector from the line string given*/
void add_pixel(std::string line, Pixel *p, std::vector<Pixel *> &pixel_list)
{
	int prev_find = 0;
	int last_find = line.find(",");
	int ct = 1;
	while(last_find != std::string::npos)			//loop for each "," index
	{
		std::string sub = line.substr(prev_find, last_find-prev_find);	//create a substring using indices before and after a comma
		switch(ct)		//using switch case to convert substring to correct data type. initialzing obtain pointed by p to the converted value of the substring
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
		ct++;			//ct increments to do the proper conversion knowing the order of the data being reading by the file
	}
	pixel_list.push_back(p);	//insert p* in pixel_list vector	
}
/*This function takes in the address of Pixel* vector and traverses the vector to add each value of a particular color. This total color value is then averaged by the size of the pixel_list*/
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
/*This function takes in the address of Pixel* vector and flips the pixel data between the first and last y coordinate for a given x coordinate. This does so by finding the index for when x changes value and uses a loops to flip the last and first pixel data for a given x coordinate.*/
void flip_vertically(std::vector<Pixel*>& pixel_list)
{
	Pixel p;
	int start = 0;
	int half = 0;
	int next = pixel_list[0]->x;		//initializing value to starting x value
	int max = 0;
	for(int i = 0; i<pixel_list.size(); i++)	//loop through entire vector list
	{
		if(pixel_list[i]->x != next)	//find when x value changes
		{
			max = i-1;		//i-1 is the previous index from the changed x
			if((i-start) % 2 != 0)	//find halfway point and considering even and odd number of switches
			{
				half = ((max-start)/2)+start;	
			}
			half = ((i-start)/2)+start;
			for(int j = 0;start<half;start++, j++)		//looping from start index to the halway point and flipping the first and last pixel objects for a given x incrementally
			{
				p = *pixel_list[start];
				pixel_list[start]->r = pixel_list[max-j]->r;
				pixel_list[start]->g = pixel_list[max-j]->g;
				pixel_list[start]->b = pixel_list[max-j]->b;
				pixel_list[max-j]->r = p.r;
				pixel_list[max-j]->g = p.g;
				pixel_list[max-j]->b = p.b;
			}
			start = i;		//initialize start to i, where the change was observed
		}
		else if(i==(pixel_list.size()-1))	//considering the list of the last x value
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
		next = pixel_list[i]->x;		//initializing next to the value of x from the ith object in the pixel_list each time the loop runs
	}	
}
/*This function makes "random" pixel data for the given xy dimensions.This pixel data is converted into a long string and returns the string*/
std::string makedata(int x, int y)
{
	Pixel p1;			//declaring a pixel object
	std::ostringstream ss;		//using ostringstream object to appended pixel data
	
	srand((unsigned) time(NULL));	//setting random number generator
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
	return ss.str();		//return a string object from the appended stringstream object
}
/*This function references the pixel_list vector obejects and converts each object of the vector into a long appended string*/
std::string outputdata(std::vector<Pixel*>& pixel_list)
{
	std::ostringstream os;
	for(int i = 0; i<pixel_list.size();i++)
	{
		os <<pixel_list[i]->x <<"," <<pixel_list[i]->y <<"," <<pixel_list[i]->r <<"," <<pixel_list[i]->g <<"," <<pixel_list[i]->b <<std::endl;
	}
	return os.str();
}
