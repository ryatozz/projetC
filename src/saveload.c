#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/db.h"

void sauvegarder_en_txt(const char *filename) {
    FILE *file = fopen(filename, "w"); 
    if (file == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier pour sauvegarde.\n");
        return;
    }

    for (int i = 0; i < num_tables; i++) {
        fprintf(file, "TABLE %s\n", tables[i].name);
        
        for (int j = 0; j < tables[i].num_rows; j++) {
            for (int k = 0; k < tables[i].rows[j].num_entries; k++) {
                fprintf(file, "INSERT INTO %s (%s, %s)\n",
                        tables[i].name,
                        tables[i].rows[j].entries[k].key,
                        tables[i].rows[j].entries[k].value);
            }
        }
    }

    fclose(file);
    printf("La base de données a été sauvegardée avec succès.\n");
}


void charger_depuis_txt(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier pour chargement.\n");
        return;
    }

    char line[256];
    db_table *current_table = NULL;


    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; 
        printf("Ligne lue : %s\n", line);

        if (strncmp(line, "TABLE", 5) == 0) {
            char table_name[50];
            sscanf(line, "TABLE %s", table_name);
            printf("Création de la table : %s\n", table_name);
            
            current_table = db_create_table(table_name);
            if (current_table == NULL) {
                fprintf(stderr, "Erreur lors de la création de la table %s.\n", table_name);
            }

        } else if (strncmp(line, "INSERT INTO", 11) == 0) {
            if (current_table != NULL) {
                char table_name[50], key[50], value[50];
                sscanf(line, "INSERT INTO %s (%49[^,], %49[^)])", table_name, key, value);
                printf("Insertion dans la table %s : (%s, %s)\n", table_name, key, value);

                db_insert_into(table_name, key, value);
            } else {
                fprintf(stderr, "Erreur : aucune table n'est active pour insérer les données.\n");
            }
        }
    }

    fclose(file);
    printf("La base de données a été chargée avec succès.\n");
}
