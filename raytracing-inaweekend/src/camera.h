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

	vec3 u, v, w;
	float lens_radius;

	ray get_ray(float u, float v);

	camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov,float aspect,float aperture,float focus_dist);
};

