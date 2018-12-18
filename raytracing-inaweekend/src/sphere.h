#pragma once
#include "hitable.h"

class sphere
	:public hitable
{
public:
	vec3 center;
	float radius;
	material *mat;

	sphere(vec3 cen, float r, material *m) :center{ cen }, radius(r),mat(m){};


	virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const;
};


