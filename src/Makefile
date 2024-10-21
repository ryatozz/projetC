CC = gcc
CFLAGS = -Wall -Werror -I./include
SOURCES = main.c db.c tree.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = db

# Règle par défaut
all: $(EXECUTABLE)
	@echo "Création de l'exécutable : $(EXECUTABLE)"

# Règle pour créer l'exécutable
$(EXECUTABLE): $(OBJECTS)
	@echo "Liage de $^"
	$(CC) -o $@ $^

# Règles pour compiler les fichiers .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
