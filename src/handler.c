#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>

#include "../include/Interface.h"

void distributeToWorkers(workersInfo *myWorkersInfo, int numOfWorkers, int bufferSize, char *input_dir)
{

    pid_t childpid;

    dirListNode *headDirList = dirListingToList(input_dir);
    int numOfDirs = listNodeCounter(headDirList);
    int divRes = numOfDirs / numOfWorkers;
    int modRes = numOfDirs % numOfWorkers;

    int i, dirsForWorker;
    dirListNode *current = headDirList;
    for (i = 1; i <= numOfWorkers; i++)
    {
        dirsForWorker = divRes;
        if (modRes - i >= 0)
            dirsForWorker++;

        char fifoToWorker[20], fifoFromWorker[20];
        sprintf(fifoToWorker, "/tmp/Worker%dIn", i);
        sprintf(fifoFromWorker, "/tmp/Worker%dOut", i);
        if (mkfifo(fifoToWorker, 0666) == -1)
            perror("mkfifo1");
        if (mkfifo(fifoFromWorker, 0666) == -1)
            perror("mkfifo2");

        myWorkersInfo->workerPATHs[i - 1][0] = (char *)malloc(sizeof(char) * (strlen(fifoToWorker) + 1));
        myWorkersInfo->workerPATHs[i - 1][1] = (char *)malloc(sizeof(char) * (strlen(fifoFromWorker) + 1));

        strcpy(myWorkersInfo->workerPATHs[i - 1][0], fifoToWorker);
        strcpy(myWorkersInfo->workerPATHs[i - 1][1], fifoFromWorker);

        if ((childpid = fork()) <= 0)
        {

            if (childpid == -1)
            {
                perror("failed to fork");
                exit(-1);
            }
            int fdRead = open(fifoToWorker, O_RDWR | O_NONBLOCK);
            int fdWrite = open(fifoFromWorker, O_RDWR | O_NONBLOCK);

            // const char *dirNames[dirsForWorker];
            // for (int j = 0; j < dirsForWorker; j++) {
            //     dirNames[j] = current->dirName;
            //     current = current->next;
            // }
            dirListNode *current;
            while(read(fdRead, current, bufferSize) == -1) {}
            //workerExec();
            //handleWorkerExit();
            exit(-1);
        }
        else
        {
            myWorkersInfo->workerPIDs[i - 1] = childpid;
            puts("aggregator\n");
            myWorkersInfo->workerFDs[i - 1][0] = open(fifoToWorker, O_RDWR | O_NONBLOCK); //write
            // if (storedFDs[i - 1][1] == -1) {
            //     perror("poutsa");
            // }
            myWorkersInfo->workerFDs[i - 1][1] = open(fifoFromWorker, O_RDWR | O_NONBLOCK); //read
            printf("fd: %d\n", myWorkersInfo->workerFDs[i - 1][1]);
            //write(myWorkersInfo->workerFDs[i - 1][0], "kalispera", 10);
            // for (int j = 0; j < dirsForWorker; j++) {
            //     current = current->next;
            // }
            continue;
        }
    }
}

void workerExec()
{
}