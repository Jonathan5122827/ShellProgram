#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <error.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>
#include <fcntl.h>
int find_command(char  *, char  *);
int cd(char *pth);
int exit();
void myhistory();
void addqueue(char *cmd_string);

//alias declarations
char *token2;
char *endltoken; 
char *token4;
char *alias_remove; 
char *r_remove;
char *c_remove; 
char alias_one [20][50]; 
char alias_two [20][50]; 
