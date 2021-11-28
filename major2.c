/*
Omar Kaddura omk0018
Jackson Johanek
Jonathan Johnson
Henry Iraheta 

3600.003
Group 13
November 26th 2021
*/
#include "major2.h"
 


	size_t li_size = 1024;// length of line
	char line[1024];// line buffer
	char *lp = line;
	char *token;
	char cwd[1000];
    int increment = 0;
 
struct PathNode	{

	char path[512];

	bool exist;
};

void Path(char X[]);
void Kill(char X[]);

struct PathNode paths[100];
int pathsIndex = 1;
char* env[] = {paths[0].path, NULL};



 

int main(int argc, char* argv[]) {



//struct PathNode paths[100];
//int pathsIndex = 1;
//char* env[] = {paths[0].path, NULL};


	void (*pfRet)(int) = signal(SIGINT, SIG_IGN);

        void (*pfRet2)(int) = signal(SIGSTOP, SIG_IGN);

        void (*pfRet3)(int) = signal(SIGQUIT, SIG_IGN);

        void (*pfRet4)(int) = signal(SIGHUP, SIG_IGN);

        void (*pfRet5)(int) = signal(SIGILL, SIG_IGN);

        void (*pfRet6)(int) = signal(SIGKILL, SIG_IGN);

        void (*pfRet7)(int) = signal(SIGTERM, SIG_IGN);

//        void (*pfRet8)(int) = signal(SIGTSTP, SIG_IGN);

//        signal (SIGTTIN, SIG_IGN);
//        signal (SIGTTOU, SIG_IGN);

	strcpy(paths[0].path,"/bin");
	paths[0].exist = true;




    while (1) {

 

//Ineractive Mode
        if (argc == 1) {
 
if (getcwd(cwd, sizeof(cwd)) != NULL)
{
printf("%s$ ", cwd);

}


//reads user's input	
fgets(lp, li_size,stdin);
        
    
//since fgets outputs outomatic endl. this implementation gets rid of that defult endl. 
endltoken = strchr(lp,'\n'); 
         if(endltoken) { 
            *endltoken = '\0'; 
         }

addqueue(line);    //adds command inputted into myhistory queue

/* I/O redirection */
char *insig = strstr(line, "< ");  //test if "< (filename)" exists in given command
if (insig)
{
    char* infile = strchr(line, "< ");
    int fd = open(infile, O_RDONLY );
    dup2(fd, STDIN_FILENO);
}
char *osig = strstr(line, "> ");   //test if "> (filename)" exists in given command
if (osig)
{
    char* outfile = strchr(line, "> ");
    int fd = open(outfile, O_WRONLY);
    dup2(fd, STDOUT_FILENO);
}
/*end of I/O redirection*/

//checking for alias in input
         for(int j=0; j < increment; j++)
         {
             if(strcmp(alias_one[j],lp)==0){
                
                 strcpy(lp,alias_two[j]);
             }
            
                    
         }



    
		
//cd Command section
	if(find_command(line,"cd") == 0){
          

            token = strchr(lp,' '); 
            if(token) {
                char *temptoken = token + 1;
                token = temptoken;
                char *locationOfNewLine = strchr(token, '\n');
                if(locationOfNewLine) {
                    *locationOfNewLine = '\0';
                }
                cd(token);
            }
        
		else{
            chdir("/home"); 
		}                   
}   
//end of cd command section           
       
       
	   
	   
	   
//exit command section
	else if(find_command(line,"exit") == 0){
           printf("execute the exit code\n");
           
       }       
       
			//path command section
			//else if(find_command(line,"path") == 0){
			else if(strstr(line,"path"))	{
				Path(line);
           			printf("execute the path code\n");
			}

			else if(strstr(line,"kill"))    {
                		Kill(line);
           			printf("execute the path code\n");
       			}




       
//myhistory command section
	else if(find_command(line,"myhistory") == 0){  
           myhistory();
       }       
       


//aliasing code here:

 else if(find_command(line,"alias") == 0){ 
            
          token2 = strchr(lp,' '); 
          token4 = strchr(lp,'\''); 
		  alias_remove = strchr(lp,'-');
          if(token2) {
            if(token4) {
            char *temptoken2 = token2 + 1;
            token2= temptoken2;
            char *token2locationOfNewLine = strchr(token2, '=');
             if(token2locationOfNewLine){
                 *token2locationOfNewLine = '\0';
             }
                
             char *temptoken4 = token4 + 1;
             token4 = temptoken4;
             char *token4locationOfNewLine = strchr(token4, '\'');
              if(token4locationOfNewLine){
                 *token4locationOfNewLine = '\0';
             }

 

        strcpy(alias_one[increment], token2);
        strcpy(alias_two[increment], token4);
		
        ++increment;
        
			}
               

//removing alias:
	
	 else if(alias_remove){
                r_remove = strchr(alias_remove,'r');
                c_remove = strchr(alias_remove,'c');
                
        if(c_remove) //removing all the aliases
			{
        for(int k=0; k<increment;k++)
			{
            strcpy(alias_one[k], "");
            strcpy(alias_two[k], "");
                increment =0;
			}
			}
        else if(r_remove) //removing a specic alias
			{    
            char *rrm =strchr(r_remove,' ');
            char *tempRRm = rrm + 1;
            rrm = tempRRm;
        for(int m=0; m<increment; ++m)
			 {
            if(strcmp(alias_one[m],rrm)==0)
				{
                strcpy(alias_one[m], "");
                strcpy(alias_two[m], "");
				}
			 }
			}
     }
	 
		}
//printing all the aliases
        else 
			{
        for(int prnt=0; prnt<increment; ++prnt)
			{
            printf("%s        %s \n",alias_one[prnt],alias_two[prnt]); 
	
			}
        
            }
 }

    
//This else statement will be implemented when neither of the 4 commands(cd, exit, path, myhistory) are inputted by the user and will display the following message
 else
        {
            printf("The command you entered was not found: -%s\n",line);

            continue;
        }

}


// Batch Mode
        else if (argc == 2) {
            FILE *fp;

 

            // Check if file can't be opened
            if (access(argv[1], F_OK) == -1) {
                fprintf(stderr, "ERROR: File doesn't exist\n");
                exit(0);
            }
            // Otherwise, open file
            else {
                fp = fopen(argv[1], "r");

 

                // If file can't be opened, send error
                if (fp == NULL) {
                    fprintf(stderr, "ERROR: File can't be opened\n");
                    exit(0);
                }
				
//This where the batch execusion and code should be implemented:

                fclose(fp);
            }

        } 
        
		
// Neither 1 or 2 args: Error
        else {
            fprintf(stderr, "ERROR: Incorrect number of command line arguments\nPlease enter 1 argument to access Ineractive Mode, or 2 arguments to access Batch mode\n");
            exit(0);
        }
    }

 


 

    return 0;
}


