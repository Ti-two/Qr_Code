#include "image_utils.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Function to load an image using STB Image
ImageData loadImage(const char* imagePath) {
    ImageData img = {nullptr, 0, 0, 0};
    
    // Load the QR code image
    img.data = stbi_load(imagePath, &img.width, &img.height, &img.channels, 0);
    
    if (!img.data) {
        std::cerr << "Error: Unable to load image " << imagePath << std::endl;
        std::cerr << "Reason: " << stbi_failure_reason() << std::endl;
        return img;
    }
    
    std::cout << "QR code image loaded successfully:" << std::endl;
    std::cout << "- Dimensions: " << img.width << "x" << img.height << " pixels" << std::endl;
    std::cout << "- Color channels: " << img.channels << std::endl;
    
    return img;
}

// Function to convert image to grayscale with memory optimization (in-place)
void convertToGrayscale(const ImageData& img, std::vector<unsigned char>& grayData) {
    // Resize the output vector to the correct size
    grayData.resize(img.width * img.height);
    
    if (img.channels > 1) {
        std::cout << "Converting to grayscale with memory optimization" << std::endl;
        
        // Optimized conversion - direct storage in grayscale array
        for (int i = 0; i < img.width * img.height; ++i) {
            // Perceptual formula for better accuracy
            int grayValue = (
                img.data[i * img.channels] * 0.299 +      // Red
                img.data[i * img.channels + 1] * 0.587 +  // Green  
                img.data[i * img.channels + 2] * 0.114    // Blue
            );
            grayData[i] = static_cast<unsigned char>(grayValue);
        }
        
        std::cout << "Original memory: " << img.width * img.height * img.channels << " bytes" << std::endl;
        std::cout << "Optimized memory: " << img.width * img.height << " bytes" << std::endl;
        std::cout << "Memory saved: " << (img.width * img.height * img.channels - img.width * img.height) << " bytes" << std::endl;
        
    } else {
        // Image already in grayscale - direct copy
        std::cout << "Image already in grayscale - copying directly" << std::endl;
        for (int i = 0; i < img.width * img.height; ++i) {
            grayData[i] = img.data[i];
        }
    }
}

// Function to convert grayscale to binary (black and white) - in-place
void convertToBinary(const std::vector<unsigned char>& grayData, 
                     int width, int height, std::vector<unsigned char>& binaryData,
                     unsigned char threshold) {
    // Resize the output vector to the correct size
    binaryData.resize(width * height);
    
    std::cout << "Converting to binary (black & white) with threshold: " << (int)threshold << std::endl;
    
    int blackPixels = 0, whitePixels = 0;
    
    for (int i = 0; i < width * height; ++i) {
        if (grayData[i] < threshold) {
            binaryData[i] = 0;      // Black
            blackPixels++;
        } else {
            binaryData[i] = 255;    // White
            whitePixels++;
        }
    }
    
    std::cout << "Binary conversion complete:" << std::endl;
    std::cout << "- Black pixels: " << blackPixels << std::endl;
    std::cout << "- White pixels: " << whitePixels << std::endl;
    std::cout << "- Black ratio: " << (float)blackPixels / (width * height) * 100 << "%" << std::endl;
}

// Function to save grayscale image
bool saveGrayscaleImage(const std::vector<unsigned char>& grayData, 
                        int width, int height, const char* outputPath) {
    int result = stbi_write_png(outputPath, width, height, 1, grayData.data(), width);
    
    if (result) {
        std::cout << "Grayscale image saved: " << outputPath << std::endl;
        return true;
    } else {
        std::cerr << "Error saving the image: " << outputPath << std::endl;
        return false;
    }
}
