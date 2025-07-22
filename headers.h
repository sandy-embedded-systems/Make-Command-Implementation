      /* These are required header files and global variable and function declarations used for implementation */
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>

/* Global variables */

static char target_file[10];
char *arg[20];
unsigned long int lines;

/* Including file contents into main file */

#include"lines.c"
#include"search.c"
#include"make_l1.c"
#include"make_l.c"

/* Function declarations */

void check_syntax(int);
void check_seperator(int);
void getlines(int,int);
void make_target(void);
