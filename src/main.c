#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/db.h"


void ajouter_entree(const char *table, const char *key, const char *value);
void modifier_entree(const char *table, const char *key, const char *new_value);
void supprimer_entree(const char *table, const char *key);
void afficher_entree(const char *table);
void afficher_tables();
void sauvegarder_en_txt(const char *fichier);
void charger_depuis_txt(const char *fichier);
void initialiser_db();
db_row* db_select_all(const char *table_name);


extern db_table *tables;
extern int num_tables;

void execute_command(const char *command);

int main() {
    db_init();  
    charger_depuis_txt("database.txt"); 

    printf("Bienvenue dans votre base de données personnalisée.\n");
    printf("Exemples de commandes :\n");
    printf("- CREATE TABLE table_name\n");
    printf("- INSERT INTO table_name (key, value)\n");
    printf("- DELETE FROM table_name WHERE key='your_key'\n");
    printf("- UPDATE table_name SET key='new_value' WHERE key='your_key'\n");
    printf("- SELECT * FROM table_name\n");
    printf("- SHOW pour afficher toutes les tables\n");
    printf("- SAVE pour sauvegarder la base de données\n");
    printf("- LOAD pour charger la base de données\n");
    printf("- EXIT pour quitter\n");

    char command[1024];
    while (1) {
        printf("\nEntrez votre commande: ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; 

        if (strcasecmp(command, "EXIT") == 0) {
            printf("Fermeture de la base de données.\n");
            sauvegarder_en_txt("database.txt"); 
            db_close();  
            break;
        }

        execute_command(command);
    }

    return 0;
}

void execute_command(const char *command) {
    char table[100], key[100], value[100], new_value[100];

    if (sscanf(command, "CREATE TABLE %s", table) == 1) {
        db_create_table(table);
        printf("Table '%s' créée avec succès.\n", table);
    }
    else if (sscanf(command, "INSERT INTO %s (%[^,], %[^)])", table, key, value) == 3) {

        ajouter_entree(table, key, value);
    }
    else if (sscanf(command, "DELETE FROM %s WHERE key='%[^']'", table, key) == 2) {
        supprimer_entree(table, key);
    }
    else if (sscanf(command, "UPDATE %s SET key='%[^']' WHERE key='%[^']'", table, new_value, key) == 3) {
        modifier_entree(table, key, new_value);
    }
    else if (sscanf(command, "SELECT * FROM %s", table) == 1) {
        afficher_entree(table);
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

void ajouter_entree(const char *table, const char *key, const char *value) {
    db_insert_into(table, key, value);
    printf("Entrée (clé : %s, valeur : %s) ajoutée avec succès dans la table '%s'.\n", key, value, table);
}

void modifier_entree(const char *table, const char *key, const char *new_value) {
    db_update(table, key, new_value);
    printf("Entrée avec clé '%s' modifiée avec succès dans la table '%s'. Nouvelle valeur : %s\n", key, table, new_value);
}

void supprimer_entree(const char *table, const char *key) {
    db_delete_from(table, key);
    printf("Entrée avec clé '%s' supprimée de la table '%s'.\n", key, table);
}

void afficher_entree(const char *table) {
    db_row *rows = db_select_all(table);
    if (rows == NULL) {
        printf("Aucune entrée trouvée pour la table : %s\n", table);
        return;
    }

    for (int i = 0; i < rows->num_entries; i++) {
        printf("Clé : %s, Valeur : %s\n", rows->entries[i].key, rows->entries[i].value);
    }

    free(rows->entries);
    free(rows);
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