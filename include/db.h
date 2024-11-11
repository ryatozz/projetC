#ifndef DB_H
#define DB_H

#include "db_entry.h"
#include "tree.h"

#define MAX_TABLE_NAME_LEN 50

typedef struct tree_node tree_node;

typedef struct {
    db_entry *entries;
    int num_entries;
} db_row;

typedef struct {
    char name[MAX_TABLE_NAME_LEN];
    db_row *rows;
    int num_rows;
    tree_node *tree_root;
} db_table;

void db_init();
int db_insert_into(const char *table_name, const char *key, const char *value);
void db_update(const char *table_name, const char *key, const char *new_value);
void db_delete_from(const char *table_name, const char *key);
db_table* db_create_table(const char *table_name);
db_table* db_get_table(const char *table_name);
db_row* db_select_all(const char *table_name);
void sauvegarder_en_txt();
void charger_depuis_txt();
void db_close(); 
void drop_table(const char *table_name);
void db_update_key(const char *table_name, const char *old_key, const char *new_key);

void insert_row(db_table *table, const char *key, const char *value);
db_entry* tree_search(tree_node *root, const char *key);

#endif
