#pragma once
#pragma pack(2)
#include "color.h"
#include <cmath>
#include <fstream>
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long LONG;

struct BmpFileHeader
{
	WORD bfType;
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
};

struct BmpInfoHeader
{
	DWORD biSize;		  //0-3
	LONG biWidth;		  //4-7
	LONG biHeight;		  //8-11
	WORD biPlanes;		  //12-13
	WORD biBitCount;	  //14-15
	DWORD biCompression;  //16-19
	DWORD biSizeImage;	//20-23
	LONG biXPelsPerMeter; //24-27
	LONG biYPelsPerMeter; //28-31
	DWORD biClrUsed;	  //32-35
	DWORD biClrImportant; //36-39
};

struct RGBType
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	void set(unsigned char r1, unsigned char g1, unsigned char b1)
	{
		r = r1;
		g = g1;
		b = b1;
	}
	void set(Color color)
	{
		r = (int)floor(color.red * 255);
		g = (int)floor(color.green * 255);
		b = (int)floor(color.blue * 255);
	}
};

void saveBmp(const char *fileName, int w, int h, int dpi, RGBType *data)
{
	int size = 4 * w * h;

	//设置bmpfileheader的各种数值
	BmpFileHeader fileHeader;
	fileHeader.bfType = 0x4D42;
	fileHeader.bfReserved1 = 0;
	fileHeader.bfReserved2 = 0;
	fileHeader.bfSize = 54 + size;
	fileHeader.bfOffBits = 54;

	//设置infoheader的值
	BmpInfoHeader infoHeader = {0};
	infoHeader.biSize = 40;
	infoHeader.biHeight = -h;
	infoHeader.biWidth = w;
	infoHeader.biPlanes = 1;
	infoHeader.biBitCount = 24;
	infoHeader.biSizeImage = 0;
	infoHeader.biCompression = 0;

	FILE *output = fopen(fileName, "wb");
	if (output)
	{
		fwrite(&fileHeader, 14, 1, output);
		fwrite(&infoHeader, 40, 1, output);
		for (int i = 0; i < w * h; ++i)
		{
			RGBType rgb = data[i];
			// unsigned char r = (int)(floor(255 * rgb.r));
			// unsigned char g = (int)(floor(255 * rgb.g));
			// unsigned char b = (int)(floor(255 * rgb.b));

			unsigned char color[3] = {rgb.r, rgb.g, rgb.b};
			fwrite(color, 3, 1, output);
		}
		fclose(output);
	}
}