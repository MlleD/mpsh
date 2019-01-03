#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include "varutils.h"
#ifndef H_VAR
#define H_VAR
#include "var.h"
#endif
#include "constantes.h"
#include <errno.h>

int process_command (char * cmdargs[]);