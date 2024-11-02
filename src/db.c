#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/db.h"
#include "../include/tree.h"

database db;

db_table *tables = NULL;
int num_tables = 0;

void db_init() {
    printf("Base de données initialisée.\n");
}

db_row* db_select_all(const char *table_name) {
    db_table *table = db_get_table(table_name);
    if (table == NULL) {
        printf("Table '%s' introuvable.\n", table_name);
        return NULL; 
    }

    return table->rows; 
}





db_table* db_get_table(const char *table_name) {
    for (int i = 0; i < num_tables; i++) {
        if (strcmp(tables[i].name, table_name) == 0) {
            return &tables[i];
        }
    }
    return NULL;
}


void db_insert_into(const char *table_name, const char *key, const char *value) {
    db_table *table = db_get_table(table_name);
    if (table == NULL) {
        printf("Table '%s' introuvable.\n", table_name);
        return;
    }


    for (int i = 0; i < table->num_rows; i++) {
        for (int j = 0; j < table->rows[i].num_entries; j++) {
            if (strcmp(table->rows[i].entries[j].key, key) == 0) {
                printf("La clé '%s' existe déjà dans la table '%s'.\n", key, table_name);
                return;  
            }
        }
    }


    db_row new_row;
    new_row.num_entries = 1;
    new_row.entries = malloc(sizeof(db_entry));

    if (!new_row.entries) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les entrées.\n");
        return;
    }

    new_row.entries[0].key = strdup(key); 
    new_row.entries[0].value = strdup(value);


    table->rows = realloc(table->rows, (table->num_rows + 1) * sizeof(db_row));
    if (!table->rows) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les lignes.\n");
        free(new_row.entries[0].key);
        free(new_row.entries[0].value);
        free(new_row.entries);
        return;
    }

    table->rows[table->num_rows] = new_row;
    table->num_rows++;
}









db_table* db_create_table(const char *table_name) {

    for (int i = 0; i < num_tables; i++) {
        if (strcmp(tables[i].name, table_name) == 0) {
            printf("La table '%s' existe déjà.\n", table_name);
            return NULL;  
        }
    }
    

    db_table new_table;
    strcpy(new_table.name, table_name);
    new_table.rows = NULL;
    new_table.num_rows = 0;


    tables = realloc(tables, (num_tables + 1) * sizeof(db_table));
    tables[num_tables] = new_table;
    num_tables++;
    return &tables[num_tables - 1];  
}


void db_update(const char *table_name, const char *key, const char *new_value) {
    db_table *table = db_get_table(table_name);
    if (table == NULL) {
        printf("Table '%s' introuvable.\n", table_name);
        return;
    }

    int found = 0;  
    for (int i = 0; i < table->num_rows; i++) {
        for (int j = 0; j < table->rows[i].num_entries; j++) {
            if (strcmp(table->rows[i].entries[j].key, key) == 0) {
                found = 1;  
                free(table->rows[i].entries[j].value);  
                table->rows[i].entries[j].value = strdup(new_value); 
                printf("La valeur de la clé '%s' a été mise à jour.\n", key);
                return; 
            }
        }
    }

    if (!found) {
        printf("Clé '%s' introuvable dans la table '%s'.\n", key, table_name);
    }
}








void db_delete_from(const char *table_name, const char *key) {
    db_table *table = db_get_table(table_name);
    if (table == NULL) {
        printf("Table '%s' introuvable.\n", table_name);
        return;
    }

    for (int i = 0; i < table->num_rows; i++) {
        for (int j = 0; j < table->rows[i].num_entries; j++) {
            if (strcmp(table->rows[i].entries[j].key, key) == 0) {
            free(table->rows[i].entries[j].key);
            free(table->rows[i].entries[j].value);

                for (int k = j; k < table->rows[i].num_entries - 1; k++) {
                    table->rows[i].entries[k] = table->rows[i].entries[k + 1];
                }

                table->rows[i].num_entries--;
                return;
            }
        }
    }
    printf("Clé '%s' non trouvée dans la table '%s'.\n", key, table_name);
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

        if (strncmp(line, "TABLE", 5) == 0) {
            char table_name[50];
            sscanf(line, "TABLE %s", table_name);
            current_table = db_create_table(table_name); 
        } else if (strncmp(line, "INSERT INTO", 11) == 0 && current_table != NULL) {
            char table_name[50], key[50], value[50];
            sscanf(line, "INSERT INTO %s (%49[^,], %49[^)])", table_name, key, value);
            db_insert_into(table_name, key, value);  
        }
    }

    fclose(file);
    printf("La base de données a été chargée avec succès.\n");
}




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





void db_close() {
    printf("Base de données fermée.\n");
}
