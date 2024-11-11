#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/tree.h"

int cmp_db_entry(const db_entry *x, const db_entry *y) {
    int key_cmp = strcmp(x->key, y->key);
    if (key_cmp != 0) {
        return key_cmp;
    }
    return strcmp(x->value, y->value);
}

void tree_insert(tree_node **root, db_entry *entry) {
    if (*root == NULL) {
        *root = (tree_node *)malloc(sizeof(tree_node));
        (*root)->entry = entry;
        (*root)->left = (*root)->right = NULL;
    } else {
        if (cmp_db_entry(entry, (*root)->entry) < 0) {
            tree_insert(&(*root)->left, entry);
        } else {
            tree_insert(&(*root)->right, entry);
        }
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

        tree_node *temp = node->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        free(node->entry->key);
        free(node->entry->value);
        node->entry->key = strdup(temp->entry->key);
        node->entry->value = strdup(temp->entry->value);

        node->right = tree_delete_node(node->right, temp->entry->key); 
    }
    return node;
}

void tree_print_in_order(tree_node *node) {
    if (node != NULL) {
        tree_print_in_order(node->left);
        printf("%s: %s\n", node->entry->key, node->entry->value);
        tree_print_in_order(node->right);
    }
}
