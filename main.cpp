#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "pixel.h"
#include "pixel_func.h"
#define SIZE 131072


int main(int argc, char** argv)
{

char *file = argv[1];

std::ofstream MyFile;
MyFile.open(file,std::ios::out);
std::string ss = makedata(512,256);
MyFile<<ss;
MyFile.close();

std::ifstream InputFile;
InputFile.open(file,std::ios::in);
std::vector<Pixel*> pixel_list;
std::string line;
Pixel *p = new Pixel[SIZE];
int ct =0;
while(!InputFile.eof())
{
	std::getline(InputFile, line);
	if(ct<SIZE)
	{
		add_pixel(line, (p+ct), pixel_list);
	}
	ct++;	
}
InputFile.close();

std::cout<<"Size of list is: " <<pixel_list.size() <<std::endl;
average_colors(pixel_list);
flip_vertically(pixel_list);

//Code for creating the flipped.dat file and entering the data for the transformed pixel vector into a string in the csv form
std::ofstream OutFile;
OutFile.open("flipped.dat", std::ios::out);
std::string os = outputdata(pixel_list);
OutFile<<os;
OutFile.close();

delete[] p;
return 0;
}
