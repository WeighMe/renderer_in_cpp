#pragma once
#include <cmath>

template <typename T>
class Vec3
{

  public:
	T x, y, z;
	Vec3() : x(0), y(0), z(0) {}
	Vec3(T xx) : x(xx), y(xx), z(xx) {}
	Vec3(T x1, T y1, T z1) : x(x1), y(y1), z(z1) {}

	//
	T X() const { return x; }
	T Y() const { return y; }
	T Z() const { return z; }

	T norm() const { return x * x + y * y + z * z; }
	T length()
	{
		return sqrt(norm());
	}
	Vec3 &normalize()
	{
		T n = norm();
		if (n > 0)
		{
			T fac = 1 / sqrt(n);
			x *= fac, y *= fac, z *= fac;
		}
		return *this;
	}
	const T &operator[](unsigned char i) const { return (&x)[i]; }

	//加减乘除
	Vec3
	operator+(const Vec3<T> &v1)
	{
		return Vec3(x + v1.x, y + v1.y, z + v1.z);
	}
	Vec3 operator-(const Vec3<T> &v1)
	{
		return Vec3(x - v1.x, y - v1.y, z + v1.z);
	}
	Vec3 operator*(const T &n)
	{
		return Vec3(x * n, y * n, z * n);
	}
	Vec3 &operator-()
	{
		x = -x, y = -y, z = -z;
		return *this;
	}
	T dotProduct(const Vec3<T> &v)
	{
		return x * v.x + y * v.y + z * v.z;
	}
	Vec3 crossProduct(const Vec3<T> &v)
	{
		return Vec3<T>(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;
typedef Vec3<double> Vec3d;

class Ray
{

  public:
	Vec3f origin, direction;
	Ray()
	{
		origin = Vec3f();
		direction = Vec3f(1, 0, 0);
	}
	Ray(Vec3f o, Vec3f d) : origin(o), direction(d) {}

	Vec3f getDirection() { return direction; }
	Vec3f getOrigin() { return origin; }
};

class Camera
{
	

  public:
	Vec3f pos, dir, right, down;
	Camera()
	{
		pos = Vec3f(0, 0, 0);
		dir = Vec3f(0, 0, 1);
		right = Vec3f(0, 0, 0);
		down = Vec3f(0, 0, 0);
	}
	Camera(Vec3f pos, Vec3f dir, Vec3f right, Vec3f down) : pos(pos), dir(dir), right(right), down(down) {}
	Vec3f getPos() { return pos; }
};