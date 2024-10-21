#ifndef DB_H
#define DB_H

extern db_table *tables;  
extern int num_tables;    


typedef struct {
    char clé[100];     
    char valeur[100];  
} db_entry;


typedef struct {
    db_entry *entries;  
    int num_entries;   
} db_row;

typedef struct {
    char name[100];   
    db_row *rows;      
    int num_rows;     
} db_table;

extern db_table *tables;  
extern int num_tables;    

void db_init();
void db_create_table(const char *table_name);
void db_insert_into(const char *table_name, const char *key, const char *value);
void db_update(const char *table_name, const char *key, const char *new_value);
void db_delete_from(const char *table_name, const char *key);
db_table* db_get_table(const char *table_name);
db_row* db_select_all(const char *table_name);
void db_save_to_disk();
void db_load_from_disk();
void db_close();

#endif 
