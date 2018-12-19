#include <iostream>
#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "sphere.h"
#include "hitable_list.h"
#include <limits>
#include "camera.h"
#include <random>
#include "material.h"
#include <corecrt_math_defines.h>

#include <string>
#include <sstream>
#include <thread>

vec3 color(const ray& r, hitable *world, int depth) {
	hit_record rec;
	if (world->hit(r, 0.001, std::numeric_limits<float>::max(), rec)) {
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation * color(scattered, world, depth + 1);
		}
		else {
			return vec3(0, 0, 0);
		}
	}
	else {
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5*(unit_direction.y() + 1.0);
		return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}

hitable *random_scene() {
	std::default_random_engine gen;
	std::uniform_real_distribution<float> dist(0.0, 1.0);

	int n = 500;
	hitable **list = new hitable*[n + 1];
	list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
	int i = 1;
	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			float choose_mat = dist(gen);
			vec3 center(a + 0.9*dist(gen), 0.2, b + 0.9*dist(gen));
			if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
				if (choose_mat < 0.95) {  // diffuse
					list[i++] = new sphere(center, 0.2, new lambertian(vec3(dist(gen)*dist(gen), dist(gen)*dist(gen), dist(gen)*dist(gen))));
				}
				else if (choose_mat < 0.98) { // metal
					list[i++] = new sphere(center, 0.2,
						new metal(vec3(0.5*(1 + dist(gen)), 0.5*(1 + dist(gen)), 0.5*(1 + dist(gen))), 0.5*dist(gen)));
				}
				else {  // glass
					list[i++] = new sphere(center, 0.2, new dielectric(1.5));
				}
			}
		}
	}

	list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
	list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
	list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));

	return new hitable_list(list, i);
}

std::stringstream sstream[100];

void multithreaded(int index,camera &cam, hitable * world)
{
	int tCount = 16;

	int nx = 1200;
	int ny = 800;
	int ns = 10;

	int ySlice = ny/16;
	int xSlice = nx;

	std::default_random_engine gen;
	std::uniform_real_distribution<float> dist(0.0, 1.0);

	using namespace  std::chrono_literals;

	for (int j = ny-(ySlice*index)-1; j >= ny-ySlice*(index+1); j--) {
		for (int i = 0; i < nx; i++) {
			std::this_thread::sleep_for(3ms);
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				float u = float(i + dist(gen)) / float(nx);
				float v = float(j + dist(gen)) / float(ny);

				ray r = cam.get_ray(u, v);
				vec3 p = r.point_at_parameter(2.0);
				col += color(r, world, 0);
			}
			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			sstream[index]<< ir << " " << ig << " " << ib << "\n";
		}
	}
}


int main()
{
	auto start = std::chrono::system_clock::now();

	int nx = 1200;
	int ny = 800;
	int ns = 10;

	std::default_random_engine gen;
	std::uniform_real_distribution<float> dist(0.0, 1.0);

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	hitable *list[5];
	float R = cos(M_PI / 4);
	list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
	list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.0));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
	list[4] = new sphere(vec3(-1, 0, -1), -0.45, new dielectric(1.5));
	hitable *world = new hitable_list(list, 5);
	world = random_scene();

	vec3 lookfrom(13, 2, 3);
	vec3 lookat(0, 0, 0);
	float dist_to_focus = 10.0;
	float aperture = 0.1;

	camera cam(lookfrom, lookat, vec3(0, 1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus);

	std::thread t_arr[16];

	for(int i=0;i<16;i++)
	{
		t_arr[i] = std::thread(multithreaded, i, std::ref(cam), world);
	}


	for(int i=0;i<16;i++)
	{
		t_arr[i].join();
	}

	for(int i=0;i<16;i++)
	{
	
		std::cout << std::noskipws << sstream[i].rdbuf();
	}

	auto end = std::chrono::system_clock::now();
	auto elapsed = end - start;

	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << std::endl;
	
	return 0;
}