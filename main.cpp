#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "pixel.h"
#include "pixel_func.h"
#define SIZE 131072

/*If using UNM linux enviroment, compile using: g++ main.cpp pixel_func.cpp -std=c++11
 * Run executable with pixels.dat on the command. Will return the flipped.dat file*/


int main(int argc, char** argv)
{

char *file = argv[1];				//assigning command line entry to a char* 

/*Opening a file with the name given by the command line entry and writing in pixel data given the describe x,y dimensions.This data will written in as a string and input in the csv format. */
std::ofstream MyFile;			
MyFile.open(file,std::ios::out);		//Opening pixels.dat file for writing into
std::string ss = makedata(512,256); 
MyFile<<ss;				
MyFile.close();					 

/*Opening the pixels.dat file and reading each line of the file to obtain the 5 data types that comprise the Pixel struct(x,y,r,g,b). Each line is entered into the Pixel* array that is then pushed into the Pixel* vector named as pixel_list*/
std::ifstream InputFile;
InputFile.open(file,std::ios::in);
std::vector<Pixel*> pixel_list;			//list of Pixel*
std::string line;
Pixel *p = new Pixel[SIZE];			//declaringa Pixel* array whose address will be input into the Pixel* vector
int ct =0;
while(!InputFile.eof())
{
	std::getline(InputFile, line);
	if(ct<SIZE)
	{
		add_pixel(line, (p+ct), pixel_list);  //(p+ct) traverses the Pixel* array so that the next address can be used to input into the pixel_list vector
	}
	ct++;	
}
InputFile.close();

/*Running the requested Pixel functions*/
std::cout<<"Size of list is: " <<pixel_list.size() <<std::endl; //Checking size of pixel_list vector equates to requested size
average_colors(pixel_list);	
flip_vertically(pixel_list);			

//Code for creating the flipped.dat file and entering the data for the transformed pixel vector into a string in the csv form
std::ofstream OutFile;
OutFile.open("flipped.dat", std::ios::out);
std::string os = outputdata(pixel_list);
OutFile<<os;
OutFile.close();

delete[] p;				//free Pixel* array 
return 0;
}
