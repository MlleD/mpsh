#include "var.h"
#include <assert.h>
#include <stdio.h>
int main(int argc, char const *argv[])
{
    init_variables_array();
    char* v1 = calloc(7, 1);
    strncpy(v1, "myvar1", 6);
    char* val1 = calloc(4, 1);
    strncpy(val1, "123", 3);
    assert(!find_variable(v1));    
    add_variable(v1, val1);
    char* v2 = calloc(5, 1);
    strncpy(v1, "var2", 4);
    char* val2 = calloc(4, 1);
    strncpy(val2, "mot", 3);
    add_variable(v2, val2);
    assert(find_variable(v1));
    assert(strncmp(get_value_of_var(v1), val1, 3) == 0);
    strncpy(val1, "456", 3);
    change_variable_value(v1, val1);
    assert(strncmp(get_value_of_var(v1), "456", 3) == 0);
    delete_variable(v1);
    assert(!find_variable("myvar1"));
    free_var_array();
    return 0;
}