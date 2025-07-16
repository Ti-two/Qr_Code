# Makefile simple pour QR Code Scanner

# Compilateur
CXX = g++

# Flags de compilation
CXXFLAGS = -std=c++11 -Wall

# Nom de l'exécutable
TARGET = qrcode_scanner

# Fichiers sources
SOURCES = main.cpp image_utils.cpp

# Chemin vers l'image de test
QRCODE_DIR = Qrcode
TEST_IMAGE = $(QRCODE_DIR)/qrcode.png

# Règle par défaut
all: $(TARGET)

# Compilation de l'exécutable
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Règle pour tester avec l'image par défaut
test: $(TARGET)
	@if [ -f $(TEST_IMAGE) ]; then \
		./$(TARGET) $(TEST_IMAGE); \
	else \
		echo "Image de test non trouvée: $(TEST_IMAGE)"; \
		echo "Placez une image QR code dans le dossier $(QRCODE_DIR)/"; \
	fi

# Règle pour lister les images disponibles
list-images:
	@echo "Images disponibles dans $(QRCODE_DIR):"
	@ls -la $(QRCODE_DIR)/ 2>/dev/null || echo "Dossier $(QRCODE_DIR) non trouvé"

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(TARGET)

# Règle pour forcer la recompilation
rebuild: clean all

.PHONY: all clean rebuild test list-images