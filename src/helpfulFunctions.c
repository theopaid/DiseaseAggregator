#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>

#include "../include/Interface.h"

bool validArgs(int argc, const char *argv[])
{

    if (argc == 7)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void getArgs(int *numWorkers, int *bufferSize, char **input_dir, const char *argv[])
{

    for (int i = 1; i < 7; i = i + 2)
    {
        if (!strcmp(argv[i], "-i"))
        {
            *input_dir = argv[i + 1];
        }
        else if (!strcmp(argv[i], "-b"))
        {
            *bufferSize = atoi(argv[i + 1]);
        }
        else if (!strcmp(argv[i], "-w"))
        {
            *numWorkers = atoi(argv[i + 1]);
        }
    }
}

dirListNode *dirListingToList(char *inputDir)
{

    DIR *dp;
    struct dirent *ep;
    dp = opendir(inputDir);

    dirListNode *head = NULL, *current = NULL;
    if (dp != NULL)
    {
        while ((ep = readdir(dp)) != NULL)
        {
            if ((strcmp(ep->d_name, ".") == 0 || strcmp(ep->d_name, "..") == 0 || (*ep->d_name) == '.'))
            {
            }
            else
            {
                if (head == NULL)
                {
                    head = (dirListNode *)malloc(sizeof(dirListNode));
                    head->dirName = malloc(sizeof(char) * (strlen(ep->d_name) + 1));
                    strcpy(head->dirName, ep->d_name);
                    head->next = NULL;
                    current = head;
                }
                else
                {
                    current->next = (dirListNode *)malloc(sizeof(dirListNode));
                    current = current->next;
                    current->dirName = malloc(sizeof(char) * (strlen(ep->d_name) + 1));
                    strcpy(current->dirName, ep->d_name);
                    current->next = NULL;
                }
            }
        }

        (void)closedir(dp);
    }
    else
        perror("Couldn't open the directory");

    return head;
}

int listNodeCounter(dirListNode *head)
{

    int count = 0;
    while (head != NULL)
    {
        count++;
        head = head->next;
    }

    return count;
}

void allocateWorkersInfo(workersInfo *myWorkersInfo, int numOfWorkers)
{

    myWorkersInfo->workerPIDs = (pid_t *)malloc(numOfWorkers * sizeof(pid_t));

    myWorkersInfo->workerFDs = (int **)malloc(numOfWorkers * sizeof(int *));
    for (int i = 0; i < numOfWorkers; i++)
        myWorkersInfo->workerFDs[i] = (int *)malloc(2 * sizeof(int));

    myWorkersInfo->workerPATHs = (char ***)malloc(numOfWorkers * sizeof(char **));
    for (int k = 0; k < numOfWorkers; k++)
        myWorkersInfo->workerPATHs[k] = (char **)malloc(2 * sizeof(char *));
}