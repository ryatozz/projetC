#ifndef TREE_H
#define TREE_H

#include "db.h"

typedef struct tree_node {
    db_entry *entry;
    struct tree_node *gauche;
    struct tree_node *droite;
} tree_node;

extern tree_node *tree_root;

void tree_insert(db_entry *entry);
db_entry *tree_search(char *clé);
void tree_init();
void tree_insert_node(tree_node *node, tree_node *new_node);


tree_node *tree_delete_node(tree_node *node, char *clé);


db_entry *tree_search_node(tree_node *node, char *clé);
void tree_free();
void tree_free_node(tree_node *node);

void tree_print_in_order(tree_node *node); 
void tree_delete(char *clé);

#endif
