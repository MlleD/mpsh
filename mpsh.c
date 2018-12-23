#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#define MAX_ARGS_LENGTH 2097152
#define MAX_ARGS 10
#define MAX_LINE_LENGTH 100

int has_config_file ()
{
    /* Construction du chemin absolu du fichier de configuration */
    char *path = getenv("HOME");
    char *config_name = "/.mpshrc";
    char *absolute_path_config = malloc(strlen(path) + strlen(config_name) + 1);
    sprintf (absolute_path_config, "%s%s", path, config_name);
    
    /* Tentative d'ouverture du fichier de configuration */
    FILE* config = fopen(absolute_path_config, "r");
    free(absolute_path_config);

    /* Si config vaut NULL, c'est que le fichier n'existe pas. Sinon, il existe */
    return (config != NULL);
}

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
    return 0;
}

int process_command (char * cmdargs[])
{
    if (strncmp(cmdargs[0], "ls", 2) == 0) {
        char* dir = *cmdargs[1] != '\0' ? cmdargs[1] : ".";
        if (ls (dir) == 1) return 1;
    }
    else if (strncmp(cmdargs[0], "mkdir", 5) == 0) {
        int exec;
        int pid = fork();
        if (pid == 0) {
            if (strncmp(cmdargs[1], "-p", 2) == 0) {
                exec = execlp("mkdir", cmdargs[0], cmdargs[1], cmdargs[2], NULL);
            }
            else {
                exec = execlp("mkdir", cmdargs[0], cmdargs[1], NULL);
            }
            if(exec == -1) {
                perror ("Error mkdir");
                return 1;
            }
        }
    }
    else {
        fprintf(stderr, "Unknown command\n");
        return 1;
    }
    return 0;
}

int main (int argc, char const *argv[])
{
    if (has_config_file()) {
        printf("Le fichier de config existe.\n");
    }
    else {
        printf("Le fichier de config n'existe pas.\n");
    }
    char input[MAX_ARGS_LENGTH];
    char* cmd_args[MAX_ARGS]; 
    for (int i = 0; i < MAX_ARGS;i++) cmd_args[i] = malloc(8);
    int return_val = 0;
    int exit_val;
    while (1) {
        fgets(input, MAX_ARGS_LENGTH, stdin);
        sscanf(input, "%s %s %s %s", cmd_args[0], cmd_args[1], cmd_args[2], cmd_args[3]);
        //si commande "exit", sortie de la boucle while
        if (strncmp(cmd_args[0], "exit", 4) == 0) {
            if (*cmd_args[1] != '\0') {
                exit_val = atoi(cmd_args[1]);
            }
            else {
                exit_val = return_val;
            }
            break;
        }
        return_val = process_command(cmd_args);
        // flush cmd_args
        for (int i = 0; i < MAX_ARGS; i++) {
            *cmd_args[i] = '\0';
        }
    }
    for (int i = 0; i < MAX_ARGS; i++) free(cmd_args[i]);
    return exit_val;
}