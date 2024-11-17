# Projet C CC1 - Base de données (avec arbre binaires et persistance sur disque) - Ryane GUEHRIA 3si5


# Fonctionnalités

- **CREATE TABLE table_name** : Crée une nouvelle table avec le nom spécifié.
- **INSERT INTO table_name (key, value)** : Insère une entrée dans la table avec la clé et la valeur fournies.
- **DELETE FROM table_name WHERE key='your_key'** : Supprime l'entrée correspondant à la clé spécifiée dans la table.
- **UPDATE table_name SET key='new_value' WHERE key='your_key'** : Met à jour la valeur de la clé dans la table.
- **SELECT * FROM table_name** : Affiche toutes les entrées de la table.
- **SHOW** : Affiche toutes les tables présentes dans la base de données.
- **SAVE** : Sauvegarde la base de données sur le disque.
- **LOAD** : Charge la base de données depuis le disque.
- **DROP TABLE table_name** : Supprime une table entière.
- **EXIT** : Quitte le programme.


# Points Techniques Importants
- Architecture et Organisation :

  Code structuré en plusieurs fichiers pour une séparation claire des responsabilités.
  Les fichiers **.o** et "db" apparaissent après exécution de la commande *make*.
  Utilisation d'un Makefile pour la gestion de la compilation et du nettoyage.

  **projetC** :
    - *include*
        - commands.h
        - db.h
        - db_entry.h
        - operations.h
        - saveload.h
        - tree.h

    - *src*
        - Makefile
        - commands.c
        - database.txt
        - db.c
        - main.c
        - operations.c
        - saveload.c
        - tree.c
     
    - *test* (pas utilisé pour la version finale)
        - test_db.c
        - test_tree.c

- Structure de Données :

  Toutes les données sont stockées dans un arbre binaire, permettant des recherches rapides et une organisation efficace.
  Support des opérations essentielles : insertion, suppression, modification, ajout, recherche et parcours.

- Gestion des Clés :

  Clés uniques, strictement positives (>= 1).
  Contrôle d'erreur intégré pour éviter les doublons ou les clés invalides (caractères non numérique ou valeur < 0).

- Persistance des Données :

  Sauvegarde des données dans un fichier texte (database.txt).
  Fonctionnalités pour recharger les données sauvegardées au démarrage.



# Commandes pour lancer le programme 

Cloner d'abord le dépôt :

```bash
git clone https://github.com/ryatozz/projetC
```
Se rendre dans le dossier src de **projetC** :
```bash
cd src
```

Nettoyer les fichiers compilés existants (optionnel) :
```bash
make clean
```

Compiler le projet :
```bash 
make
```

Lancer le programme :
```bash
./db
```

**Interagir avec le programme : Entrez les commandes SQL-like décrites ci-dessus pour interagir avec la base de données.**
