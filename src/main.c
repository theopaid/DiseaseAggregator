#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>

#include "../include/Interface.h"

int main(int argc, const char* argv[]) {

    // dirListNode *headDirList = dirListingToList("input_dir");

    if (!validArgs(argc, argv))
    {
        printf("The arguments given are invalid. Try again.\n");
        return -1;
    }

    int numWorkers, bufferSize;
    char *input_dir;
    getArgs(&numWorkers, &bufferSize, &input_dir, argv);

    pid_t *workersInf = distributeToWorkers(numWorkers, bufferSize, input_dir);

    renderMenu(workersInf, numWorkers);

    return 0;
}
