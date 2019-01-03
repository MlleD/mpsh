#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"

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
    for (int i = 0; i < MAX_ARGS; i++) {
        cmd_args[i] = malloc(MAX_ARGS_LENGTH);
        *cmd_args[i] = '\0';
    }
    int return_val = 0;
    int exit_val;
    init_variables_array();

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
    free_var_array();
    return exit_val;
}