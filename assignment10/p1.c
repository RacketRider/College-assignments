Program 	#include <stdio.h>
#include <string.h>

#define MAX_NODES 100
#define NAME_LEN 50

char nodeNames[MAX_NODES][NAME_LEN];
int graphMat[MAX_NODES][MAX_NODES];
int queueData[MAX_NODES];
int visitMark[MAX_NODES];
int bfsOrder[MAX_NODES];
int totalNodes;

int findNodeIndex(char key[])
{
    int idx;
    for(idx=0;idx<totalNodes;idx++)
    {
        if(strcmp(nodeNames[idx],key)==0)
        {
            return idx;
        }
    }
    return -1;
}

void printMatrix()
{
    int row,col;
    printf("Adjacency Matrix:\n\n");
    printf("%-5s","");
    for(col=0;col<totalNodes;col++)
    {
        printf("%-5s",nodeNames[col]);
    }
    printf("\n");
    for(row=0;row<totalNodes;row++)
    {
        printf("%-5s",nodeNames[row]);
        for(col=0;col<totalNodes;col++)
        {
            printf("%-5d",graphMat[row][col]);
        }
        printf("\n");
    }
}

void printQueueState(int front,int rear)
{
    int pos;
    printf("  Queue:");
    for(pos=front;pos<=rear;pos++)
    {
        printf(" %s",nodeNames[queueData[pos]]);
    }
    printf("\n");
}

void runBfs(int startIndex)
{
    int front=0,rear=-1;
    int current,next,orderPos=0;

    queueData[++rear]=startIndex;
    visitMark[startIndex]=1;

    printf("\nStep-by-step BFS traversal:\n\n");

    while(front<=rear)
    {
        current=queueData[front++];
        bfsOrder[orderPos++]=current;

        printf("Visited: %s\n\n",nodeNames[current]);

        for(next=0;next<totalNodes;next++)
        {
            if(graphMat[current][next]!=0 && !visitMark[next])
            {
                visitMark[next]=1;
                queueData[++rear]=next;
                printf("  %s --> %s (edge exists, enqueueing)\n\n",nodeNames[current],nodeNames[next]);
            }
        }

        printQueueState(front,rear);
    }

    printf("\nFinal BFS Traversal Order:\n\n");
    for(current=0;current<orderPos;current++)
    {
        printf("%s",nodeNames[bfsOrder[current]]);
        if(current<orderPos-1)
        {
            printf(" ");
        }
    }
    printf("\n\nTime Complexity: O(V + E)\n\n");
    printf("Space Complexity: O(V)\n");
}

int main()
{
    int row,col,startIndex;
    char startName[NAME_LEN];

    scanf("%d",&totalNodes);

    for(row=0;row<totalNodes;row++)
    {
        scanf("%s",nodeNames[row]);
    }

    for(row=0;row<totalNodes;row++)
    {
        for(col=0;col<totalNodes;col++)
        {
            scanf("%d",&graphMat[row][col]);
        }
    }

    scanf("%s",startName);
    startIndex=findNodeIndex(startName);

    printMatrix();
    runBfs(startIndex);

    return 0;
}
