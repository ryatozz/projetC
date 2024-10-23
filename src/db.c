#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/db.h"
#include "../include/tree.h"

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

    db_row new_row;
    new_row.num_entries = 1;
    new_row.entries = malloc(sizeof(db_entry));

    if (!new_row.entries) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les entrées.\n");
        return;
    }

    strcpy(new_row.entries[0].key, key);
    strcpy(new_row.entries[0].value, value);

    table->rows = realloc(table->rows, (table->num_rows + 1) * sizeof(db_row));
    if (!table->rows) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les lignes.\n");
        free(new_row.entries);
        return;
    }

    table->rows[table->num_rows] = new_row;
    table->num_rows++;
}

void db_create_table(const char *table_name) {
    tables = realloc(tables, (num_tables + 1) * sizeof(db_table));
    if (tables == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les tables.\n");
        return;
    }

    strncpy(tables[num_tables].name, table_name, 100);
    tables[num_tables].rows = NULL;
    tables[num_tables].num_rows = 0;
    num_tables++;
}

void db_update(const char *table_name, const char *key, const char *new_value) {
    db_table *table = db_get_table(table_name);
    if (table == NULL) {
        printf("Table '%s' introuvable.\n", table_name);
        return;
    }

    for (int i = 0; i < table->num_rows; i++) {
        for (int j = 0; j < table->rows[i].num_entries; j++) {
            if (strcmp(table->rows[i].entries[j].key, key) == 0) {
            strcpy(table->rows[i].entries[j].value, new_value);
            }
        }
    }
    printf("Clé '%s' non trouvée dans la table '%s'.\n", key, table_name);
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
        perror("Erreur d'ouverture du fichier");
        return;
    }
    
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        tree_load_entry(line);
    }
    
    fclose(file);
}

void sauvegarder_en_txt(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Erreur d'ouverture du fichier");
        return;
    }
    
    tree_save_in_order(tree_root, file);
    
    fclose(file);
}

void db_close() {
    printf("Base de données fermée.\n");
}
