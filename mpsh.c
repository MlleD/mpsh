#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

#define ARG_MAX 2097152
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

void ls (char *path)
{
    DIR* dir = opendir(path);
    if (dir == NULL) {
        perror("Error ls");
        return;
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
}

int process_command (char *word1, char *word2)
{
    if (strncmp(word1, "ls", 2) == 0) {
        if (word2[0] == '\0') {
            sprintf(word2, "%s", ".");
        }
        ls (word2);
        return 0;
    }
    else {
        fprintf(stderr, "Unknown command\n");
        return 1;
    }
}

int main (int argc, char const *argv[])
{
    if (has_config_file()) {
        printf("Le fichier de config existe.\n");
    }
    else {
        printf("Le fichier de config n'existe pas.\n");
    }
    char input[ARG_MAX];
    char word1 [ARG_MAX/2], word2[ARG_MAX/2];
    while (1) {
        fgets(input, ARG_MAX, stdin);
        sscanf(input, "%s %s", word1, word2);
        if (process_command(word1, word2) == 1) return 1;
    }
    return 0;
}