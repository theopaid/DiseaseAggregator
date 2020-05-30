#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>

#include "../include/Interface.h"

int main(int argc, const char *argv[])
{

    // dirListNode *headDirList = dirListingToList("input_dir");

    if (!validArgs(argc, argv))
    {
        printf("The arguments given are invalid. Try again.\n");
        return -1;
    }

    int numOfWorkers, bufferSize;
    char *input_dir;
    getArgs(&numOfWorkers, &bufferSize, &input_dir, argv);

    workersInfo myWorkersInfo;
    allocateWorkersInfo(&myWorkersInfo, numOfWorkers);

    distributeToWorkers(&myWorkersInfo, numOfWorkers, bufferSize, input_dir);

    dirListNode *headDirList = dirListingToList(input_dir);
    int numOfDirs = listNodeCounter(headDirList);
    int divRes = numOfDirs / numOfWorkers;
    int modRes = numOfDirs % numOfWorkers;

    dirListNode *current = headDirList;
    int dirsForWorker;
    for (int i = 1; i <= numOfWorkers; i++)
    {
        write(myWorkersInfo.workerFDs[i - 1][0], current, bufferSize);
        dirsForWorker = divRes;
        if (modRes - i >= 0)
            dirsForWorker++;
        for (int j = 0; j < dirsForWorker; j++)
        {
                dirNames[j] = current->dirName;
                current = current->next;
            }
        }

    renderMenu(&myWorkersInfo, numOfWorkers);

    return 0;
    }
