#include "variables.h"

// Nombre de variables dans le tableau de variables
int numberVariables = 0;

// Capacité du tableau de variables : Nombre maximal de variables stockables
// La capacité est extensible : double quand le nombre de variable atteint la capacité
int capacity = 1;

void init_variables_array () {
    variables = malloc(sizeof(*variables));
}

/* * 
 * Double la taille du tableau de variables
 * Retourne 1 en cas de succès, 0 sinon
 * */
int double_array_size ()
{
    variable_t** new = realloc(variables, 2 * capacity);
    if (new == NULL) { 
        perror("Error when doubling variables arraysize: ");
        return 0;
    }
    variables = new;
    capacity *= 2;
    return 1;
}

int add_variable (char* name, char* value)
{
    if (numberVariables == capacity) {
        if (double_array_size(2 * capacity) == 1) {
            return 1;
        }
    }
    variable_t* var = malloc(sizeof(*var));
    if (var == NULL) {
        perror ("Error malloc for the variable to add: ");
        return 0;
    }
    var->name = name;
    var->value = value;
    *(variables + numberVariables) = var;
    numberVariables++;
    return 1;
}

int find_index_variable (char* name)
{
    int pos = numberVariables - 1;
    while (pos >= 0 && (strncmp(name, (*(variables + pos))->name, strlen(name)) != 0)) {
        pos--;
    }
    return pos;
}

int find_variable (char *name)
{
    return find_index_variable(name) != -1;
}

int change_variable_value (char* name, char* newvalue)
{
    int pos = find_index_variable(name);
    if (pos == -1) {
        fprintf(stderr, "Variable not found\n");
        return 0;
    }
    (*(variables + pos))->value = newvalue;
    return 1;
}

int delete_variable (char* name) {
    int pos = find_index_variable(name);
    if (pos == -1) {
        fprintf(stderr, "Variable not found\n");
        return 0;
    }
    free (variables[pos]);
    if (numberVariables > 1) {
        /* Subtitution entre la variable à la position numberVariables
         * et la position de name pour combler le "trou" */
        variables[pos] = variables[numberVariables];
        variables[numberVariables] = NULL;
    }
    numberVariables--;
    return 1;
}

char* get_value_of_var (char* name)
{
    int pos = find_index_variable(name);
    if (pos == -1) {
        return NULL;
    }
    return (variables[pos])->value;
}

void free_var_array () {
    for (int i = 0; i < numberVariables; i++) {
        free(variables[i]->name);
        free(variables[i]->value);
        free(variables[i]);
    }
    free(variables);
}