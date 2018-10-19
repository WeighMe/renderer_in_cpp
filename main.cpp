#include "func.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{

	cout << "rendering";

	int dpi = 72;
	int width = 640;
	int height = 480;
	int n = width * height;
	RGBType *pixels = new RGBType[n];
	for (int x = 0;x<width;++x){
		for(int y=0;y<height;++y){
			int i=y*width+x;
			if((x>100&&x<200) && (y>0 &&y<400)){
				pixels[i].set(66, 77, 88);
			}else
				pixels[i].set(23,233,16);	
		}
	}
	saveBmp("scene.bmp", width, height, dpi, pixels);
	return 0;
}