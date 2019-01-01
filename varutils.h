#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Une varaffect est une chaîne de la forme nom=valeur

/* Paramètres : str (char*), la chaîne à vérifier
 * Retourne l'index du signe egal dans str si str est une varaffect, -1 sinon
 * */
int index_equal_in_varaffect (char* str);

/* Paramètres : varaffect (char*), name (char*), value (char*)
 * Parse la chaine de caractère varaffect
 * Modifie name et value si varaffect a le motif varName=varValue
 * */
void parse_variable (char* varaffect, char** name, char** value);