#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>

int main(int argc, const char* argv[]) {

    if (!validArgs(argc, argv))
    {
        printf("The arguments given are invalid. Try again.\n");
        return -1;
    }

    int numWorkers, bufferSize;
    char *input_dir;
    getArgs(&numWorkers, &bufferSize, &input_dir);

    distributeToWorkers(numWorkers, bufferSize, input_dir);

    return 0;
}


void distributeToWorkers(int numOfWorkers, int bufferSize, char *input_dir) {

    pid_t childpid;

    int i;
    for (i=1; i<n; i++) {
        if ((childpid = fork()) <= 0)
        {
            if(childpid==-1) {
                perror("failed to fork");
                break;
            }
            workerExec();
            handleWorkerExit();
            break;
        }
        else {
            continue;
        }
    }


}