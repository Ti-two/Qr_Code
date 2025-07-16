#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

#include <vector>

// Forward declaration for STB functions
extern "C" {
    void stbi_image_free(void *retval_from_stbi_load);
}

// Structure to hold image data
struct ImageData {
    unsigned char* data;
    int width;
    int height;
    int channels;
};

// Function declarations
ImageData loadImage(const char* imagePath);
std::vector<unsigned char> convertToGrayscale(const ImageData& img);
bool saveGrayscaleImage(const std::vector<unsigned char>& grayData, 
                        int width, int height, const char* outputPath);

#endif // IMAGE_UTILS_H
