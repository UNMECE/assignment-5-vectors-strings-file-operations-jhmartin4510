#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "pixel.h"
#include "pixel_func.h"
#define SIZE 131072


int main(int argc, char** argv)
{

char *file = argv[1];

std::ifstream MyFile;
MyFile.open(file,std::ios::in);
/*
if(!MyFile.is_open())
{
	std::cout<<"File did not open successfully" <<std::endl;
}
else
{
	std::cout<< "File opened succesfully" <<std::endl;
}
*/

std::vector<Pixel*> pixel_list;
std::string line;
Pixel *p = new Pixel[SIZE];
int prev_find;
int last_find;
int ct;
int ct_p=0;
while(!MyFile.eof())
{
	std::getline(MyFile, line);
//	std::cout<<"Line x" <<std::endl;
//	std::cout<<line <<std::endl;	
	prev_find = 0;
	last_find = line.find(",");
	ct = 1;
	while(last_find != std::string::npos)
	{
		
		std::string sub = line.substr(prev_find, last_find-prev_find);
		switch(ct)
		{
			case 1:
				(p+ct_p)->x = std::stoi(sub);
				break;
			case 2:
				(p+ct_p)->y = std::stoi(sub);
				break;
			case 3:
				(p+ct_p)->r = std::stof(sub);
				break;
			case 4:
				(p+ct_p)->g = std::stof(sub);
				break;
		}
		prev_find = last_find+1;
		last_find = line.find(",", last_find+1);
		ct++;  
		sub = line.substr(prev_find, line.length()+1-prev_find);
		(p+ct_p)->b = std::stof(sub);
	}
	if(ct_p<SIZE)
	{
	pixel_list.push_back(p+ct_p);
	}
	ct_p++;	
}
MyFile.close();
/*
for(int i = 0; i<SIZE;i++)
{
std::cout<<pixel_list[i]->x <<"\t" <<pixel_list[i]->y <<"\t" <<pixel_list[i]->r <<"\t" <<pixel_list[i]->g <<"\t" <<pixel_list[i]->b <<std::endl;
}
*/
std::cout<<"Size of list is: " <<pixel_list.size() <<std::endl;
average_colors(pixel_list);
flip_vertically(pixel_list);
/*
for(int i=0; i<SIZE; i++)
{
std::cout<<pixel_list[i]->x <<"\t" <<pixel_list[i]->y <<"\t" <<pixel_list[i]->r <<"\t" <<pixel_list[i]->g <<"\t" <<pixel_list[i]->b <<std::endl;
}
*/
//Function to make data that will be used for input into the pixel* vector
/*
std::string ss = makedata(512, 256);
MyFile <<ss;
MyFile.close();
*/
//Code for creating the flipped.dat file and entering the data for the transformed pixel vector into a string in the csv form
std::ofstream OutFile;
OutFile.open("flipped.dat", std::ios::out);
std::string os = outputdata(pixel_list);
OutFile<<os;
OutFile.close();

delete[] p;
return 0;
}
