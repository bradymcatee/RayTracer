# RayTracer

A compact CPU ray tracer written in modern C++ (single-file main + headers) that renders a simple scene of spheres with diffuse, metal and dielectric materials. This project is a small implementation inspired by "Ray Tracing in One Weekend" and produces a PPM image.

## Features
- Basic Lambertian, metal and dielectric materials
- Depth-limited recursive ray tracing
- Antialiasing via multiple samples per pixel
- Thin lens defocus (depth of field)
- Outputs P3 PPM image

## Build
Option A: CMake

mkdir -p build && cd build && cmake .. && cmake --build . --config Release

Option B: One-shot compile

g++ -std=c++17 -O3 -DNDEBUG -fopenmp main.cpp -o raytracer
# Clang (if installed):
# clang++ -std=c++17 -O3 -DNDEBUG -fopenmp=libomp -lomp main.cpp -o raytracer

(Use clang++ if preferred.)

## Run
Run and redirect output to a PPM file:

./raytracer > image.ppm
# With OpenMP parallelism (example with 8 threads):
OMP_NUM_THREADS=8 ./raytracer --width 800 --height 450 --spp 50 --bounces 10 > image.ppm

CLI options:
- --width <int>    image width in pixels (default 1200)
- --height <int>   image height; if set, overrides aspect ratio
- --spp <int>      samples per pixel (default 500)
- --bounces <int>  max path depth (default 50)
- --vfov <deg>     vertical field of view (default 20)
- --defocus <deg>  lens defocus angle (default 0.6)
- --focus <dist>   focus distance (default 10)
- --seed <n|random> RNG seed (default 1337; use "random" for non-deterministic)

Timing
The renderer prints elapsed time, total rays, and rays/sec to stderr.

Open `image.ppm` with an image viewer that supports PPM or convert it with ImageMagick:

convert image.ppm image.png

## Configuration
Camera and render settings are in `camera.h` (image size, samples per pixel, max depth, defocus angle, focus distance). Scene objects are created in `main.cpp`.

## Project structure
- main.cpp — scene setup and render entrypoint
- *.h — small headers for vectors, rays, materials, shapes, camera, etc.
- image.ppm — example output

## License & Credits
Inspired by Peter Shirley's "Ray Tracing in One Weekend". Use and modify as you like; add a license file if you plan to publish.
