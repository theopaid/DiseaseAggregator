#define LINE_MAX 1000

typedef struct dirListNode
{
    char *dirName;
    struct dirListNode *next;
} dirListNode;

typedef int bool;
#define true 1;
#define false 0;

bool validArgs(int argc,const char *argv[]);

void getArgs(int *numWorkers, int *bufferSize, char **input_dir,const char *argv[]);

pid_t *distributeToWorkers(int numOfWorkers, int bufferSize, char *input_dir);

void renderMenu(pid_t *workersInf, int numOfWorkers);

dirListNode *dirListingToList(char *inputDir);

int listNodeCounter(dirListNode *head);