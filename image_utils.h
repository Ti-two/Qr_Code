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
void convertToGrayscale(const ImageData& img, std::vector<unsigned char>& grayData);
void convertToBinary(const std::vector<unsigned char>& grayData, 
                     int width, int height, std::vector<unsigned char>& binaryData,
                     unsigned char threshold = 128);
bool saveGrayscaleImage(const std::vector<unsigned char>& grayData, 
                        int width, int height, const char* outputPath);

#endif // IMAGE_UTILS_H
