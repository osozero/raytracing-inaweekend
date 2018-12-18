#define _USE_MATH_DEFINES
#include "camera.h"
#include <random>

vec3 random_in_unit_disk()
{
	vec3 p;

	std::default_random_engine gen;
	std::uniform_real_distribution<float> dist(0.0, 1.0);

	do
	{
		p = 2.0*vec3(dist(gen), dist(gen), 0) - vec3(1, 1, 0);
	} while (dot(p, p) >= 1);

	return p;
}


ray camera::get_ray(float s, float t)
{
	vec3 rd = lens_radius * random_in_unit_disk();
	vec3 offset = u * rd.x() + v * rd.y();

	return ray(origin+offset, lower_left_corner + s * horizontal + t * vertical - origin-offset);
}

camera::camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist)
{
	lens_radius = aperture / 2;
	float theta = vfov * M_PI / 180;
	float half_height = tan(theta / 2);
	float half_width = aspect * half_height;

	origin = lookfrom;

	w = unit_vector(lookfrom - lookat);
	u = unit_vector(cross(vup, w));
	v = cross(w, u);

	lower_left_corner = origin - half_width * u*focus_dist - half_height * v*focus_dist - w*focus_dist;
	horizontal = 2 * half_width*u*focus_dist;
	vertical = 2 * half_height*v*focus_dist;
}

