#pragma once
#include "color.h"
#include "object.h"
#include "vec.h"

class Sphere : public Object
{
  public:
	Vec3f center;
	double radius;
	Color color;
	Sphere()
	{
		center = Vec3f(0, 0, 0);
		radius = 1.0;
		color = Color(0.5, 0.5, 0.5, 0);
	}
	Sphere(Vec3f center, double r, Color c) : center(center), radius(r), color(c) {}

	Vec3f getNormalAt(Vec3f point)
	{
		return (point - center).normalize();
	}
	Color getColor(){
		return color;
	}

	double intersect(Ray ray)
	{
		Vec3f ori = ray.origin;
		Vec3f dir = ray.direction;
		Vec3f oc = ori - center;
		double a = 1;
		double b = 2*(oc).dotProduct(dir);
		double c = oc.dotProduct(oc) - pow(radius, 2);

		double discrim = b * b - 4 * c;
		if (discrim > 0)
		{
			//光线与球面相交
			double root1 = (-b - sqrt(discrim)) / 2 - 0.000001;
			if (root1 > 0)
				return root1;

			else 
			{
				return (-b + sqrt(discrim)) / 2 - 0.000001;
			}
		}
		else
		{
			return -1;
		}
	}
};