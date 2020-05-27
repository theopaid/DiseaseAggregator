#define LINE_MAX 1000

typedef struct dirListNode
{
    char *dirName;
    struct dirListNode *next;
} dirListNode;

typedef struct workersInfo
{
    pid_t *workerPIDs;
    int **workerFDs;
    char ***workerPATHs;
} workersInfo;

typedef int bool;
#define true 1;
#define false 0;

bool validArgs(int argc, const char *argv[]);

void getArgs(int *numOfWorkers, int *bufferSize, char **input_dir, const char *argv[]);

void distributeToWorkers(workersInfo *myWorkersInfo, int numOfWorkers, int bufferSize, char *input_dir);

void renderMenu(workersInfo *myWorkersInfo, int numOfWorkers);

dirListNode *dirListingToList(char *inputDir);

int listNodeCounter(dirListNode *head);

void allocateWorkersInfo(workersInfo *myWorkersInfo, int numOfWorkers);