#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/db.h"
#include "../include/operations.h"
#include "../include/saveload.h"

void execute_command(const char *command) {
    char table[100], old_key[100], new_key[100], value[100];
    if (sscanf(command, "CREATE TABLE %s", table) == 1) {
        db_create_table(table);
        printf("Table '%s' créée avec succès.\n", table);
    }
    else if (sscanf(command, "INSERT INTO %s (%[^,], %[^)])", table, old_key, value) == 3) {
        ajouter_entree(table, old_key, value);
    }
    else if (sscanf(command, "DELETE FROM %s WHERE key='%[^']'", table, old_key) == 2) {
        supprimer_entree(table, old_key);
    }
    else if (sscanf(command, "UPDATE %s SET key='%[^']' WHERE key='%[^']'", table, new_key, old_key) == 3) {
        modifier_entree(table, old_key, new_key);
    }
    else if (sscanf(command, "SELECT * FROM %s", table) == 1) {
        afficher_entree(table);
    }
    else if (sscanf(command, "DROP TABLE %s", table) == 1) {
        drop_table(table);
    }
    else if (strcasecmp(command, "SHOW") == 0) {
        afficher_tables(); 
    }
    else if (strcasecmp(command, "SAVE") == 0) {
        sauvegarder_en_txt("database.txt"); 
    }
    else if (strcasecmp(command, "LOAD") == 0) {
        charger_depuis_txt("database.txt"); 
    }
    else {
        printf("Commande non reconnue. Veuillez réessayer.\n");
    }
}
