#include <cstddef>
#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include "geometry.h"

void render() {
    const int width = 1024;
    const int height = 768;
    std::vector<Vec3f> framebuffer(width*height);

    for (size_t j=0;j<height;j++) {
        for (size_t i=0;i<width;i++) {
            framebuffer[i+j*width] = Vec3f(j/float(height))
        }
    }
}