#ifndef H_SPECIALVAR
#define H_SPECIALVAR
#include "specialvar.h"
#endif

int count_atoi_size (int number)
{
    int res = 0;
    if (number < 0) {
        number = - number;
        res++;
    }
    else if (number == 0) {
        return 1;
    }
    while(number > 0) {
        number /= 10;
        res++;
    }
    return res;
}

void add_interrogation()
{
    char* question = calloc(2, 1);
    strncpy(question, "?", 1);
    char* qval = calloc(1,1);
    add_variable(question, qval);
}

void change_interrogation_value(int newvalue)
{
    char* val = get_value_of_var("?");
    free(val);
    int len = count_atoi_size(newvalue) + 1;
    val = malloc(len);
    sprintf(val, "%d", newvalue);
    val[len - 1] = '\0';
    change_variable_value("?", val);
}

int is_special_var (char* name)
{
    return (strcmp("?", name) == 0);
}