#include "lfbg/graphics.h"

namespace lfbg {

#pragma pack(push, 1)
struct BMPFileHeader {
    char file_type[2];    // File type always BM which is 0x4D42
    uint32_t file_size;   // Size of the file (in bytes)
    uint16_t reserved1;   // Reserved, always 0
    uint16_t reserved2;   // Reserved, always 0
    uint32_t offset_data; // Start position of pixel data (bytes from the beginning of the file)

    void print() {
        std::cout << "file_type: " << std::string(file_type, file_type + 2) << std::endl;
        std::cout << "file_size: " << file_size << std::endl;
        std::cout << "reserved1: " << reserved1 << std::endl;
        std::cout << "reserved2: " << reserved2 << std::endl;
        std::cout << "offset_data: " << offset_data << std::endl;
    }
};
#pragma pack(pop)

#pragma pack(push, 1)
struct BMPInfoHeader {
    uint32_t size;      // Size of this header (in bytes)
    int32_t width;      // width of bitmap in pixels
    int32_t height;     // width of bitmap in pixels
                        //       (if positive, bottom-up, with origin in lower left corner)
                        //       (if negative, top-down, with origin in upper left corner)
    uint16_t planes;    // No. of planes for the target device, this is always 1
    uint16_t bit_count; // No. of bits per pixel
    uint32_t
        compression; // 0 or 3 - uncompressed. THIS PROGRAM CONSIDERS ONLY UNCOMPRESSED BMP images
    uint32_t size_image; // 0 - for uncompressed images
    int32_t x_pixels_per_meter;
    int32_t y_pixels_per_meter;
    uint32_t colors_used;      // No. color indexes in the color table. Use 0 for the max number of
                               // colors allowed by bit_count
    uint32_t colors_important; // No. of colors used for displaying the bitmap. If 0 all colors are
                               // required

    void print() {
        std::cout << "size: " << size << std::endl;
        std::cout << "width: " << width << std::endl;
        std::cout << "height: " << height << std::endl;
        std::cout << "planes: " << planes << std::endl;
        std::cout << "bit_count: " << bit_count << std::endl;
        std::cout << "compression: " << compression << std::endl;
        std::cout << "size_image: " << size_image << std::endl;
        std::cout << "x_pixels_per_meter: " << x_pixels_per_meter << std::endl;
        std::cout << "y_pixels_per_meter: " << y_pixels_per_meter << std::endl;
        std::cout << "colors_used: " << colors_used << std::endl;
        std::cout << "colors_important: " << colors_important << std::endl;
    }
};
#pragma pack(pop)

Image Image::fromBMP(const char* fname) {
    Image img;
    std::ifstream fin(fname, std::ios::binary);
    if (!fin)
        throw std::runtime_error("File " + std::string(fname) + " not found.");

    BMPFileHeader header;
    fin.read((char*)&header, sizeof(header));
    // header.print();

    BMPInfoHeader info;
    fin.read((char*)&info, sizeof(info));
    // info.print();

    if (info.compression != 0 && info.compression != 3) {
        fin.close();
        throw std::runtime_error("Compressed BMP is not supported.");
    }

    img.bit_depth = info.bit_count;
    img.width = info.width;
    img.height = std::abs(info.height);
    if (info.bit_count == 32) {
        img.pixels.resize(img.width * img.height * 4);
        auto buf = (color*)img.pixels.data();
        for (int y = 0; y < img.height; y++)
            fin.read((char*)(buf + y * img.width), img.width * 4);
    }

    fin.close();
    return img;
}

void Image::draw(int x, int y) const {
    if (bit_depth == 32) {
        auto buf = (color*)pixels.data();
        for (int i = 0, k = 0; i < height; i++)
            for (int j = 0; j < width; j++, k++)
                putpixel(x + j, y + i, buf[k]);
    }
}

} // namespace lfbg