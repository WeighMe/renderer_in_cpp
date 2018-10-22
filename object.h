#pragma once
#include "vec.h"
#include "color.h"

class Object{
	public:
	Object(){}

	virtual Color getColor() { return Color(0, 0, 0, 0); }

	virtual double intersect(Ray ray){
		return 0;
	}
};