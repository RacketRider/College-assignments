Program 	#include <stdio.h>
#include <string.h>

#define MAX 100
#define NAME_LEN 50

char vertices[MAX][NAME_LEN];
int graph[MAX][MAX];
int n;

int findVertexIndex(char name[])
{
    int i;
    for(i=0;i<n;i++)
    {
        if(strcmp(vertices[i],name)==0)
        {
            return i;
        }
    }
    return -1;
}

void displayGraph()
{
    int i,j;
    printf("\nAdjacency Matrix (weights):\n\n");
    printf("%-5s","");
    for(i=0;i<n;i++)
    {
        printf("%-5s",vertices[i]);
    }
    printf("\n");
    for(i=0;i<n;i++)
    {
        printf("%-5s",vertices[i]);
        for(j=0;j<n;j++)
        {
            printf("%-5d",graph[i][j]);
        }
        printf("\n");
    }
}

void addVertex()
{
    char newVertex[NAME_LEN];
    int i;
    printf("Enter new vertex name: ");
    scanf("%s",newVertex);
    if(findVertexIndex(newVertex)!=-1)
    {
        printf("Vertex '%s' already exists.\n",newVertex);
        return;
    }
    printf("Before Vertex %s Adding Old Matrix is\n",newVertex);
    displayGraph();
    strcpy(vertices[n],newVertex);
    for(i=0;i<=n;i++)
    {
        graph[n][i]=0;
        graph[i][n]=0;
    }
    n++;
    printf("Vertex '%s' added.\n",newVertex);
    printf("After Vertex %s Adding New Matrix is\n",newVertex);
    displayGraph();
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
    i=findVertexIndex(v1);
    j=findVertexIndex(v2);
    if(i==-1 || j==-1)
    {
        printf("One or both vertices not found.\n");
        return;
    }
    printf("Before adding edge between %s-->%s with %d Old Matrix is\n",v1,v2,weight);
    displayGraph();
    graph[i][j]=weight;
    graph[j][i]=weight;
    printf("Edge added between '%s' and '%s' with weight %d.\n",v1,v2,weight);
    printf("After adding edge between %s-->%s with %d New Matrix is\n",v1,v2,weight);
    displayGraph();
}

void removeVertex()
{
    char vertex[NAME_LEN];
    int idx;
    int i,j;
    printf("Enter vertex name to remove: ");
    scanf("%s",vertex);
    idx=findVertexIndex(vertex);
    if(idx==-1)
    {
        printf("Vertex '%s' not found.\n",vertex);
        return;
    }
    printf("Before Vertex %s Removing Old Matrix is\n",vertex);
    displayGraph();
    for(i=idx;i<n-1;i++)
    {
        for(j=0;j<n;j++)
        {
            graph[i][j]=graph[i+1][j];
        }
    }
    for(j=idx;j<n-1;j++)
    {
        for(i=0;i<n-1;i++)
        {
            graph[i][j]=graph[i][j+1];
        }
    }
    for(i=idx;i<n-1;i++)
    {
        strcpy(vertices[i],vertices[i+1]);
    }
    n--;
    printf("Vertex '%s' removed.\n",vertex);
    printf("After Vertex %s Removing New Matrix is\n",vertex);
    displayGraph();
}

void removeEdge()
{
    char v1[NAME_LEN],v2[NAME_LEN];
    int i,j;
    printf("Enter vertex 1: ");
    scanf("%s",v1);
    printf("Enter vertex 2: ");
    scanf("%s",v2);
    i=findVertexIndex(v1);
    j=findVertexIndex(v2);
    if(i==-1 || j==-1)
    {
        printf("One or both vertices not found.\n");
        return;
    }
    printf("Before removing edge between %s-->%s Old Matrix is\n",v1,v2);
    displayGraph();
    graph[i][j]=0;
    graph[j][i]=0;
    printf("Edge removed between '%s' and '%s'.\n",v1,v2);
    printf("After removing edge between %s-->%s New Matrix is\n",v1,v2);
    displayGraph();
}

void checkEdgeExistence()
{
    char v1[NAME_LEN],v2[NAME_LEN];
    int i,j;
    printf("Enter vertex 1: ");
    scanf("%s",v1);
    printf("Enter vertex 2: ");
    scanf("%s",v2);
    i=findVertexIndex(v1);
    j=findVertexIndex(v2);
    if(i==-1 || j==-1)
    {
        printf("One or both vertices not found.\n");
        return;
    }
    if(graph[i][j]!=0)
    {
        printf("Edge exists between '%s' and '%s' with weight %d.\n",v1,v2,graph[i][j]);
    }
    else
    {
        printf("No edge exists between '%s' and '%s'.\n",v1,v2);
    }
}

void findNeighbors()
{
    char vertex[NAME_LEN];
    int idx;
    int i,found=0;
    printf("Enter vertex name: ");
    scanf("%s",vertex);
    idx=findVertexIndex(vertex);
    if(idx==-1)
    {
        printf("Vertex '%s' not found.\n",vertex);
        return;
    }
    printf("Neighbors of '%s': ",vertex);
    for(i=0;i<n;i++)
    {
        if(graph[idx][i]!=0)
        {
            printf("%s(%d) ",vertices[i],graph[idx][i]);
            found=1;
        }
    }
    if(!found)
    {
        printf("No neighbors");
    }
    printf("\n");
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
    printf("Enter number of vertices: ");
    scanf("%d",&n);
    printf("Enter names of the vertices:\n");
    for(i=0;i<n;i++)
    {
        scanf("%s",vertices[i]);
    }
    for(i=0;i<MAX;i++)
    {
        for(j=0;j<MAX;j++)
        {
            graph[i][j]=0;
        }
    }
    printf("Enter weights between each pair (0 if no edge):\n");
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            printf("Weight between %s and %s: ",vertices[i],vertices[j]);
            scanf("%d",&w);
            graph[i][j]=w;
            graph[j][i]=w;
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
                addVertex();
                break;
            case 2:
                addEdge();
                break;
            case 3:
                removeVertex();
                break;
            case 4:
                removeEdge();
                break;
            case 5:
                checkEdgeExistence();
                break;
            case 6:
                findNeighbors();
                break;
            case 7:
                displayGraph();
                break;
            case 0:
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}
