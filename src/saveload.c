#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/db.h"
#include "../include/operations.h"

extern int num_tables;
extern db_table *tables;

void sauvegarder_en_txt(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier %s en écriture.\n", filename);
        return;
    }

    for (int i = 0; i < num_tables; i++) {
        fprintf(file, "CREATE TABLE %s;\n", tables[i].name);
        for (int j = 0; j < tables[i].num_rows; j++) {
            for (int k = 0; k < tables[i].rows[j].num_entries; k++) {
                fprintf(file, "INSERT INTO %s (%s, %s);\n", tables[i].name, 
                        tables[i].rows[j].entries[k].key, 
                        tables[i].rows[j].entries[k].value);
            }
        }
    }

    fclose(file);
    printf("Base de données sauvegardée dans %s.\n", filename);
}

void charger_depuis_txt(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier %s en lecture.\n", filename);
        return;
    }

    char command[200];
    char table_name[100], key[100], value[100];
    db_table *current_table = NULL;

    while (fgets(command, sizeof(command), file) != NULL) {
        if (sscanf(command, "CREATE TABLE %s", table_name) == 1) {

            char *semicolon = strchr(table_name, ';');
            if (semicolon) {
                *semicolon = '\0';
            }
            current_table = db_create_table(table_name); 
        }
        else if (sscanf(command, "INSERT INTO %s (%[^,], %[^)])", table_name, key, value) == 3) {
            if (current_table != NULL) {
                db_insert_into(current_table->name, key, value);
            }
        }
    }

    fclose(file);
    printf("Base de données chargée depuis %s.\n", filename);
}
