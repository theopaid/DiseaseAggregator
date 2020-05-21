#include "../include/Interface.h"

bool validArgs(int argc, char *argv[])
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

void getArgs(int *numWorkers, int *bufferSize, char **input_dir, char *argv[]) {

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