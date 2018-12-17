#pragma once
#include <stdexcept>
#include <string>

class vec3
{
public:
	float e[3];
	vec3(): e{}
	{
	};

	vec3(float e0,float e1,float e2)
	{
		e[0] = e0;
		e[1] = e1;
		e[2] = e2;
	}

	inline float x() const { return e[0]; }
	inline float y() const { return e[1]; }
	inline float z() const { return e[2]; }
	inline float r() const { return e[0]; }
	inline float g() const { return e[1]; }
	inline float b() const { return e[2]; }

	inline const vec3& operator+() const { return *this; };
	inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	inline float operator[](int i) const
	{
		if((i<0) || (i>=3))
		{
			throw std::out_of_range("vec3 index must be between 0-2");
		}
		return e[i];
	}

	inline float& operator[](int i)
	{
		if ((i < 0) || (i >= 3))
		{
			throw std::out_of_range("vec3 index must be between 0-2");
		}
		return e[i];
	}

	vec3& operator+=(const vec3 &v2);
	vec3& operator-=(const vec3 &v2);
	vec3& operator*=(const vec3 &v2);
	vec3& operator/=(const vec3 &v2);
	vec3& operator*=(float f);
	vec3& operator/=(float f);

	inline float length() const
	{
		return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	}

	inline float squared_length() const
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	void make_unit_vector();
};

//non member inline functions

inline std::istream& operator>>(std::istream &is,vec3 &v)
{
	is >> v.e[0] >> v.e[1] >> v.e[2];
	return is;
}

inline std::ostream& operator<<(std::ostream &os,const vec3 &v)
{
	os << v.e[0] <<" " <<v.e[1] << " " << v.e[2];
	return os;
}

inline vec3 operator+(const vec3 &v1,const vec3 &v2)
{
	return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2)
{
	return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2)
{
	return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline vec3 operator/(const vec3 &v1, const vec3 &v2)
{
	return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline vec3 operator*(const vec3 &v1, float f)
{
	return vec3(v1.e[0] * f, v1.e[1] * f, v1.e[2] * f);
}

inline vec3 operator*(float f, const vec3 &v1)
{
	return v1 * f;
}

inline vec3 operator/(const vec3 &v1, float f)
{
	return vec3(v1.e[0] / f, v1.e[1] / f, v1.e[2] / f);
}

inline float dot(const vec3 &v1, const vec3 &v2)
{
	return v1.e[0] * v2.e[0]
		+ v1.e[1] * v2.e[1]
		+ v1.e[2] * v2.e[2];
}

inline vec3 cross(const vec3 &v1, const vec3 &v2)
{
	return vec3((v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
		(-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0])),
		(v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
}

inline vec3 unit_vector(vec3 v)
{
	return v / v.length();
}
