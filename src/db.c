#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/db.h"

db_table *tables = NULL;  
int num_tables = 0;

void db_init() {
    printf("Base de données initialisée.\n");
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

    db_row new_row;
    new_row.num_entries = 1;
    new_row.entries = malloc(sizeof(db_entry));

    if (!new_row.entries) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les entrées.\n");
        return;
    }

    strncpy(new_row.entries[0].clé, key, 100); 
    strncpy(new_row.entries[0].valeur, value, 100);

    table->rows = realloc(table->rows, (table->num_rows + 1) * sizeof(db_row));
    if (!table->rows) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les lignes.\n");
        free(new_row.entries); 
        return;
    }

    table->rows[table->num_rows] = new_row;
    table->num_rows++;
}

void db_save_to_disk() {
    printf("Base de données sauvegardée sur le disque.\n");
}

void db_load_from_disk() {
    printf("Base de données chargée depuis le disque.\n");
}

void db_close() {
    printf("Base de données fermée.\n");
}
