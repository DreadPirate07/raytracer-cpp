#include <cstddef>
#include <limits>
#include <iostream>
#include <fstream>
#include <vector>
#include "geometry.h"

// renders a file of 
void render() {
    const int width = 1024;
    const int height = 768;
    std::vector<Vec3f> framebuffer(width*height);

    // vec3f values are manipulated from (0,0,0) to (1,1,0)
    for (size_t j=0;j<height;j++) {
        for (size_t i=0;i<width;i++) {
            framebuffer[i+j*width] = Vec3f(j/float(height),i/float(width),0);
        }
    }

    std::ofstream ofs;
    ofs.open("./out.ppm",std::ofstream::out | std::ofstream::binary);
    // PPM header - P6 file format
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (size_t i=0;i<height*width;++i) {
        for (size_t j=0;j<3;j++) {
            ofs << (char)(255*std::max(0.f,std::min(1.0f,framebuffer[i][j])));
        }
    }
    ofs.close();
}

int main() {
    render();
    return 0;
}