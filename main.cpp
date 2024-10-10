#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cstdlib>
#include <time.h>
#include "pixel.h"
#include "pixel_func.h"
#define SIZE 15


int main(int argc, char** argv)
{

char *file = argv[1];

std::ifstream MyFile;
MyFile.open(file,std::ios::in);
if(!MyFile.is_open())
{
	std::cout<<"File did not open successfully" <<std::endl;
}
else
{
	std::cout<< "File opened succesfully" <<std::endl;
}

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
	std::cout<<"Line x" <<std::endl;
	std::cout<<line <<std::endl;	
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

for(int i = 0; i<SIZE;i++)
{
std::cout<<pixel_list[i]->x <<"\t" <<pixel_list[i]->y <<"\t" <<pixel_list[i]->r <<"\t" <<pixel_list[i]->g <<"\t" <<pixel_list[i]->b <<std::endl;
}

std::cout<<"Size of list is: " <<pixel_list.size() <<std::endl;
average_colors(pixel_list);
flip_vertically(pixel_list);
for(int i=0; i<SIZE; i++)
{
std::cout<<pixel_list[i]->x <<"\t" <<pixel_list[i]->y <<"\t" <<pixel_list[i]->r <<"\t" <<pixel_list[i]->g <<"\t" <<pixel_list[i]->b <<std::endl;
}

/*
Pixel p1;

std::ostringstream ss;

srand((unsigned) time(NULL));
for(int i = 0; i<3; i++)
{
	for(int j = 0; j<5; j++)
	{
		p1.x = i;
		p1.y = j;
		p1.r = (float) rand() / RAND_MAX;
		p1.g = (float) rand() /RAND_MAX;
		p1.b = (float) rand() /RAND_MAX;
//		std::cout<<p1.x <<"," <<p1.y <<"," <<p1.r <<"," <<p1.g <<"," <<p1.b  <<std::endl;
		ss <<p1.x <<"," <<p1.y <<"," <<p1.r <<"," <<p1.g <<"," <<p1.b <<std::endl; 
	}	
}
MyFile<<ss.str();
*/

std::ofstream OutFile;
OutFile.open("flipped.dat", std::ios::out);
std::ostringstream os;
for(int i = 0 ; i<SIZE; i++)
{
	os <<pixel_list[i]->x <<"," <<pixel_list[i]->y <<"," <<pixel_list[i]->r <<"," <<pixel_list[i]->g <<"," <<pixel_list[i]->b <<std::endl;
}
OutFile<<os.str();


delete[] p;
return 0;
}
