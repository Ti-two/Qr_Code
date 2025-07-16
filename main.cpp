#include <iostream>
#include <string>
#include "image_utils.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <qrcode_image_path>" << std::endl;
        return 1;
    }

    const char* imagePath = argv[1];
    
    // Load the image
    ImageData img = loadImage(imagePath);
    if (!img.data) {
        return 1;
    }
    
    // Convert to grayscale
    std::vector<unsigned char> grayData = convertToGrayscale(img);
    
    // Free the original image - we don't need it anymore!
    stbi_image_free(img.data);
    
    // Save the grayscale image
    std::string outputPath = "output_grayscale.png";
    bool success = saveGrayscaleImage(grayData, img.width, img.height, outputPath.c_str());
    
    if (!success) {
        return 1;
    }
    
    // Now you can use grayData for QR code processing
    // Access pixel at (x, y): grayData[y * width + x]
    
    std::cout << "Optimized data ready for QR code processing" << std::endl;
    
    return 0;
}