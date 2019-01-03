#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include "varutils.h"
#include "var.h"
#include "constantes.h"

int ls (char *path);
int mkdir (char* cmdargs[]);
int cat (char* cmdargs[]);
int echo (char* cmdargs[]);
int del (char* cmdargs[]);

int process_command (char * cmdargs[]);