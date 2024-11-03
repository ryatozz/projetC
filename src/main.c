#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/db.h"
#include "../include/commands.h"
#include "../include/saveload.h"

int main() {
    db_init(); 
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
    printf("- DROP TABLE table_name pour supprimer une table\n");
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
