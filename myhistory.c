/*
 * Created by: Jackson Johanek
 * myhistory command
 *
 *
 */
#include "major2.h"

    static int MAXCMD = 20;
    int currentsize = 0;
    bool qfull = false;
    char * queue[MAXCMD] = {0}; // initialize history with 0

void myhistory()
{
    for (int i = 0; i < 20; i++) //for all index in history;
    {
        if (queue[i] != 0) //if index != 0, print the command
        {
            printf("%s", queue[i]) //print the command
        }
    }
}

void addqueue(cmd_string)
{
    if (qfull == true) //if queue is full;
    {
        for (int i = 0; i < 19; i++)
        {
            queue[i] = queue[i+1];
            //remove first index;
            //shift all indexes;
        }
        currentsize--;
         //then add newest index
    }    
    queue[currentsize] = cmd_string; //add newest index
    currentsize++;
    if (currentsize == MAXCMD)
    {
        qfull = true;
    }
    else
    {
        qfull = false;
    }
}
