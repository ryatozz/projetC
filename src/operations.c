#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/db.h"
#include "../include/tree.h"

void ajouter_entree(const char *table_name, const char *key, const char *value) {
    db_table *table = db_get_table(table_name); 
    if (table == NULL) {
        printf("Table '%s' non trouvée.\n", table_name);
        return;
    }

    db_entry entry;  
    entry.key = strdup(key);
    entry.value = strdup(value);

    if (db_insert_into(table_name, key, value)) { 
        printf("Entrée (clé : %s, valeur : %s) ajoutée avec succès dans la table '%s'.\n", key, value, table_name);
    } else {
        printf("Échec de l'ajout de l'entrée (clé : %s, valeur : %s) dans la table '%s'.\n", key, value, table_name);
    }

    free(entry.key);  
    free(entry.value);
}

void modifier_entree(const char *table, const char *old_key, const char *new_key) {
    db_update_key(table, old_key, new_key);
    printf("Clé '%s' modifiée avec succès dans la table '%s'. Nouvelle clé : %s\n", old_key, table, new_key);
}

void supprimer_entree(const char *table, const char *key) {
    db_delete_from(table, key);
    printf("Entrée avec clé '%s' supprimée de la table '%s'.\n", key, table);
}

void afficher_entree(const char *table) {
    db_table *table_ptr = db_get_table(table);
    if (table_ptr == NULL) {
        printf("Aucune entrée trouvée pour la table : %s\n", table);
        return;
    }

    printf("Entrées pour la table '%s':\n", table);
    tree_print_in_order(table_ptr->tree_root);
}

void afficher_tables() {
    if (num_tables == 0) {
        printf("Aucune table disponible.\n");
    } else {
        printf("Tables disponibles :\n");
        for (int i = 0; i < num_tables; i++) {
            printf("- %s\n", tables[i].name);
        }
    }
}
