#include "color.h"
#include "func.h"
#include "light.h"
#include "plane.h"
#include "sphere.h"
#include "vec.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int firstObj(vector<double> objects)
{
	if (objects.empty())
		return -1;
	sort(objects.begin(), objects.end());
	for (int i = 0; i < objects.size(); ++i)
	{
		if (objects[i] > 0)
			return i;
	}
	return -1;
}

int main(int argc, char *argv[])
{

	cout << "rendering";

	int dpi = 72;
	int width = 640;
	int height = 480;
	int n = width * height;

	RGBType *pixels = new RGBType[n];
	double aspectratio = (double)width / (double)height;

	Vec3f campos(5, 1.5, 0);
	Vec3f look(0, 0, 0);
	Vec3f camdir = (look - campos).normalize();
	Vec3f camright = camdir.crossProduct(Vec3f(0, 1, 0)).normalize();
	Vec3f camdown = camdir.crossProduct(Vec3f(0, 0, 1));
	Camera sceneCam(campos, camdir, camright, camdown);

	Vec3f lightpos(-7, 10, -10);
	Color white(1.0, 1.0, 1.0, 0);
	//Color blue(0.0, 0.0, 0.8, 0.3);
	Color maroon(0.5, 0.25, 0.25, 0);
	Light sceneLight(lightpos, white);

	//scene objects
	Sphere sceneSphere(Vec3f(0, 0, 0), 1, Color(0.6,1.0,0.5,0.3));
	Plane scenePlane(Vec3f(0, 1, 0), -1, maroon);

	vector<Object *> scene_objects;
	scene_objects.push_back(&sceneSphere);
	scene_objects.push_back(&scenePlane);

	double xamnt, yamnt;

	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			int i = y * width + x;
			if (width > height)
			{
				xamnt = ((x + 0.5) / width) * aspectratio - ((width - height) / (double)height) / 2;
				yamnt = ((height - y) + 0.5) / height;
			}
			else if (height > width)
			{
				xamnt = (x + 0.5) / width;
				yamnt = (((height - y) + 0.5) / height) / aspectratio-((height-width)/(double)width)/2;
			}
			else
			{
				xamnt = (x + 0.5) / width;
				yamnt = ((height - y) + 0.5) / height;
			}
			//发射从摄像机到该像素的射线到场景中。
			Vec3f cam_ray_origin = sceneCam.pos;
			Vec3f cam_ray_dir = (camdir + camright * (xamnt - 0.5) + camdown * (yamnt - 0.5)).normalize();
			Ray cam_ray(cam_ray_origin, cam_ray_dir);

			vector<double> intersections;

			for (int index = 0; index < scene_objects.size(); ++index)
			{
				intersections.push_back(scene_objects.at(index)->intersect(cam_ray));
			}
			int idx_of_first_obj = firstObj(intersections);

			if (idx_of_first_obj == -1)
			{
				pixels[i].set(0, 0, 0);
			}
			else
			{
				Color color = scene_objects[idx_of_first_obj]->getColor();
				pixels[i].set(color);
			}
		}
	}
	saveBmp("scene.bmp", width, height, dpi, pixels);
	return 0;
}