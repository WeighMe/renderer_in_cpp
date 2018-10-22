#pragma once

#include "color.h"
#include "object.h"
#include "vec.h"

class Plane : public Object
{

  public:
	Vec3f normal;
	double distance;
	Color color;

	Plane()
	{
		normal = Vec3f(1, 0, 0);
		distance = 0;
		color = Color(0.5, 0.5, 0.5, 0);
	}
	Plane(Vec3f normal, double dis, Color c) : normal(normal), distance(dis), color(c) {}

	Color getColor() { return color; }

	double intersect(Ray ray)
	{
		Vec3f direct = ray.direction;
		double a = direct.dotProduct(normal);
		if (a == 0)
		{
			return -1;
		}
		else
		{
			double b = normal.dotProduct(ray.origin - (normal * distance));
			return -b / a;
		}
	}
};