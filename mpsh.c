#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    return 0;
}