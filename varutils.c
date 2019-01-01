#include "varutils.h"

int index_equal_in_varaffect (char* str)
{
    int i = 0;
    while (str[i] != '\0') {
        if (isspace(str[i])) {
            return -1;
        }
        else if (str[i] == '=') {
            return i;
        }
        i++;
    }
    return -1;
}

void parse_variable (char* varaffect, char** name, char** value) {
    int posEqual = index_equal_in_varaffect(varaffect);
    if (posEqual == -1) {
        return;
    }
    *name = malloc (posEqual + 1);
    int sizeValue = strlen(varaffect) - posEqual - 1;
    *value = malloc (sizeValue + 1);
    strncpy(*name, varaffect, posEqual);
    strncpy(*value, varaffect + posEqual + 1, sizeValue + 1);
}