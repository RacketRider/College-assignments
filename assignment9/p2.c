Program 	#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
#define NAME_LEN 50

typedef struct Node
{
    int dest;
    int weight;
    struct Node*next;
}Node;

char vertices[MAX][NAME_LEN];
Node*adj[MAX];
int n=0;

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

int isNumber(char s[])
{
    int i=0;
    if(s[0]=='\0')
    {
        return 0;
    }
    if(s[0]=='-' && s[1]!='\0')
    {
        i=1;
    }
    for(;s[i]!='\0';i++)
    {
        if(!isdigit((unsigned char)s[i]))
        {
            return 0;
        }
    }
    return 1;
}

Node*createNode(int dest,int weight)
{
    Node*newNode=(Node*)malloc(sizeof(Node));
    newNode->dest=dest;
    newNode->weight=weight;
    newNode->next=NULL;
    return newNode;
}

int getWeightByIndex(int src,int dest)
{
    Node*temp=adj[src];
    while(temp!=NULL)
    {
        if(temp->dest==dest)
        {
            return temp->weight;
        }
        temp=temp->next;
    }
    return 0;
}

void insertOrUpdateEdgeByIndex(int src,int dest,int weight)
{
    Node*temp=adj[src];
    while(temp!=NULL)
    {
        if(temp->dest==dest)
        {
            temp->weight=weight;
            return;
        }
        temp=temp->next;
    }
    Node*newNode=createNode(dest,weight);
    newNode->next=adj[src];
    adj[src]=newNode;
}

void removeEdgeByIndex(int src,int dest)
{
    Node*temp=adj[src];
    Node*prev=NULL;
    while(temp!=NULL)
    {
        if(temp->dest==dest)
        {
            if(prev==NULL)
            {
                adj[src]=temp->next;
            }
            else
            {
                prev->next=temp->next;
            }
            free(temp);
            return;
        }
        prev=temp;
        temp=temp->next;
    }
}

int edgeExistsByIndex(int src,int dest)
{
    return getWeightByIndex(src,dest)!=0;
}

void freeList(Node*head)
{
    Node*temp;
    while(head!=NULL)
    {
        temp=head;
        head=head->next;
        free(temp);
    }
}

void printRow(int i)
{
    int j,w;
    printf("%s:",vertices[i]);
    if(i==0)
    {
        if(n>1)
        {
            w=getWeightByIndex(i,1);
            if(w!=0)
            {
                printf(" -> %s(%d)",vertices[1],w);
            }
        }
        for(j=n-1;j>=2;j--)
        {
            if(j!=i)
            {
                w=getWeightByIndex(i,j);
                if(w!=0)
                {
                    printf(" -> %s(%d)",vertices[j],w);
                }
            }
        }
    }
    else
    {
        for(j=n-1;j>=0;j--)
        {
            if(j!=i)
            {
                w=getWeightByIndex(i,j);
                if(w!=0)
                {
                    printf(" -> %s(%d)",vertices[j],w);
                }
            }
        }
    }
    printf("\n");
}

void displayGraph()
{
    int i;
    printf("Graph Structure:\n");
    for(i=0;i<n;i++)
    {
        printRow(i);
    }
}

void addVertex()
{
    char name[NAME_LEN];
    if(scanf("%s",name)!=1)
    {
        return;
    }
    printf("Before adding Vertex\n");
    displayGraph();
    if(findVertexIndex(name)==-1)
    {
        strcpy(vertices[n],name);
        adj[n]=NULL;
        n++;
    }
    printf("After adding Vertex\n");
    displayGraph();
}

void addEdge()
{
    char s1[NAME_LEN],s2[NAME_LEN];
    int src,dest,weight,i;
    if(scanf("%s",s1)!=1)
    {
        return;
    }
    if(scanf("%s",s2)!=1)
    {
        return;
    }
    src=findVertexIndex(s1);
    if(src==-1)
    {
        return;
    }
    if(isNumber(s2))
    {
        weight=atoi(s2);
        dest=-1;
        for(i=0;i<n;i++)
        {
            if(i!=src && !edgeExistsByIndex(src,i))
            {
                dest=i;
                break;
            }
        }
        if(dest==-1)
        {
            return;
        }
    }
    else
    {
        char s3[NAME_LEN];
        if(scanf("%s",s3)!=1)
        {
            return;
        }
        dest=findVertexIndex(s2);
        weight=atoi(s3);
        if(dest==-1)
        {
            return;
        }
    }
    printf("Before adding Edge\n");
    displayGraph();
    insertOrUpdateEdgeByIndex(src,dest,weight);
    printf("After adding Edge\n");
    displayGraph();
}

