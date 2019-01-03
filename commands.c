#include "commands.h"

int ls (char *path)
{
    DIR* dir = opendir(path);
    if (dir == NULL) {
        perror("Error ls");
        return 1;
    }
    struct dirent* direntry;
    size_t current_line_length = 0;
    size_t format = 20;
    while ((direntry = readdir(dir)) != NULL) {
        if (direntry->d_name[0] == '.') continue;
        else {
            size_t len = strlen(direntry->d_name);
            size_t f = len > format ? len : format;
            if (current_line_length + f > MAX_LINE_LENGTH) {
                printf("\n");
                current_line_length = 0;
            }
            printf("%-*s", (int) f, direntry->d_name);
            current_line_length += f;
        }
    }
    printf("\n");
    free(dir);
    return 0;
}

int mkdir (char* cmdargs[])
{
    int pid = fork();
    if (pid == 0) {
        int exec;
        if (strncmp(cmdargs[1], "-p", 2) == 0) {
            exec = execlp("mkdir", cmdargs[0], cmdargs[1], cmdargs[2], NULL);
        }
        else {
            exec = execlp("mkdir", cmdargs[0], cmdargs[1], NULL);
        }
        if (exec == -1) {
            perror("Error mkdir");
            return 1;
        }
    }
    return 0;
}

int cat (char* cmdargs[])
{
    int pid = fork();
    if (pid == 0) {
        int exec = execlp("cat", cmdargs[0], cmdargs[1], NULL);
        if (exec == -1) {
            perror("Error cat");
            return 1;
        }
    }
    return 0;
}

int echo (char* cmdargs[])
{
    if (*cmdargs[1] == '$') {
        int len = strlen(cmdargs[1]) - 1; // ne pas compter le $ à la position 0
        char *nameV = calloc(len + 1, 1);
        strncpy(nameV, cmdargs[1] + 1, len);
        char *valueV = get_value_of_var(nameV);
        if (valueV != NULL) {
            printf("%s\n", valueV);
        }
        else {
            printf("Unknown variable\n");
        }
        free(nameV);
        return 0;
    }
    else {
        fprintf(stderr, "Unknown command\n");
        return 1;
    }
}

int del (char* cmdargs[])
{
    if (*cmdargs[1] == '\0') {
        fprintf(stderr, "Error del: missing parameter\n");
        return 1;
    }
    else if (!find_variable(cmdargs[1])) {
        fprintf(stderr, "Error del: unknown variable\n");
        return 1;
    }
    else {
        return delete_variable(cmdargs[1]);
    }
}
int process_command (char * cmdargs[])
{
    if (strncmp(cmdargs[0], "ls", 2) == 0) {
        char* dir = *cmdargs[1] != '\0' ? cmdargs[1] : ".";
        return ls (dir);
    }
    else if (strncmp(cmdargs[0], "mkdir", 5) == 0) {
        return mkdir(cmdargs);
    }
    else if (strncmp(cmdargs[0], "cat", 3) == 0) {
        return cat(cmdargs);
    }
    else if (strncmp(cmdargs[0], "echo", 4) == 0) {
        return echo(cmdargs);
    }
    else if (strncmp(cmdargs[0], "del", 4) == 0) {
        return del(cmdargs);
    }
    else {
        int posEqual = index_equal_in_varaffect(cmdargs[0]);
        if (posEqual != -1) {
            char* name = NULL, *value = NULL;
            parse_variable(cmdargs[0], &name, &value);
            if (find_variable(name)) {
                change_variable_value(name, value);
            }
            else {
                add_variable(name, value);
            }
        }
        else {
            fprintf(stderr, "Unknown command\n");
            return 1;
        }
    }
    return 0;
}