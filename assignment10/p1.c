#include <stdio.h>
#include <string.h>
/*Abhijit Prasad Mallick
20252501001*/
#define MAX_NODES 100
#define NAME_LEN 50

char nnms[MAX_NODES][NAME_LEN];
int grphmt[MAX_NODES][MAX_NODES];
int qudat[MAX_NODES];
int vstmrk[MAX_NODES];
int bfsOrder[MAX_NODES];
int totnod;
int fndndind(char key[]);
void prntmtrx();
void prntqust(int frnt,int rear);
void bfsrnr(int startIndex);
void prntqust(int frnt,int rear)
{
    int pos;
    printf("  Queue:");
    for(pos=frnt;pos<=rear;pos++)
    {
        printf(" %s",nnms[qudat[pos]]);
    }
    printf("\n");
}
void prntmtrx()
{
    int row,col;
    printf("Adjacency Matrix:\n\n");
    printf("%-5s","");
    for(col=0;col<totnod;col++)
    {
        printf("%-5s",nnms[col]);
    }
    printf("\n");
    for(row=0;row<totnod;row++)
    {
        printf("%-5s",nnms[row]);
        for(col=0;col<totnod;col++)
        {
            printf("%-5d",grphmt[row][col]);
        }
        printf("\n");
    }
}
void bfsrnr(int startIndex)
{
    int frnt=0,rear=-1;
    int crrnt,next,orderPos=0;

    qudat[++rear]=startIndex;
    vstmrk[startIndex]=1;

    printf("\nStep-by-step BFS traversal:\n\n");

    while(frnt<=rear)
    {
        crrnt=qudat[frnt++];
        bfsOrder[orderPos++]=crrnt;

        printf("Visited: %s\n\n",nnms[crrnt]);

        for(next=0;next<totnod;next++)
        {
            if(grphmt[crrnt][next]!=0 && !vstmrk[next])
            {
                vstmrk[next]=1;
                qudat[++rear]=next;
                printf("  %s --> %s (edge exists, enqueueing)\n\n",nnms[crrnt],nnms[next]);
            }
        }

        prntqust(frnt,rear);
    }

    printf("\nFinal BFS Traversal Order:\n\n");
    for(crrnt=0;crrnt<orderPos;crrnt++)
    {
        printf("%s",nnms[bfsOrder[crrnt]]);
        if(crrnt<orderPos-1)
        {
            printf(" ");
        }
    }
    printf("\n\nTime Complexity: O(V + E)\n\n");
    printf("Space Complexity: O(V)\n");
}
int fndndind(char key[])
{
    int idx;
    for(idx=0;idx<totnod;idx++)
    {
        if(strcmp(nnms[idx],key)==0)
        {
            return idx;
        }
    }
    return -1;
}
int main()
{
    int row,col,startIndex;
    char startName[NAME_LEN];

    scanf("%d",&totnod);

    for(row=0;row<totnod;row++)
    {
        scanf("%s",nnms[row]);
    }

    for(row=0;row<totnod;row++)
    {
        for(col=0;col<totnod;col++)
        {
            scanf("%d",&grphmt[row][col]);
        }
    }

    scanf("%s",startName);
    startIndex=fndndind(startName);

    prntmtrx();
    bfsrnr(startIndex);

    return 0;
}