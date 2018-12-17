#include <iostream>
#include "vec3.h"
#include "ray.h"

//dot((p-c),(p-c)) = R*R
// dot(p(t)-c,p(t)-c))=R*R
//p(t) = A + t*B; (point_at_parameter (ray.h)) A=center of ray, B= direction
// dot((A+t*B-C), (A+t*B-C)) = R*R // R= radius of sphere
//t*t*dot(B,B)+2*t*dot(B,A-C)+dot(A-C,A-C) - R*R = 0
// calculate discriminant
bool hit_sphere(const vec3 &center, float radius, const ray &r)
{
	//C = A - C = center of ray - Center
	vec3 oc = r.origin() - center;

	float a = dot(r.direction(), r.direction());
	float b = 2 * dot(r.direction(), oc);
	float c = dot(oc, oc) - radius * radius;

	//discriminant = b*b - 4*a*c; if discriminant >0 then there is 2 solution, if disc=0  then there is 1 solution, if disc<0 then there is no real solution.
	float discriminant = b * b - 4 * a*c;


	//if disc==0 then ray is tangent(teget) with the sphere, if disc>0 then ray hits the sphere
	return discriminant > 0;
}

vec3 color(const ray& r)
{
	if(hit_sphere(vec3(0,0,1),0.5,r))
	{
		return vec3(1.0, 0.0, 0.0);
	}

	vec3 unit_direction = unit_vector(r.direction());
	float f = 0.5 * (unit_direction.y() + 1.0);

	return (1.0 - f)*vec3(1.0f, 1.0f, 1.0f) + f * vec3(0.5f, 0.7f, 1.0f);
}

int main()
{
	int nx = 200;
	int ny = 100;

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);

	vec3 horizontal(4.0f, 0.0f, 0.0f);

	vec3 vertical(0.0f, 2.0f, 0.0f);

	vec3 origin(0.0f, 0.0f, 0.0f);

	for(int j=ny-1;j>=0;j--)
	{
		for(int i=0;i<nx;i++)
		{
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);

			ray r(origin, lower_left_corner + u * horizontal + v * vertical);

			vec3 col = color(r);
			
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);

			std::cout << ir << " " << ig << " " << ib << std::endl;
		}
	}

	return 0;
}