#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/tree.h"

tree_node *tree_root = NULL; 


void tree_init() {
    tree_root = NULL;
}

void tree_insert(db_entry *entry) {
    tree_node *node = malloc(sizeof(tree_node));
    node->entry = entry;
    node->gauche = NULL;
    node->droite = NULL;

    if (tree_root == NULL) {
        tree_root = node;
    } else {
        tree_insert_node(tree_root, node);
    }
}

void tree_insert_node(tree_node *node, tree_node *new_node) {
    if (strcmp(new_node->entry->clé, node->entry->clé) < 0) {
        if (node->gauche == NULL) {
            node->gauche = new_node;
        } else {
            tree_insert_node(node->gauche, new_node);
        }
    } else {
        if (node->droite == NULL) {
            node->droite = new_node;
        } else {
            tree_insert_node(node->droite, new_node);
        }
    }
}

db_entry *tree_search(char *clé) {
    return tree_search_node(tree_root, clé);
}

db_entry *tree_search_node(tree_node *node, char *clé) {
    if (node == NULL) {
        return NULL;
    } else if (strcmp(clé, node->entry->clé) == 0) {
        return node->entry;
    } else if (strcmp(clé, node->entry->clé) < 0) {
        return tree_search_node(node->gauche, clé);
    } else {
        return tree_search_node(node->droite, clé);
    }
}

void tree_free() {
    tree_free_node(tree_root); 
    tree_root = NULL;           
}

void tree_free_node(tree_node *node) {
    if (node != NULL) {
        if (node->gauche != NULL) {
            tree_free_node(node->gauche);
        }
        if (node->droite != NULL) {
            tree_free_node(node->droite);
        }
        free(node->entry->clé);
        free(node->entry->valeur);
        free(node->entry);
        free(node);
    }
}

void tree_delete(char *clé) {
    tree_root = tree_delete_node(tree_root, clé);
}

tree_node *tree_delete_node(tree_node *node, char *clé) {
    if (node == NULL) {
        return NULL; 
    }

    if (strcmp(clé, node->entry->clé) < 0) {
        node->gauche = tree_delete_node(node->gauche, clé);
    } else if (strcmp(clé, node->entry->clé) > 0) {
        node->droite = tree_delete_node(node->droite, clé);
    } else {

        if (node->gauche == NULL) {
            tree_node *temp = node->droite;
            free(node->entry->clé);
            free(node->entry->valeur);
            free(node->entry);
            free(node);
            return temp;
        } else if (node->droite == NULL) {
            tree_node *temp = node->gauche;
            free(node->entry->clé);
            free(node->entry->valeur);
            free(node->entry);
            free(node);
            return temp;
        }

        tree_node *successeur = node->droite;
        while (successeur && successeur->gauche != NULL) {
            successeur = successeur->gauche;
        }

        free(node->entry->clé);
        free(node->entry->valeur);
        node->entry->clé = strdup(successeur->entry->clé);
        node->entry->valeur = strdup(successeur->entry->valeur);
        node->droite = tree_delete_node(node->droite, successeur->entry->clé);
    }

    return node;
}

void tree_save_in_order(tree_node *node, FILE *file) {
    if (node == NULL) {
        return;
    }

    tree_save_in_order(node->gauche, file);  
    fprintf(file, "%s,%s\n", node->entry->clé, node->entry->valeur);  
    tree_save_in_order(node->droite, file); 
}



void tree_load_entry(char *line) {
    char *clé = strtok(line, "=");
    char *valeur = strtok(NULL, "\n");
    if (clé != NULL && valeur != NULL) {
        db_entry *entry = malloc(sizeof(db_entry));
        entry->clé = strdup(clé);
        entry->valeur = strdup(valeur);
        tree_insert(entry);  
        db_save_to_disk("database.txt");
    }
}

void tree_print_in_order(tree_node *node) {
    if (node == NULL) {
        return;
    }

    tree_print_in_order(node->gauche);  
    printf("Clé: %s, Valeur: %s\n", node->entry->clé, node->entry->valeur);
    tree_print_in_order(node->droite); 
}
