CC = gcc
CFLAGS = -Wall -Werror -I./include
SOURCES = main.c db.c tree.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = db

all: $(EXECUTABLE)
	@echo "Création de l'exécutable : $(EXECUTABLE)"

$(EXECUTABLE): $(OBJECTS)
	@echo "Liage de $^"
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)