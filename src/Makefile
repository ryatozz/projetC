CC = gcc
CFLAGS = -Wall -Werror -I./include

SOURCES = main.c db.c tree.c commands.c operations.c saveload.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = db

all: $(EXECUTABLE)
	@echo "Création de l'exécutable : $(EXECUTABLE)"
	@if [ -f database.txt ]; then chmod 644 database.txt; fi

$(EXECUTABLE): $(OBJECTS)
	@echo "Liage des objets pour créer $(EXECUTABLE)"
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean
