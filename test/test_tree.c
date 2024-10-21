#include <stdio.h>
#include <assert.h>
#include "../include/tree.h"

int main() {
    // Initialisation de l'arbre binaire
    tree_init();

    // Insertion de quelques entrées
    db_entry *entry1 = malloc(sizeof(db_entry));
    entry1->clé = "clé1";
    entry1->valeur = "valeur1";
    tree_insert(entry1);

    db_entry *entry2 = malloc(sizeof(db_entry));
    entry2->clé = "clé2";
    entry2->valeur = "valeur2";
    tree_insert(entry2);

    db_entry *entry3 = malloc(sizeof(db_entry));
    entry3->clé = "clé3";
    entry3->valeur = "valeur3";
    tree_insert(entry3);

    // Recherche de quelques entrées
    db_entry *entry = tree_search("clé1");
    assert(strcmp(entry->clé, "clé1") == 0);
    assert(strcmp(entry->valeur, "valeur1") == 0);

    entry = tree_search("clé2");
    assert(strcmp(entry->clé, "clé2") == 0);
    assert(strcmp(entry->valeur, "valeur2") == 0);

    entry = tree_search("clé3");
    assert(strcmp(entry->clé, "clé3") == 0);
    assert(strcmp(entry->valeur, "valeur3") == 0);

    // Libération de la mémoire allouée pour l'arbre binaire
    tree_free();

    return 0;
}