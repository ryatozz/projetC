#ifndef OPERATIONS_H
#define OPERATIONS_H


void ajouter_entree(const char *table_name, const char *key, const char *value);
void supprimer_entree(const char *table_name, const char *key);
void modifier_entree(const char *table_name, const char *old_key, const char *new_key);
void afficher_entree(const char *table_name);
void afficher_tables();

#endif