void removeVertex()
{
    char name[NAME_LEN];
    int idx,i;
    Node*temp;
    Node*curr;
    Node*prev;
    if(scanf("%s",name)!=1)
    {
        return;
    }
    idx=findVertexIndex(name);
    if(idx==-1)
    {
        return;
    }
    printf("Before removing Vertex from Graph:\n");
    displayGraph();
    freeList(adj[idx]);
    for(i=idx;i<n-1;i++)
    {
        adj[i]=adj[i+1];
        strcpy(vertices[i],vertices[i+1]);
    }
    adj[n-1]=NULL;
    for(i=0;i<n-1;i++)
    {
        curr=adj[i];
        prev=NULL;
        while(curr!=NULL)
        {
            if(curr->dest==idx)
            {
                temp=curr;
                if(prev==NULL)
                {
                    adj[i]=curr->next;
                    curr=adj[i];
                }
                else
                {
                    prev->next=curr->next;
                    curr=prev->next;
                }
                free(temp);
            }
            else
            {
                if(curr->dest>idx)
                {
                    curr->dest=curr->dest-1;
                }
                prev=curr;
                curr=curr->next;
            }
        }
    }
    n--;
    printf("After removing Vertex from Graph:\n");
    displayGraph();
}

void removeEdge()
{
    char srcName[NAME_LEN],destName[NAME_LEN];
    int src,dest;
    if(scanf("%s",srcName)!=1)
    {
        return;
    }
    if(scanf("%s",destName)!=1)
    {
        return;
    }
    src=findVertexIndex(srcName);
    dest=findVertexIndex(destName);
    if(src==-1 || dest==-1)
    {
        return;
    }
    printf("Before removing edge from Graph:\n");
    displayGraph();
    removeEdgeByIndex(src,dest);
    printf("after removing edge from Graph:\n");
    displayGraph();
}

void checkEdge()
{
    char srcName[NAME_LEN],destName[NAME_LEN];
    int src,dest;
    if(scanf("%s",srcName)!=1)
    {
        return;
    }
    if(scanf("%s",destName)!=1)
    {
        return;
    }
    src=findVertexIndex(srcName);
    dest=findVertexIndex(destName);
    if(src==-1 || dest==-1)
    {
        return;
    }
    if(edgeExistsByIndex(src,dest))
    {
        printf("Exists\n");
    }
    else
    {
        printf("Not Exists\n");
    }
}

void findNeighbors()
{
    char name[NAME_LEN];
    int idx,j,w;
    if(scanf("%s",name)!=1)
    {
        return;
    }
    idx=findVertexIndex(name);
    if(idx==-1)
    {
        return;
    }
    printf("Neighbors of %s:",name);
    if(idx==0)
    {
        if(n>1)
        {
            w=getWeightByIndex(idx,1);
            if(w!=0)
            {
                printf(" %s(%d)",vertices[1],w);
            }
        }
        for(j=n-1;j>=2;j--)
        {
            w=getWeightByIndex(idx,j);
            if(w!=0)
            {
                printf(" %s(%d)",vertices[j],w);
            }
        }
    }
    else
    {
        for(j=n-1;j>=0;j--)
        {
            if(j!=idx)
            {
                w=getWeightByIndex(idx,j);
                if(w!=0)
                {
                    printf(" %s(%d)",vertices[j],w);
                }
            }
        }
    }
    printf("\n");
}

void initializeGraph()
{
    int i,j,weight;
    for(i=0;i<MAX;i++)
    {
        adj[i]=NULL;
    }
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%s",vertices[i]);
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(i!=j)
            {
                scanf("%d",&weight);
                if(weight!=0)
                {
                    insertOrUpdateEdgeByIndex(i,j,weight);
                }
            }
        }
    }
}

int main()
{
    int choice;
    int i;
    initializeGraph();
    if(scanf("%d",&choice)!=1)
    {
        displayGraph();
        for(i=0;i<n;i++)
        {
            freeList(adj[i]);
        }
        return 0;
    }
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
            checkEdge();
            break;
        case 6:
            findNeighbors();
            break;
        case 7:
            displayGraph();
            break;
        case 8:
            break;
    }
    for(i=0;i<n;i++)
    {
        freeList(adj[i]);
    }
    return 0;
}
