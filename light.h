#pragma once
#include "color.h"
#include "vec.h"

class Light
{
  public:
	Vec3f pos;
	Color color;
	Light()
	{
		pos = Vec3f();
		color = Color(1,1,1,0);
	}
	Light(Vec3f pos,Color color):pos(pos),color(color){}

};