//This is to understand user's input
int find_command(char  *x, char  *y)
{
int i = 0;
for(i = 0;y[i];i++)
{
if(x[i] != y[i])
return -1;
}
return 0;
}

void Path(char X[])	{

        char path[512] = "";

        char newPath[512] = "";

        int pathl = strlen(X) - 9 ;

	if(strlen(X) > 5)	{

        	strncpy(path,X + 8 ,pathl);
	}

	if(X[5] == '+')	{

	strcpy(paths[pathsIndex].path,path);

	paths[pathsIndex].exist = true;

	pathsIndex++;


	for(int i = 0; i < 100; i++)	{

		if(paths[i].exist == true)	{

			strcat(newPath,paths[i].path);

			strcat(newPath,":");
		}
	}

        env[0] = newPath;

	}

	else if(X[5] == '-')	{

		bool found = false;

        	for(int i = 0; i < 100; i++)    {

                	if(paths[i].exist == true)      {

				if(strcmp(path,paths[i].path) == 0)	{

					paths[i].exist = false;

					found = true;
				}
                	}
        	}

		if(found == false)	{

			printf("Path Not Found\n");

			return;
		}

	        for(int i = 0; i < 100; i++)    {

        	        if(paths[i].exist == true)      {

                	        strcat(newPath,paths[i].path);

                        	strcat(newPath,":");
                	}
        	}

        	env[0] = newPath;
	}

	else	{

        	for(int i = 0; i < 100; i++)    {

                	if(paths[i].exist == true)      {

                        	strcat(newPath,paths[i].path);

                        	strcat(newPath,":");
                	}
        	}

        	env[0] = newPath;
	}

	pid_t cpid = fork();

	pid_t cpid2;

	int stat;

	if(cpid == 0)	{


//           signal (SIGQUIT, SIG_DFL);
//	   signal (SIGTSTP, SIG_DFL);
  //         signal (SIGTTIN, SIG_DFL);
    //       signal (SIGTTOU, SIG_DFL);
      //     signal (SIGCHLD, SIG_DFL);
        //   signal (SIGINT, SIG_DFL);


	//	setpgid(0,0);

	//	tcsetpgrp(0,getpgrp());

//		cpid2 = cpid;

//		sleep(5);

        	execle("/usr/bin/env", "env" , NULL, env);
	}

	else {

  //              setpgid(cpid,cpid);

    //            tcsetpgrp (STDIN_FILENO, getpgid(cpid));

		waitpid(cpid,&stat,0);

//		tcsetpgrp (STDIN_FILENO, getpgrp());
		return;
	}
}

