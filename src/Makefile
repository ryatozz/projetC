# version compilateur  : gcc version 13.1.0 (debian 13.1.0-6)
CC = gcc


# Active les avertissements courants, traite les avertissements comme des erreurs, spécifie le répertoire contenant les fichiers d'en-tête personnalisés
CFLAGS = -Wall -Werror -I./include

# Liste des fichiers sources
SOURCES = main.c db.c tree.c commands.c operations.c saveload.c

# Génération auto de la liste des fichiers objets à partir des fichiers sources
OBJECTS = $(SOURCES:.c=.o)

# Nom de l'exécutable final
EXECUTABLE = db

# Cible par défaut : compilation de l'exécutable
all: $(EXECUTABLE)
	@echo "Création de l'exécutable : $(EXECUTABLE)"
	@if [ -f database.txt ]; then chmod 644 database.txt; fi

#Si le fichier "database.txt" existe, ajuste ses permissions à 644 (lecture/écriture pour le propriétaire, lecture pour les autres)

# Règle pour créer l'exécutable à partir des fichiers objets
$(EXECUTABLE): $(OBJECTS)
	@echo "Liage des objets pour créer $(EXECUTABLE)"
	$(CC) -o $@ $^

# Règle générique pour compiler un fichier source en fichier objet
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Cible pour nettoyer les fichiers générés (objets et exécutable)
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

# Spécifie que les cibles "all" et "clean" ne correspondent pas à des fichiers réels
.PHONY: all clean
