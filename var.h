#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef H_SPECIALVAR
#define H_SPECIALVAR
#include "specialvar.h"
#endif

typedef struct variable {
    char* name;
    char* value;
}variable_t;

variable_t** variables;

/* *
 * Alloue la mémoire nécessaire au tableau de variables
 * */
void init_variables_array ();

/* *
 * Ajoute une variable (nom et valeurs passés en paramètres)
 * Renvoie 1 si la variable a été ajoutée avec succès, 0 sinon
 * */
int add_variable (char* name, char* value);

/* *
 * Retourne la position de la variable name dans le tableau de variables,
 * ou - 1 si name n'a pas été trouvé
 * */
int find_index_variable (char* name);

/* *
 * Paramètre : name(char*), nom de la variable à rechercher
 * Retourne 1 si la variable name a été trouvée, 0 sinon
 * */
int find_variable (char *name);

/* *
 * Paramètres : name (char*), nom de la variable, newvalue (char*), nouvelle valeur de la variable
 * Change la valeur d'une variable
 * Retourne 1 si la valeur a été changée avec succès, 0 sinon
 * */
int change_variable_value (char* name, char* newvalue);

/* *
 * Paramètre : name(char*), nom de la variable à supprimer
 * Retourne 1 si la variable name a été supprimée avec succès, 0 sinon
 * */
int delete_variable (char* name);

/* *
 * Paramètre : name(char*), nom de la variable à chercher
 * Renvoie la valeur de la variable de nom name passée en paramètre
 * ou NULL si la variable n'a pas été trouvée
 * */
char* get_value_of_var (char* name);

/* *
 * Libère la mémoire associée au tableau de variables
 * */
void free_var_array ();

/* *
 * Libère la mémoire associée à une variable
 * */
void free_var (variable_t* var);