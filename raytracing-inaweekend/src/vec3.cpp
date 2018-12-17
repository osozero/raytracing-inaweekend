#include "vec3.h"


vec3& vec3::operator+=(const vec3&  v2)
{
	this->e[0] += v2.e[0];
	this->e[1] += v2.e[1];
	this->e[2] += v2.e[2];

	return *this;
}

vec3& vec3::operator-=(const vec3& v2)
{
	this->e[0] -= v2.e[0];
	this->e[1] -= v2.e[1];
	this->e[2] -= v2.e[2];

	return *this;
}

vec3& vec3::operator*=(const vec3& v2)
{
	this->e[0] *= v2.e[0];
	this->e[1] *= v2.e[1];
	this->e[2] *= v2.e[2];

	return *this;
}

vec3& vec3::operator/=(const vec3& v2)
{
	this->e[0] /= v2.e[0];
	this->e[1] /= v2.e[1];
	this->e[2] /= v2.e[2];

	return *this;
}

vec3& vec3::operator*=(const float f)
{
	this->e[0] *= f;
	this->e[1] *= f;
	this->e[2] *= f;

	return *this;
}

vec3& vec3::operator/=(float f)
{
	this->e[0] /= f;
	this->e[1] /= f;
	this->e[2] /= f;

	return *this;
}

void vec3::make_unit_vector()
{
	float length = this->length();

	this->e[0] /= length;
	this->e[1] /= length;
	this->e[2] /= length;
}
 
