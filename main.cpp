#include <iostream>
#include <string>
#include <vector>
#include <cstring> // Pour memcpy
#include "image_utils.h"
#include "quirc.h"

using namespace std;

void decode_qr(const vector<unsigned char>& binaryData, int width, int height);

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
    
    // Convert to grayscale (correction: pas de 'new' ici)
    vector<unsigned char> grayData;
    convertToGrayscale(img, grayData);
    
    // Convert to binary (black and white) for QR code detection
    vector<unsigned char> binaryData;
    convertToBinary(grayData, img.width, img.height, binaryData, 128);
    
    // Free the original image - we don't need it anymore!
    stbi_image_free(img.data);
    
    // Save the binary image
    string outputPath = "output_binary.png";
    if (!saveGrayscaleImage(binaryData, img.width, img.height, outputPath.c_str())) {
        return 1;
    }
    
    cout << "\n--- Starting QR Code Detection ---" << endl;
    decode_qr(binaryData, img.width, img.height);
    
    return 0;
}

void decode_qr(const vector<unsigned char>& binaryData, int width, int height) {
    // 1. Initialiser Quirc
    struct quirc *qr = quirc_new();
    if (!qr) {
        cerr << "Error: Failed to allocate quirc struct." << endl;
        return;
    }

    // 2. Préparer Quirc pour la taille de l'image
    if (quirc_resize(qr, width, height) < 0) {
        cerr << "Error: Failed to resize quirc struct." << endl;
        quirc_destroy(qr);
        return;
    }

    // 3. Charger les données de l'image dans Quirc
    unsigned char *image_buffer = quirc_begin(qr, NULL, NULL);
    memcpy(image_buffer, binaryData.data(), width * height);
    quirc_end(qr);

    // 4. Compter les QR codes détectés
    int count = quirc_count(qr);
    if (count == 0) {
        cout << "No QR codes detected." << endl;
        quirc_destroy(qr);
        return;
    }
    cout << count << " QR code(s) found." << endl;

    // 5. Extraire et décoder chaque QR code
    for (int i = 0; i < count; i++) {
        struct quirc_code code;
        struct quirc_data data;

        quirc_extract(qr, i, &code);
        
        quirc_decode_error_t err = quirc_decode(&code, &data);
        if (err) {
            cerr << "QR Code #" << i << " - DECODE FAILED: " << quirc_strerror(err) << endl;
        } else {
            cout << "----------------------------------------" << endl;
            cout << "QR Code #" << i << " - DECODED SUCCESSFULLY" << endl;
            cout << "Payload: " << data.payload << endl;
            cout << "----------------------------------------" << endl;
        }
    }

    // 6. Libérer la mémoire de Quirc
    quirc_destroy(qr);
}