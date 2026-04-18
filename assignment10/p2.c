#include <stdio.h>
#include <string.h>
/*Abhijit Prasad Mallick
20252501001*/
#define MAX_NODES 100
#define NAME_LEN 50

char nodnms[MAX_NODES][NAME_LEN];
int grphmt[MAX_NODES][MAX_NODES];
int stckdat[MAX_NODES];
int vstmrk[MAX_NODES];
int dfsOrder[MAX_NODES];
int totnod;
int fndnodindx(char key[]);
void prntmtrx();
void prntstck(int top);
void rndfs(int startIndex);
void rndfs(int startIndex)
{
    int top=-1;
    int current,next,orderPos=0;

    stckdat[++top]=startIndex;
    vstmrk[startIndex]=1;

    printf("\nStep-by-step DFS traversal:\n\n");

    while(top>=0)
    {
        current=stckdat[top--];
        dfsOrder[orderPos++]=current;

        printf("Visited: %s\n\n",nodnms[current]);

        for(next=totnod-1;next>=0;next--)
        {
            if(grphmt[current][next]!=0 && !vstmrk[next])
            {
                vstmrk[next]=1;
                stckdat[++top]=next;
                printf("  %s --> %s (edge exists, pushing to stack)\n\n",nodnms[current],nodnms[next]);
            }
        }

        prntstck(top);
    }

    printf("\nFinal DFS Traversal Order:\n\n");
    for(current=0;current<orderPos;current++)
    {
        printf("%s",nodnms[dfsOrder[current]]);
        if(current<orderPos-1)
        {
            printf(" ");
        }
    }
    printf("\n\nTime Complexity: O(V + E)\n\n");
    printf("Space Complexity: O(V)\n");
}
void prntmtrx()
{
    int row,col;
    printf("Adjacency Matrix:\n\n");
    printf("%-5s","");
    for(col=0;col<totnod;col++)
    {
        printf("%-5s",nodnms[col]);
    }
    printf("\n");
    for(row=0;row<totnod;row++)
    {
        printf("%-5s",nodnms[row]);
        for(col=0;col<totnod;col++)
        {
            printf("%-5d",grphmt[row][col]);
        }
        printf("\n");
    }
}
void prntstck(int top)
{
    int pos;
    printf("  Stack:");
    for(pos=0;pos<=top;pos++)
    {
        printf(" %s",nodnms[stckdat[pos]]);
    }
    printf("\n");
}
int fndnodindx(char key[])
{
    int idx;
    for(idx=0;idx<totnod;idx++)
    {
        if(strcmp(nodnms[idx],key)==0)
        {
            return idx;
        }
    }
    return -1;
}
int main()
{
    int row,col,startIndex;
    char strtnm[NAME_LEN];

    scanf("%d",&totnod);

    for(row=0;row<totnod;row++)
    {
        scanf("%s",nodnms[row]);
    }

    for(row=0;row<totnod;row++)
    {
        for(col=0;col<totnod;col++)
        {
            scanf("%d",&grphmt[row][col]);
        }
    }

    scanf("%s",strtnm);
    startIndex=fndnodindx(strtnm);

    prntmtrx();
    rndfs(startIndex);

    return 0;
}







