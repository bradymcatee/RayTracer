# RayTracer

A compact CPU ray tracer written in modern C++ (single-file main + headers) that renders a simple scene of spheres with diffuse, metal and dielectric materials. This project is a small implementation inspired by "Ray Tracing in One Weekend" and produces a PPM image.

## Features
- Basic Lambertian, metal and dielectric materials
- Depth-limited recursive ray tracing
- Antialiasing via multiple samples per pixel
- Thin lens defocus (depth of field)
- Outputs P3 PPM image

## Build
Requires a C++11/14/17-capable compiler. From the repository root:

g++ -std=c++17 -O2 main.cpp -o raytracer

(If your toolchain prefers clang: replace `g++` with `clang++`.)

## Run
Run and redirect output to a PPM file:

./raytracer > image.ppm

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
