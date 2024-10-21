#include <stdio.h>
#include <assert.h>
#include "../include/db.h"

int main() {
    // Initialisation de la base de données
    db_init();

    // Insertion de quelques entrées
    db_insert("clé1", "valeur1");
    db_insert("clé2", "valeur2");
    db_insert("clé3", "valeur3");

    // Sélection de quelques entrées
    char *valeur1 = db_select("clé1");
    assert(strcmp(valeur1, "valeur1") == 0);
    free(valeur1);

    char *valeur2 = db_select("clé2");
    assert(strcmp(valeur2, "valeur2") == 0);
    free(valeur2);

    char *valeur3 = db_select("clé3");
    assert(strcmp(valeur3, "valeur3") == 0);
    free(valeur3);

    // Fermeture de la base de données
    db_close();

    return 0;
}