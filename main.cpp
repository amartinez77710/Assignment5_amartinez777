#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "pixel.h"

//This function will 
void average_colors(std::vector<Pixel> &pixel_list, int counter){
	float averageR = 0, averageG = 0, averageB = 0;
	for(int i = 0; i < counter; i++){
		averageR = averageR + pixel_list[i].r;
	}
	for(int i = 0; i < counter; i++){
                averageG = averageG + pixel_list[i].g;
        }
	for(int i = 0; i < counter; i++){
                averageB = averageB + pixel_list[i].b;
        }
	averageR = averageR/counter;
	averageG = averageG/counter;
	averageB = averageB/counter;

	std::cout << averageR << " is the average of R values\n" << std::endl;
	std::cout << averageB << " is the average of B values\n" << std::endl;
	std::cout << averageG << " is the average of G values\n" <<std::endl;

}
//This function will flip every y value in the vector vertically.
//I needed to add counter to the parameter, as i thought it was easier.
void flip_vertically(std::vector<Pixel> &pixel_list, int counter){
	for(int i = 0; i < counter/2; i++){
		int origin = 0;
		origin = pixel_list[i].y;
	       	pixel_list[i].y = pixel_list[counter - 1 - i].y;
		pixel_list[counter - 1 - i].y = origin;
	}
}

		

int main(int arg, char *argv[]){
	
	std::vector<Pixel> pixel_list;
	
	if(arg < 2){
		std::cout << "2 Arguments Please. Or needs correct file" << std::endl;
		return 0;
	}
	//TESTING READ from command line
	std::string filename = argv[1];
	std::ifstream file(filename);
	if(!file.is_open()){
		std::cout << "Could not open file" << std::endl;
		return 0;
	}
	//Loop to read files and seperation
	std::string line;
	int line_counter = 0;
	while(std::getline(file, line)){
		unsigned int start = 0;
		
		//Seperation for X
		unsigned int comma = line.find(',', start);
		std::string xString = line.substr(start, comma - start);
		start = comma + 1; // must index for the next value

		//Seperation for Y
		comma = line.find(',', start);
		std::string yString = line.substr(start, comma - start);
		start = comma + 1;

		//Seperation for R
		comma = line.find(',', start);
		std::string rString = line.substr(start, comma - start);
		start = comma + 1;

		//Seperation for G
		comma = line.find(',', start);
		std::string gString = line.substr(start, comma - start);
		start = comma + 1 ;

		//Seperation for B. Find() will not get another comma
		std::string bString = line.substr(start);
		
		//Conversions + Adding to Pixel_List
		//We can pass a container into Pixel_list with Pushback
		Pixel data;
			data.r = std::stof(rString);
			data.g = std::stof(gString);
			data.b = std::stof(bString);
			data.x = std::stoi(xString);
			data.y = std::stoi(yString);
		pixel_list.push_back(data);

		//To count the amount of lines read
		line_counter++;

		}

	//Average Colors call
	average_colors(pixel_list, line_counter);
	
	//Flipping pixels.dat
	flip_vertically(pixel_list, line_counter);

	//Printing into new file called flipped.dat
	std::ofstream outFile("flipped.dat");
	if (!outFile.is_open()){
		std::cout << "could not create file" << std::endl;
		return 1;
	}
	for(int i = 0; i < line_counter; i++){
		outFile << pixel_list[i].x << ", " << pixel_list[i].y << ", " << pixel_list[i].r << ", " << pixel_list[i].g << ", " << pixel_list[i].b << "\n";
	}
	outFile.close();



return 0;
}
	


