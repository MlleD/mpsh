#ifndef H_VAR
#define H_VAR
#include "var.h"
#endif

/**
 * Ajoute la variable '?' au tableau des variables
 */
void add_interrogation();

/**
 * Paramètre : newvalue (int), la nouvelle valeur de la variable '?'
 * Change la valeur de la variable '?'
 */
void change_interrogation_value(int newvalue);

/**
 * Paramètre : name (char*), nom de la variable à vérifier
 * Vérifie si la variable de nom name est une variable speciale
 */
int is_special_var (char* name);