void Kill(char X[])	{


        pid_t cpid = fork();

        pid_t cpid2;

        int stat;

        if(cpid == 0)   {


//           signal (SIGQUIT, SIG_DFL);
  //         signal (SIGTSTP, SIG_DFL);
    //       signal (SIGTTIN, SIG_DFL);
      //     signal (SIGTTOU, SIG_DFL);
        //   signal (SIGCHLD, SIG_DFL);
          // signal (SIGINT, SIG_DFL);


            //    setpgid(0,0);

              //  tcsetpgrp(0,getpgrp());

                //cpid2 = cpid;

                //sleep(5);


	int space2;

	char sig[512] = "";

	char pid[512] = "";

	char sigx[512] = "SIG";

	int pidl = 0;

	for(int i = 5; i < strlen(X); i++)	{

		if(X[i] == ' ')	{

			space2 = i;

			break;
		}
	}

	strncpy(sig,X + 6,space2 - 6);

	printf("%s_\n",sig);

	pidl = strlen(X) - strlen(sig) - 7;

	strncpy(pid,X + 7 + strlen(sig),pidl);

	printf("%s_\n",pid);

	int pidx = atoi(pid);

	strcat(sigx,sig);

        printf("%s_\n",sigx);

	if(strcmp(sigx,"SIGKILL") == 0)	{

		kill(pidx,SIGKILL);
	}

        else if(strcmp(sigx,"SIGINT") == 0) {

                if(kill(pidx,SIGINT) == -1){printf("error\n");};
        }

        else if(strcmp(sigx,"SIGTERM") == 0) {

                kill(pidx,SIGTERM);
        }

        else if(strcmp(sigx,"SIGQUIT") == 0) {

                kill(pidx,SIGQUIT);
        }

        else if(strcmp(sigx,"SIGHUP") == 0) {

                kill(pidx,SIGHUP);
        }


	else{

		printf("signal not found\n");
	}

        sigx[0] = '\0';

	}

        else {
//
  //              setpgid(cpid,cpid);

    //            tcsetpgrp (STDIN_FILENO, getpgid(cpid));

                waitpid(cpid,&stat,0);

        //        tcsetpgrp (STDIN_FILENO, getpgrp());
                return;
        }
}

