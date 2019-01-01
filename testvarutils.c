#include "varutils.h"
#include <assert.h>

void test_index_equal_in_varaffect ()
{
    char* var = "word";
    assert(index_equal_in_varaffect(var) == -1);
    var = "123456";
    assert(index_equal_in_varaffect(var) == -1);
    var="number=123456";
    assert(index_equal_in_varaffect(var) == 6);
    var="number = 123456";
    assert(index_equal_in_varaffect(var) == -1);
}

void test_parse_variable ()
{
    char* varaffect = "myVar1=1234";
    char* name = NULL, *value = NULL;
    parse_variable(varaffect, &name, &value);

    assert(strncmp(name, "myVar1", 7) == 0);
    assert(strncmp(value, "1234", 5) == 0);
    free(name);
    free(value);
}

int main(int argc, char const *argv[])
{
    test_parse_variable();
    test_index_equal_in_varaffect();
    return 0;
}