#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/tree.h"

tree_node *tree_root = NULL; 

void tree_insert(tree_node **root, db_entry *entry) {
    tree_node *node = malloc(sizeof(tree_node));
    node->entry = entry;
    node->left = NULL;
    node->right = NULL;

    if (*root == NULL) {
        *root = node;
    } else {
        tree_insert_node(*root, node);
    }
}

void tree_insert_node(tree_node *node, tree_node *new_node) {
    if (strcmp(new_node->entry->key, node->entry->key) < 0) {
        if (node->left == NULL) {
            node->left = new_node;
        } else {
            tree_insert_node(node->left, new_node);
        }
    } else {
        if (node->right == NULL) {
            node->right = new_node;
        } else {
            tree_insert_node(node->right, new_node);
        }
    }
}

db_entry *tree_search(tree_node *root, const char *key) {
    return tree_search_node(root, key);
}

db_entry *tree_search_node(tree_node *node, const char *key) {
    if (node == NULL) {
        return NULL;
    } else if (strcmp(key, node->entry->key) == 0) {
        return node->entry;
    } else if (strcmp(key, node->entry->key) < 0) {
        return tree_search_node(node->left, key);
    } else {
        return tree_search_node(node->right, key);
    }
}

void tree_free(tree_node *root) {
    tree_free_node(root); 
}

void tree_free_node(tree_node *node) {
    if (node != NULL) {
        if (node->left != NULL) {
            tree_free_node(node->left);
        }
        if (node->right != NULL) {
            tree_free_node(node->right);
        }
        free(node->entry->key);  
        free(node->entry->value); 
        free(node->entry);
        free(node);
    }
}

void tree_delete(tree_node **root, const char *key) {
    *root = tree_delete_node(*root, key);
}

tree_node *tree_delete_node(tree_node *node, const char *key) {
    if (node == NULL) {
        return NULL;  
    }

    if (strcmp(key, node->entry->key) < 0) {
        node->left = tree_delete_node(node->left, key);  
    } else if (strcmp(key, node->entry->key) > 0) {
        node->right = tree_delete_node(node->right, key);  
    } else {
        if (node->left == NULL) {
            tree_node *temp = node->right;
            free(node->entry->key); 
            free(node->entry->value); 
            free(node->entry);
            free(node);
            return temp; 
        } else if (node->right == NULL) {
            tree_node *temp = node->left;
            free(node->entry->key); 
            free(node->entry->value); 
            free(node->entry);
            free(node);
            return temp;
        }

        tree_node *successeur = node->right;
        while (successeur && successeur->left != NULL) {
            successeur = successeur->left;
        }

        free(node->entry->key);
        free(node->entry->value); 
        node->entry->key = strdup(successeur->entry->key); 
        node->entry->value = strdup(successeur->entry->value); 

        node->right = tree_delete_node(node->right, successeur->entry->key);
    }

    return node; 
}

void tree_save_in_order(tree_node *node, FILE *file) {
    if (node == NULL) {
        return;
    }

    tree_save_in_order(node->left, file);
    fprintf(file, "%s,%s\n", node->entry->key, node->entry->value);
    tree_save_in_order(node->right, file);
}

void tree_load_entry(char *line) {
    char *key = strtok(line, "=");
    char *value = strtok(NULL, "\n");

    if (key != NULL && value != NULL) {
        db_entry *entry = malloc(sizeof(db_entry));
        entry->key = strdup(key);   
        entry->value = strdup(value); 

        tree_insert(&tree_root, entry);  
    }
}

void tree_print_in_order(tree_node *node) {
    if (node == NULL) {
        return;
    }

    tree_print_in_order(node->left);  
    printf("Clé: %s, Valeur: %s\n", node->entry->key, node->entry->value); 
    tree_print_in_order(node->right); 
}
