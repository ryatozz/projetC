#ifndef TREE_H
#define TREE_H
#include "db_entry.h"

typedef struct tree_node {
    struct tree_node *left;
    struct tree_node *right;
    db_entry *entry;
} tree_node;

extern tree_node *tree_root;

int cmp_db_entry(const db_entry *x, const db_entry *y); 
void tree_insert(tree_node **root, db_entry *entry);
void tree_delete(tree_node **root, const char *key);
void tree_print_in_order(tree_node *node); 
void tree_free(tree_node *root);
void tree_save_in_order(tree_node *node, FILE *file);
void tree_load_entry(char *line);

db_entry* tree_search_node(tree_node *node, const char *key);
void tree_free_node(tree_node *node);
tree_node* tree_delete_node(tree_node *node, const char *key);

#endif
