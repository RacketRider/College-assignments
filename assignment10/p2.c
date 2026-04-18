Program 	#include <stdio.h>
#include <string.h>

#define MAX_NODES 100
#define NAME_LEN 50

char nodeNames[MAX_NODES][NAME_LEN];
int graphMat[MAX_NODES][MAX_NODES];
int stackData[MAX_NODES];
int visitMark[MAX_NODES];
int dfsOrder[MAX_NODES];
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

void printStackState(int top)
{
    int pos;
    printf("  Stack:");
    for(pos=0;pos<=top;pos++)
    {
        printf(" %s",nodeNames[stackData[pos]]);
    }
    printf("\n");
}

void runDfs(int startIndex)
{
    int top=-1;
    int current,next,orderPos=0;

    stackData[++top]=startIndex;
    visitMark[startIndex]=1;

    printf("\nStep-by-step DFS traversal:\n\n");

    while(top>=0)
    {
        current=stackData[top--];
        dfsOrder[orderPos++]=current;

        printf("Visited: %s\n\n",nodeNames[current]);

        for(next=totalNodes-1;next>=0;next--)
        {
            if(graphMat[current][next]!=0 && !visitMark[next])
            {
                visitMark[next]=1;
                stackData[++top]=next;
                printf("  %s --> %s (edge exists, pushing to stack)\n\n",nodeNames[current],nodeNames[next]);
            }
        }

        printStackState(top);
    }

    printf("\nFinal DFS Traversal Order:\n\n");
    for(current=0;current<orderPos;current++)
    {
        printf("%s",nodeNames[dfsOrder[current]]);
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
    runDfs(startIndex);

    return 0;
}
