/*
    Author: Omar Kaddura
    EUID: omk0018
    November 26, 2021

    Command Description: The cd command is used to switch
			 between dirctories in operating systems. 
    
*/
#include "major2.h"


int cd(char *pth){
   
size_t temp = 1024;
   char path[temp];
    strcpy(path,pth);

 

    char cwd[temp];
    if(pth[0] != '/')
    {
        getcwd(cwd,sizeof(cwd));
        strcat(cwd,"/");
        strcat(cwd,path);
        chdir(cwd);
    }
	else{//true for dir w.r.t. /
        chdir(pth);
    }

 

    return 0;
}
