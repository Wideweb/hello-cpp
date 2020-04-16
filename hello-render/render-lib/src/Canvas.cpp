#include "Canvas.hpp"

bool operator==(const Color &c1, const Color &c2) {
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b;
}

bool operator==(const Position &p1, const Position &p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

void Canvas::save(const std::string &fileName) {
    std::ofstream outfile(fileName, std::ios::binary);
    outfile << "P6" << std::endl;
    outfile << width << " " << height << " " << 255 << std::endl;
    outfile.write(reinterpret_cast<char *>(this), sizeof(Color) * size());

    outfile.close();
}

void Canvas::load(const std::string &fileName) {
    std::string img_format;
    int img_width;
    int img_height;
    int img_color_value;

    std::ifstream infile(fileName, std::ios::binary);
    infile >> img_format >> img_width >> img_height >> img_color_value;
    infile.read(reinterpret_cast<char *>(this), sizeof(Color) * size());
    infile.close();
}
