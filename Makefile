# Makefile pour QR Code Scanner

# Compilateurs
CXX = g++
CC = gcc

# Flags de compilation
# -I. indique au compilateur de chercher les headers dans le dossier courant
CXXFLAGS = -std=c++11 -Wall -I.
CFLAGS = -Wall -I.

# Nom de l'exécutable
TARGET = qrcode_scanner

# Fichiers sources
CPP_SOURCES = main.cpp image_utils.cpp
C_SOURCES = quirc.c decode.c identify.c version_db.c

# Fichiers objets
OBJECTS = $(CPP_SOURCES:.cpp=.o) $(C_SOURCES:.c=.o)

# Règle par défaut
all: $(TARGET)

# Compilation de l'exécutable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Règle de compilation pour les fichiers C++
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Règle de compilation pour les fichiers C
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour tester avec l'image par défaut
test: $(TARGET)
	@if [ -f Qrcode/qrcode.png ]; then \
		./$(TARGET) Qrcode/qrcode.png; \
	else \
		echo "Image de test non trouvée: Qrcode/qrcode.png"; \
	fi

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(TARGET) $(OBJECTS)

# Règle pour forcer la recompilation
rebuild: clean all

.PHONY: all clean rebuild test