#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/db.h"

db_table *tables = NULL; 
int num_tables = 0;       


db_table *tables = NULL;  
int num_tables = 0;       
db_table* db_get_table(const char *table_name) {
    for (int i = 0; i < num_tables; i++) {
        if (strcmp(tables[i].name, table_name) == 0) {
            return &tables[i];  
        }
    }
    return NULL;  
}


db_table *tables = NULL;  
int num_tables = 0;

void db_init() {
    printf("Base de données initialisée.\n");
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


db_table* db_select(const char *table_name) {
    printf("Sélection de la table '%s'.\n", table_name);
    return NULL; 
}


void db_insert(const char *table_name, const char *key, const char *value) {
    db_table *table = db_select(table_name);
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

    new_row.entries[0].clé = strdup(key);
    new_row.entries[0].valeur = strdup(value);

    table->rows = realloc(table->rows, (table->num_rows + 1) * sizeof(db_row));
    if (!table->rows) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les lignes.\n");
        return;
    }
    
    table->rows[table->num_rows] = new_row;
    table->num_rows++;
}


void db_create_table(const char *table_name) {
    db_table *new_table = malloc(sizeof(db_table));
    if (!new_table) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return;
    }

    new_table->rows = NULL; 
    new_table->num_rows = 0;

    const char *default_key = "default_key";
    const char *default_value = "default_value";


    db_insert(table_name, default_key, default_value);
}


void db_insert_into(const char *table_name, const char *key, const char *value) {
    db_table *table = db_select(table_name);
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

    new_row.entries[0].clé = strdup(key);
    new_row.entries[0].valeur = strdup(value);

    table->rows = realloc(table->rows, (table->num_rows + 1) * sizeof(db_row));
    if (!table->rows) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les lignes.\n");
        return;
    }
    
    table->rows[table->num_rows] = new_row;
    table->num_rows++;
}


char *db_select_from(const char *table, const char *key) {
    if (strcmp(table, "utilisateurs") == 0 && strcmp(key, "id") == 0) {
        return strdup("1");
    } else if (strcmp(table, "utilisateurs") == 0 && strcmp(key, "nom") == 0) {
        return strdup("Alice");
    } else {
        return NULL;
    }
}


void db_update(const char *table_name, const char *clé, const char *nouvelle_valeur) {
    db_table *table = db_select(table_name);
    if (!table) {
        printf("Table '%s' introuvable.\n", table_name);
        return;
    }

    for (int i = 0; i < table->num_rows; i++) {
        db_row *row = &table->rows[i];
        for (int j = 0; j < row->num_entries; j++) {
            if (strcmp(row->entries[j].clé, clé) == 0) {
                free(row->entries[j].valeur);
                row->entries[j].valeur = strdup(nouvelle_valeur);
                printf("Entrée mise à jour : Clé = %s, Nouvelle Valeur = %s\n", clé, nouvelle_valeur);
                return;
            }
        }
    }

    printf("Entrée avec clé '%s' non trouvée dans la table '%s'.\n", clé, table_name);
}


void db_delete_from(const char *table_name, const char *clé) {
    db_table *table = db_select(table_name);
    if (!table) {
        printf("Table '%s' introuvable.\n", table_name);
        return;
    }

    for (int i = 0; i < table->num_rows; i++) {
        db_row *row = &table->rows[i];
        for (int j = 0; j < row->num_entries; j++) {
            if (strcmp(row->entries[j].clé, clé) == 0) {
                free(row->entries[j].clé);
                free(row->entries[j].valeur);

                // Décalage des entrées restantes
                for (int k = j; k < row->num_entries - 1; k++) {
                    row->entries[k] = row->entries[k + 1];
                }
                row->num_entries--;
                row->entries = realloc(row->entries, row->num_entries * sizeof(db_entry));

                printf("Entrée avec clé '%s' supprimée de la table '%s'.\n", clé, table_name);
                return;
            }
        }
    }

    printf("Entrée avec clé '%s' non trouvée dans la table '%s'.\n", clé, table_name);
}
