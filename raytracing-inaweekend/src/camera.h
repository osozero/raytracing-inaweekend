#pragma once
#include "vec3.h"
#include "ray.h"

class camera
{
public:
	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;

	ray get_ray(float u, float v);

	camera();
};

