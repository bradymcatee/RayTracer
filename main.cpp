#include "rt.h"
#include <chrono>


#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

int main(int argc, char* argv[]) {
  hittable_list world;

  auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
  world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      auto choose_mat = random_double();
      point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

      if ((center - point3(4, 0.2, 0)).length() > 0.9) {
        shared_ptr<material> sphere_material;

        if (choose_mat < 0.8) {
          // diffuse
          auto albedo = color::random() * color::random();
          sphere_material = make_shared<lambertian>(albedo);
          world.add(make_shared<sphere>(center, 0.2, sphere_material));
        } else if (choose_mat < 0.95) {
          // metal
          auto albedo = color::random(0.5, 1);
          auto fuzz = random_double(0, 0.5);
          sphere_material = make_shared<metal>(albedo, fuzz);
          world.add(make_shared<sphere>(center, 0.2, sphere_material));
        } else {
          // glass
          sphere_material = make_shared<dielectric>(1.5);
          world.add(make_shared<sphere>(center, 0.2, sphere_material));
        }
      }
    }
  }

  auto material1 = make_shared<dielectric>(1.5);
  world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

  auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
  world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

  auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
  world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

  camera cam;

  // CLI defaults and parsing
  uint64_t seed = 1337;
  int width = 1200;
  int height = 0;
  int spp = 500;
  int bounces = 50;
  double vfov = 20;
  double defocus = 0.6;
  double focus = 10.0;
  for (int i = 1; i < argc; ++i) {
    const char* arg = argv[i];
    auto next = [&](void) -> const char* { return (i+1 < argc) ? argv[++i] : nullptr; };
    if (strcmp(arg, "--width") == 0) { const char* v = next(); if (v) width = atoi(v); }
    else if (strcmp(arg, "--height") == 0) { const char* v = next(); if (v) height = atoi(v); }
    else if (strcmp(arg, "--spp") == 0) { const char* v = next(); if (v) spp = atoi(v); }
    else if (strcmp(arg, "--bounces") == 0) { const char* v = next(); if (v) bounces = atoi(v); }
    else if (strcmp(arg, "--vfov") == 0) { const char* v = next(); if (v) vfov = atof(v); }
    else if (strcmp(arg, "--defocus") == 0) { const char* v = next(); if (v) defocus = atof(v); }
    else if (strcmp(arg, "--focus") == 0) { const char* v = next(); if (v) focus = atof(v); }
    else if (strcmp(arg, "--seed") == 0) { const char* v = next(); if (v) { if (strcmp(v, "random") == 0) seed = non_deterministic_seed(); else seed = strtoull(v, nullptr, 10); } }
  }
  seed_rng(seed);

  cam.aspect_ratio      = (height > 0) ? (double(width) / double(height)) : (16.0 / 9.0);
  cam.image_width       = width;
  cam.samples_per_pixel = spp;
  cam.max_depth         = bounces;

  cam.vfov     = vfov;
  cam.lookfrom = point3(13,2,3);
  cam.lookat   = point3(0,0,0);
  cam.vup      = vec3(0,1,0);

  cam.defocus_angle = defocus;
  cam.focus_dist    = focus;

  auto t0 = std::chrono::steady_clock::now();
  cam.render(world);
  auto t1 = std::chrono::steady_clock::now();
  double secs = std::chrono::duration<double>(t1 - t0).count();
  unsigned long long rays = cam.rays_traced;
  double rps = (secs > 0.0) ? (double(rays) / secs) : 0.0;
  std::clog << "Elapsed: " << secs << " s, Rays: " << rays << ", Rays/sec: " << rps << "\n";
}
