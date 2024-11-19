#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/db.h"
#include "../include/tree.h"
#include "../include/saveload.h"

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

int is_positive_integer(const char *str) {
    if (str == NULL || *str == '\0' || *str == '-') {
        return 0;
    }
    char *p;
    strtol(str, &p, 10);
    return *p == '\0';
}

int db_insert_into(const char *table_name, const char *key, const char *value) {
    if (!is_positive_integer(key) || strcmp(key, "0") == 0) {
        printf("Erreur : La clé '%s' doit être un entier positif non nul.\n", key);
        return 0;
    }

    db_table *table = db_get_table(table_name);
    if (table == NULL) {
        printf("Table '%s' introuvable.\n", table_name);
        return 0;
    }

    db_entry *existing_entry = tree_search(table->tree_root, key);
    if (existing_entry != NULL) {
        printf("Erreur : La clé '%s' existe déjà.\n", key);
        return 0;
    }

    db_entry *entry = malloc(sizeof(db_entry));
    entry->key = strdup(key);
    entry->value = strdup(value);

    tree_insert(&table->tree_root, entry); 
    insert_row(table, key, value); 
    return 1;
}



db_table* db_create_table(const char *table_name) {
    db_table *existing_table = db_get_table(table_name);
    if (existing_table != NULL) {
        printf("La table '%s' existe déjà.\n", table_name);
        return existing_table; 
    }

    db_table new_table;
    strcpy(new_table.name, table_name);
    new_table.rows = NULL;
    new_table.num_rows = 0;
    new_table.tree_root = NULL; 

    tables = realloc(tables, (num_tables + 1) * sizeof(db_table));
    if (!tables) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les tables.\n");
        return NULL;
    }
    tables[num_tables] = new_table;
    num_tables++;
    printf("Table '%s' créée avec succès.\n", table_name);
    return &tables[num_tables - 1];
}

void db_update_key(const char *table_name, const char *old_key, const char *new_key) {
    if (!is_positive_integer(new_key) || strcmp(new_key, "0") == 0) {
        printf("Erreur : La nouvelle clé '%s' doit être un entier positif non nul.\n", new_key);
        return;
    }

    db_table *table = db_get_table(table_name);
    if (table == NULL) {
        printf("Table '%s' introuvable.\n", table_name);
        return;
    }

    db_entry *entry = tree_search(table->tree_root, old_key); 
    if (entry != NULL) {
        free(entry->key);
        entry->key = strdup(new_key);
        printf("La clé '%s' a été mise à jour en '%s'.\n", old_key, new_key);
    } else {
        printf("Clé '%s' introuvable dans la table '%s'.\n", old_key, table_name);
    }
}




void insert_row(db_table *table, const char *key, const char *value) {
    table->rows = realloc(table->rows, (table->num_rows + 1) * sizeof(db_row));
    if (!table->rows) {
        perror("Erreur de réallocation de mémoire pour les lignes");
        exit(EXIT_FAILURE);
    }

    db_row *new_row = &table->rows[table->num_rows++];
    new_row->num_entries = 1;
    new_row->entries = malloc(sizeof(db_entry));
    if (!new_row->entries) {
        perror("Erreur d'allocation de mémoire pour les entrées de la ligne");
        exit(EXIT_FAILURE);
    }

    new_row->entries[0].key = strdup(key);
    new_row->entries[0].value = strdup(value); 
}

void db_delete_from(const char *table_name, const char *key) {
    db_table *table = db_get_table(table_name);
    if (table == NULL) {
        printf("Table '%s' introuvable.\n", table_name);
        return;
    }

    db_entry *entry = tree_search(table->tree_root, key); 
    if (entry != NULL) {

        tree_delete(&table->tree_root, key); 


        for (int i = 0; i < table->num_rows; i++) {
            if (strcmp(table->rows[i].entries[0].key, key) == 0) {

                free(table->rows[i].entries[0].key);
                free(table->rows[i].entries[0].value);
                free(table->rows[i].entries);


                for (int j = i; j < table->num_rows - 1; j++) {
                    table->rows[j] = table->rows[j + 1];
                }
                table->num_rows--;
                table->rows = realloc(table->rows, table->num_rows * sizeof(db_row));
                break;
            }
        }

        printf("Entrée avec clé '%s' supprimée de la table '%s'.\n", key, table_name);
    } else {
        printf("Clé '%s' non trouvée dans la table '%s'.\n", key, table_name);
    }
}


void drop_table(const char *table_name) {
    int table_index = -1;
    for (int i = 0; i < num_tables; i++) {
        if (strcmp(tables[i].name, table_name) == 0) {
            table_index = i;
            break;
        }
    }

    if (table_index == -1) {
        printf("Table '%s' introuvable.\n", table_name);
        return;
    }

    tree_free(tables[table_index].tree_root); 

    for (int i = table_index; i < num_tables - 1; i++) {
        tables[i] = tables[i + 1];
    }
    num_tables--;
    tables = realloc(tables, num_tables * sizeof(db_table)); 
    printf("Table '%s' supprimée.\n", table_name);
}

void db_close() {
    for (int i = 0; i < num_tables; i++) {
        tree_free(tables[i].tree_root);
        for (int j = 0; j < tables[i].num_rows; j++) {
            for (int k = 0; k < tables[i].rows[j].num_entries; k++) {
                free(tables[i].rows[j].entries[k].key);
                free(tables[i].rows[j].entries[k].value);
            }
            free(tables[i].rows[j].entries);
        }
        free(tables[i].rows);
    }
    free(tables);
    tables = NULL;
    num_tables = 0;
    printf("Base de données fermée.\n");
}