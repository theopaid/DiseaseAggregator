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

pid_t *distributeToWorkers(int numOfWorkers, int bufferSize, char *input_dir)
{

    pid_t childpid;
    pid_t *workersInf = (pid_t*) malloc(numOfWorkers*sizeof(pid_t));

    dirListNode *headDirList = dirListingToList(input_dir);
    int numOfDirs = listNodeCounter(headDirList);
    int divRes = numOfDirs/numOfWorkers;
    int modRes = numOfDirs%numOfWorkers;
    int storedFDs[numOfWorkers][2];

    int i, dirsForWorker;
    dirListNode *current = headDirList;
    for (i = 1; i <= numOfWorkers; i++)
    {
        dirsForWorker = divRes;
        if (modRes - i >= 0)
            dirsForWorker++;

        char fifoToWorker[100], fifoFromWorker[100];
        sprintf(fifoToWorker, "/tmp/Worker%dIn", i);
        sprintf(fifoFromWorker, "/tmp/Worker%dOut", i);
        mkfifo(fifoToWorker, 0666);
        mkfifo(fifoFromWorker, 0666);

        if ((childpid = fork()) <= 0)
        {
            workersInf[i-1] = childpid;
            if (childpid == -1)
            {
                perror("failed to fork");
                break;
            }
            int fdWrite = open(fifoFromWorker, O_WRONLY);
            int fdRead = open(fifoToWorker, O_RDONLY);

            // const char *dirNames[dirsForWorker];
            // for (int j = 0; j < dirsForWorker; j++) {
            //     dirNames[j] = current->dirName;
            //     current = current->next;
            // }
            //workerExec();
            //handleWorkerExit();
            break;
        }
        else
        {
            storedFDs[i-1][1] = open(fifoToWorker, O_WRONLY); //write
            storedFDs[i-1][2] = open(fifoFromWorker, O_RDONLY); //read
            // for (int j = 0; j < dirsForWorker; j++) {
            //     current = current->next;
            // }
            continue;
        }
    }

    return workersInf;
}

void workerExec() {


}