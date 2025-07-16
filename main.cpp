#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <qrcode_image_path>" << std::endl;
        return 1;
    }

    // Chemin vers l'image QR code
    const char* imagePath = argv[1];
    
    int width, height, channels;
    
    // Charger l'image QR code
    unsigned char* imageData = stbi_load(imagePath, &width, &height, &channels, 0);
    
    if (!imageData) {
        std::cerr << "Erreur: Impossible de charger l'image " << imagePath << std::endl;
        std::cerr << "Raison: " << stbi_failure_reason() << std::endl;
        return 1;
    }
    
    std::cout << "Image QR code chargée avec succès:" << std::endl;
    std::cout << "- Dimensions: " << width << "x" << height << " pixels" << std::endl;
    std::cout << "- Canaux couleur: " << channels << std::endl;
    
    // Les données de l'image sont maintenant dans imageData
    // Chaque pixel occupe 'channels' octets
    // Pour traitement ultérieur du QR code...
    
    // Exemple: convertir en niveaux de gris si nécessaire
    if (channels > 1) {
        std::cout << "Image en couleur détectée, conversion possible en niveaux de gris" << std::endl;
    }
    
    // Libérer la mémoire
    stbi_image_free(imageData);
    
    return 0;
}