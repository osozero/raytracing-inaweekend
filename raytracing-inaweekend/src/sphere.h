#pragma once
#include "hitable.h"

class sphere
	:public hitable
{
public:
	vec3 center;
	float radius;
	sphere(){};

	sphere(vec3 cen, float r) :center{ cen }, radius(r){};

};

