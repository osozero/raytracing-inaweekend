#include <iostream>
#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "sphere.h"
#include "hitable_list.h"
#include <limits>
#include "camera.h"
#include <random>


vec3 random_in_unit_sphere()
{
	std::default_random_engine gen;
	std::uniform_real_distribution<float> dist(0.0, 1.0);

	vec3 p;

	do
	{
		p = 2.0*vec3(dist(gen), dist(gen), dist(gen)) - vec3(1.0, 1.0, 1.0);
	} while (p.squared_length() >= 1.0);

	return p;
}

vec3 color(const ray& r,hitable *world)
{
	
	hit_record rec;

	if(world->hit(r,0.001,std::numeric_limits<float>::max(),rec))
	{
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5*color(ray(rec.p, target - rec.p), world);
	}

	vec3 unit_direction = unit_vector(r.direction());
	float f = 0.5 * (unit_direction.y() + 1.0);

	return (1.0 - f)*vec3(1.0f, 1.0f, 1.0f) + f * vec3(0.5f, 0.7f, 1.0f);
}



int main()
{
	int nx = 200;
	int ny = 100;
	int ns = 100;

	std::default_random_engine gen;
	std::uniform_real_distribution<float> dist(0.0,1.0);

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	
	hitable *list[2];

	list[0] = new sphere(vec3(0.0, 0.0, -1.0), 0.5);
	list[1] = new sphere(vec3(0.0, -100.5, -1.0), 100);

	hitable *world = new hitable_list(list, 2);

	camera cam;

	for(int j=ny-1;j>=0;j--)
	{
		for(int i=0;i<nx;i++)
		{
			vec3 col(0, 0, 0);

			for(int s=0;s<ns;s++)
			{
				float u = float(i +dist(gen)) / float(nx);
				float v = float(j + dist(gen)) / float(ny);
				
				ray r = cam.get_ray(u, v);

				vec3 p = r.point_at_parameter(2.0);
				col += color(r, world);
			}

			col /= float(ns);
			
			//gamma 2
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);

			std::cout << ir << " " << ig << " " << ib << std::endl;
		}
	}

	return 0;
}