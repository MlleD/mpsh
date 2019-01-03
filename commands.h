#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include "varutils.h"
#include "var.h"
#include "constantes.h"

int ls (char *path);

int process_command (char * cmdargs[]);