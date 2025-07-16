#include <iostream>
#include <string>
#include "image_utils.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <qrcode_image_path>" << endl;
        return 1;
    }

    const char* imagePath = argv[1];
    
    // Load the image
    ImageData img = loadImage(imagePath);
    if (!img.data) {
        return 1;
    }
    
    // Convert to grayscale
    vector<unsigned char>* grayData = new vector<unsigned char>();
    convertToGrayscale(img, *grayData);
    
    // Convert to binary (black and white) for QR code detection
    vector<unsigned char> binaryData;
    convertToBinary(*grayData, img.width, img.height, binaryData, 128);
    
    // Free the original image - we don't need it anymore!
    stbi_image_free(img.data);
    
    // Save the binary image
    string outputPath = "output_binary.png";
    bool success = saveGrayscaleImage(binaryData, img.width, img.height, outputPath.c_str());
    
    if (!success) {
        return 1;
    }
    
    // Now you can use binaryData for QR code detection
    // Access pixel at (x, y): binaryData[y * width + x]
    // 0 = black, 255 = white
    
    cout << "Binary data ready for QR code detection" << endl;
    
    return 0;
}