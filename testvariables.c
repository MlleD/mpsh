#include "variables.c"
#include <assert.h>

int main(int argc, char const *argv[])
{
    init_variables_array();
    char* v1 = "myVar1";
    assert(!find_variable(v1));
    add_variable(v1, "123");
    assert(find_variable(v1));
    assert(strncmp(get_value_of_var(v1), "123", 3) == 0);
    change_variable_value(v1, "456");
    assert(strncmp(get_value_of_var(v1), "456", 3) == 0);
    delete_variable(v1);
    assert(!find_variable(v1));
    free_var_array();
    return 0;
}