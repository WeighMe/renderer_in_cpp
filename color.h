#pragma once

class Color{
public:
	double red,green,blue,special;

	Color():red(0.5),green(0.5),blue(0.5),special(0){}
	Color(double r,double g,double b,double s):red(r),green(g),blue(b),special(s){}
};