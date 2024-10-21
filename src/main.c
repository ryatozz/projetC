#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/db.h"


void ajouter_entree();
void modifier_entree();
void supprimer_entree();
void afficher_entree();
void initialiser_db();
db_row* db_select_all(const char *table_name); 
db_table* db_get_table(const char *table_name);

extern db_table *tables;  
extern int num_tables;    
int main() {
    db_init(); 

    initialiser_db();

    int choix;
    do {
        printf("\nMenu:\n");
        printf("1. Ajouter une entrée\n");
        printf("2. Modifier une entrée\n");
        printf("3. Supprimer une entrée\n");
        printf("4. Afficher une entrée\n");
        printf("5. Sauvegarder sur disque\n");
        printf("6. Charger depuis disque\n");
        printf("7. Quitter\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choix);
        getchar(); 

        switch (choix) {
            case 1:
                ajouter_entree();
                break;
            case 2:
                modifier_entree();
                break;
            case 3:
                supprimer_entree();
                break;
            case 4:
                afficher_entree();
                break;
            case 5:
                db_save_to_disk();
                printf("Base de données sauvegardée.\n");
                break;
            case 6:
                db_load_from_disk();
                printf("Base de données chargée.\n");
                break;
            case 7:
                printf("Fermeture de la base de données.\n");
                db_close();
                break;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
    } while (choix != 7);

    db_close(); 
    return 0;
}

void initialiser_db() {
    char table[100];
    printf("Entrez le nom de la table à créer : ");
    fgets(table, sizeof(table), stdin);
    table[strcspn(table, "\n")] = 0;

    db_create_table(table);
    printf("Table '%s' créée avec succès.\n", table);
}

void ajouter_entree() {
    char table[100];
    char clé[100];
    char valeur[100];

    printf("Entrez le nom de la table: ");
    fgets(table, sizeof(table), stdin);
    table[strcspn(table, "\n")] = 0;

    printf("Entrez la clé: ");
    fgets(clé, sizeof(clé), stdin);
    clé[strcspn(clé, "\n")] = 0;

    printf("Entrez la valeur: ");
    fgets(valeur, sizeof(valeur), stdin);
    valeur[strcspn(valeur, "\n")] = 0;

    db_insert_into(table, clé, valeur);
    printf("Entrée ajoutée avec succès.\n");
}

void modifier_entree() {
    char table[100];
    char clé[100];
    char nouvelle_valeur[100];

    printf("Entrez le nom de la table: ");
    fgets(table, sizeof(table), stdin);
    table[strcspn(table, "\n")] = 0;

    printf("Entrez la clé à modifier: ");
    fgets(clé, sizeof(clé), stdin);
    clé[strcspn(clé, "\n")] = 0;

    printf("Entrez la nouvelle valeur: ");
    fgets(nouvelle_valeur, sizeof(nouvelle_valeur), stdin);
    nouvelle_valeur[strcspn(nouvelle_valeur, "\n")] = 0;

    db_update(table, clé, nouvelle_valeur);
    printf("Entrée modifiée avec succès.\n");
}

void supprimer_entree() {
    char table[100];
    char clé[100];

    printf("Entrez le nom de la table: ");
    fgets(table, sizeof(table), stdin);
    table[strcspn(table, "\n")] = 0;

    printf("Entrez la clé à supprimer: ");
    fgets(clé, sizeof(clé), stdin);
    clé[strcspn(clé, "\n")] = 0;

    db_delete_from(table, clé);
    printf("Entrée supprimée avec succès.\n");
}


void afficher_entree() {
    char table[100];

    printf("Entrez le nom de la table: ");
    fgets(table, sizeof(table), stdin);
    table[strcspn(table, "\n")] = 0;

    db_row *rows = db_select_all(table); 
    if (rows == NULL) {
        printf("Aucune entrée trouvée pour la table : %s\n", table);
        return;
    }

    for (int i = 0; i < rows->num_entries; i++) {
        printf("Clé : %s, Valeur : %s\n", rows->entries[i].clé, rows->entries[i].valeur);
    }

    free(rows->entries);
    free(rows);
}




db_row* db_select_all(const char *table_name) {
    db_table *table = db_get_table(table_name);
    if (table == NULL) {
        printf("Table '%s' introuvable.\n", table_name);
        return NULL;
    }

    db_row *result = malloc(sizeof(db_row));
    if (result == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire.\n");
        return NULL;
    }

    result->entries = malloc(table->num_rows * sizeof(db_entry));
    if (result->entries == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les entrées.\n");
        free(result);
        return NULL;
    }

    for (int i = 0; i < table->num_rows; i++) {
        result->entries[i] = table->rows[i].entries[0];  
    }

    result->num_entries = table->num_rows; 
    return result;
}




db_table* db_get_table(const char *table_name) {
    for (int i = 0; i < num_tables; i++) {
        if (strcmp(tables[i].name, table_name) == 0) {
            return &tables[i];
        }
    }

    return NULL;
}
