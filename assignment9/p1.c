#include <stdio.h>
#include <string.h>

#define MAX 100
#define NAME_LEN 50
/*Abhijit Prasad Mallick
20252501001*/
char verti[MAX][NAME_LEN];
int grph[MAX][MAX];
int n;

void dispgraph();
void advrtx();
void addEdge();
void rmvrtx();
void rmedge();
void chckedgexst();
void fndneighbours();
int fndvrtxindx(char name[]);
void fndneighbours()
{
    char vertex[NAME_LEN];
    int idx;
    int i,found=0;
    printf("Enter vertex name: ");
    scanf("%s",vertex);
    idx=fndvrtxindx(vertex);
    if(idx==-1)
    {
        printf("Vertex '%s' not found.\n",vertex);
        return;
    }
    printf("Neighbors of '%s': ",vertex);
    for(i=0;i<n;i++)
    {
        if(grph[idx][i]!=0)
        {
            printf("%s(%d) ",verti[i],grph[idx][i]);
            found=1;
        }
    }
    if(!found)
    {
        printf("No neighbors");
    }
    printf("\n");
}
void chckedgexst()
{
    char v1[NAME_LEN],v2[NAME_LEN];
    int i,j;
    printf("Enter vertex 1: ");
    scanf("%s",v1);
    printf("Enter vertex 2: ");
    scanf("%s",v2);
    i=fndvrtxindx(v1);
    j=fndvrtxindx(v2);
    if(i==-1 || j==-1)
    {
        printf("One or both verti not found.\n");
        return;
    }
    if(grph[i][j]!=0)
    {
        printf("Edge exists between '%s' and '%s' with weight %d.\n",v1,v2,grph[i][j]);
    }
    else
    {
        printf("No edge exists between '%s' and '%s'.\n",v1,v2);
    }
}
void rmedge()
{
    char v1[NAME_LEN],v2[NAME_LEN];
    int i,j;
    printf("Enter vertex 1: ");
    scanf("%s",v1);
    printf("Enter vertex 2: ");
    scanf("%s",v2);
    i=fndvrtxindx(v1);
    j=fndvrtxindx(v2);
    if(i==-1 || j==-1)
    {
        printf("One or both verti not found.\n");
        return;
    }
    printf("Before removing edge between %s-->%s Old Matrix is\n",v1,v2);
    dispgraph();
    grph[i][j]=0;
    grph[j][i]=0;
    printf("Edge removed between '%s' and '%s'.\n",v1,v2);
    printf("After removing edge between %s-->%s New Matrix is\n",v1,v2);
    dispgraph();
}
void advrtx()
{
    char nvrtx[NAME_LEN];
    int i;
    printf("Enter new vertex name: ");
    scanf("%s",nvrtx);
    if(fndvrtxindx(nvrtx)!=-1)
    {
        printf("Vertex '%s' already exists.\n",nvrtx);
        return;
    }
    printf("Before Vertex %s Adding Old Matrix is\n",nvrtx);
    dispgraph();
    strcpy(verti[n],nvrtx);
    for(i=0;i<=n;i++)
    {
        grph[n][i]=0;
        grph[i][n]=0;
    }
    n++;
    printf("Vertex '%s' added.\n",nvrtx);
    printf("After Vertex %s Adding New Matrix is\n",nvrtx);
    dispgraph();
}

void dispgraph()
{
    int i,j;
    printf("\nAdjacency Matrix (weights):\n\n");
    printf("%-5s","");
    for(i=0;i<n;i++)
    {
        printf("%-5s",verti[i]);
    }
    printf("\n");
    for(i=0;i<n;i++)
    {
        printf("%-5s",verti[i]);
        for(j=0;j<n;j++)
        {
            printf("%-5d",grph[i][j]);
        }
        printf("\n");
    }
}



void addEdge()
{
    char v1[NAME_LEN],v2[NAME_LEN];
    int weight;
    int i,j;
    printf("Enter vertex 1: ");
    scanf("%s",v1);
    printf("Enter vertex 2: ");
    scanf("%s",v2);
    printf("Enter weight: ");
    scanf("%d",&weight);
    i=fndvrtxindx(v1);
    j=fndvrtxindx(v2);
    if(i==-1 || j==-1)
    {
        printf("One or both verti not found.\n");
        return;
    }
    printf("Before adding edge between %s-->%s with %d Old Matrix is\n",v1,v2,weight);
    dispgraph();
    grph[i][j]=weight;
    grph[j][i]=weight;
    printf("Edge added between '%s' and '%s' with weight %d.\n",v1,v2,weight);
    printf("After adding edge between %s-->%s with %d New Matrix is\n",v1,v2,weight);
    dispgraph();
}

void rmvrtx()
{
    char vertex[NAME_LEN];
    int idx;
    int i,j;
    printf("Enter vertex name to remove: ");
    scanf("%s",vertex);
    idx=fndvrtxindx(vertex);
    if(idx==-1)
    {
        printf("Vertex '%s' not found.\n",vertex);
        return;
    }
    printf("Before Vertex %s Removing Old Matrix is\n",vertex);
    dispgraph();
    for(i=idx;i<n-1;i++)
    {
        for(j=0;j<n;j++)
        {
            grph[i][j]=grph[i+1][j];
        }
    }
    for(j=idx;j<n-1;j++)
    {
        for(i=0;i<n-1;i++)
        {
            grph[i][j]=grph[i][j+1];
        }
    }
    for(i=idx;i<n-1;i++)
    {
        strcpy(verti[i],verti[i+1]);
    }
    n--;
    printf("Vertex '%s' removed.\n",vertex);
    printf("After Vertex %s Removing New Matrix is\n",vertex);
    dispgraph();
}

int fndvrtxindx(char name[])
{
    int i;
    for(i=0;i<n;i++)
    {
        if(strcmp(verti[i],name)==0)
        {
            return i;
        }
    }
    return -1;
}





int main()
{
    int choice;
    int i,j,w;
    printf("===== GRAPH MENU =====\n\n");
    printf("1. Add Vertex\n\n");
    printf("2. Add Edge\n\n");
    printf("3. Remove Vertex\n\n");
    printf("4. Remove Edge\n\n");
    printf("5. Check Edge Existence\n\n");
    printf("6. Find Neighbors\n\n");
    printf("7. Display Graph\n\n");
    printf("0. Exit\n\n");
    printf("======================\n\n");
    printf("Enter number of verti: ");
    scanf("%d",&n);
    printf("Enter names of the verti:\n");
    for(i=0;i<n;i++)
    {
        scanf("%s",verti[i]);
    }
    for(i=0;i<MAX;i++)
    {
        for(j=0;j<MAX;j++)
        {
            grph[i][j]=0;
        }
    }
    printf("Enter weights between each pair (0 if no edge):\n");
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            printf("Weight between %s and %s: ",verti[i],verti[j]);
            scanf("%d",&w);
            grph[i][j]=w;
            grph[j][i]=w;
        }
    }
    while(scanf("%d",&choice)==1)
    {
        printf("\nEnter choice: ");
        scanf("%d",&choice);
        printf("\n");
        switch(choice)
        {
            case 1:
                advrtx();
                break;
            case 2:
                addEdge();
                break;
            case 3:
                rmvrtx();
                break;
            case 4:
                rmedge();
                break;
            case 5:
                chckedgexst();
                break;
            case 6:
                fndneighbours();
                break;
            case 7:
                dispgraph();
                break;
            case 0:
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}
