#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 100
#define NAME_LEN 50
/*Abhijit Prasad Mallick
20252501001*/
typedef struct Node
{
    int dest;
    int wght;
    struct Node*next;
}Node;

int fndvrtx(char nm[]);
int isnum(char s[]);
int getwght(int src,int dest);
void inorup(int src,int dest,int wght);
void rmedgeind(int src,int dest);
int edgind(int src,int dest);
void frlst(Node*head);
void prtrw(int i);
void dispgrph();
void advrtx();
void adedg();
void rmvrtx();
void rmedg();
void chckedge();
void findNeighbors();
void inigrph();

char vrtcs[MAX][NAME_LEN];
Node*adj[MAX];
int n=0;

void inigrph()
{
    int i,j,wght;
    for(i=0;i<MAX;i++)
    {
        adj[i]=NULL;
    }
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%s",vrtcs[i]);
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(i!=j)
            {
                scanf("%d",&wght);
                if(wght!=0)
                {
                    inorup(i,j,wght);
                }
            }
        }
    }
}
int isnum(char s[])
{
    int i=0;
    if(s[0]=='\0')
        return 0;
    if(s[0]=='-' && s[1]!='\0')
        i=1;
    for(;s[i]!='\0';i++)
        if(!isdigit((unsigned char)s[i]))
            return 0;
    return 1;
}
void findNeighbors()
{
    char nm[NAME_LEN];
    int idx,j,w;
    if(scanf("%s",nm)!=1)
    {
        return;
    }
    idx=fndvrtx(nm);
    if(idx==-1)
    {
        return;
    }
    printf("Neighbors of %s:",nm);
    if(idx==0)
    {
        if(n>1)
        {
            w=getwght(idx,1);
            if(w!=0)
            {
                printf(" %s(%d)",vrtcs[1],w);
            }
        }
        for(j=n-1;j>=2;j--)
        {
            w=getwght(idx,j);
            if(w!=0)
            {
                printf(" %s(%d)",vrtcs[j],w);
            }
        }
    }
    else
    {
        for(j=n-1;j>=0;j--)
        {
            if(j!=idx)
            {
                w=getwght(idx,j);
                if(w!=0)
                {
                    printf(" %s(%d)",vrtcs[j],w);
                }
            }
        }
    }
    printf("\n");
}
void chckedge()
{
    char sname[NAME_LEN],dname[NAME_LEN];
    int src,dest;
    if(scanf("%s",sname)!=1)
    {
        return;
    }
    if(scanf("%s",dname)!=1)
    {
        return;
    }
    src=fndvrtx(sname);
    dest=fndvrtx(dname);
    if(src==-1 || dest==-1)
    {
        return;
    }
    if(edgind(src,dest))
    {
        printf("Exists\n");
    }
    else
    {
        printf("Not Exists\n");
    }
}
void rmvrtx()
{
    char nm[NAME_LEN];
    int idx,i;
    Node*temp;
    Node*curr;
    Node*prev;
    if(scanf("%s",nm)!=1)
    {
        return;
    }
    idx=fndvrtx(nm);
    if(idx==-1)
    {
        return;
    }
    printf("Before removing Vertex from Graph:\n");
    dispgrph();
    frlst(adj[idx]);
    for(i=idx;i<n-1;i++)
    {
        adj[i]=adj[i+1];
        strcpy(vrtcs[i],vrtcs[i+1]);
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
    dispgrph();
}
Node*createNode(int dest,int wght)
{
    Node*nnode=(Node*)malloc(sizeof(Node));
    nnode->dest=dest;
    nnode->wght=wght;
    nnode->next=NULL;
    return nnode;
}
int fndvrtx(char nm[])
{
    int i;
    for(i=0;i<n;i++)
        if(strcmp(vrtcs[i],nm)==0)
            return i;
    return -1;
}
void rmedgeind(int src,int dest)
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
void dispgrph()
{
    int i;
    printf("Graph Structure:\n");
    for(i=0;i<n;i++)
    {
        prtrw(i);
    }
}
void rmedg()
{
    char sname[NAME_LEN],dname[NAME_LEN];
    int src,dest;
    if(scanf("%s",sname)!=1)
    {
        return;
    }
    if(scanf("%s",dname)!=1)
    {
        return;
    }
    src=fndvrtx(sname);
    dest=fndvrtx(dname);
    if(src==-1 || dest==-1)
    {
        return;
    }
    printf("Before removing edge from Graph:\n");
    dispgrph();
    rmedgeind(src,dest);
    printf("after removing edge from Graph:\n");
    dispgrph();
}
void prtrw(int i)
{
    int j,w;
    printf("%s:",vrtcs[i]);
    if(i==0)
    {
        if(n>1)
        {
            w=getwght(i,1);
            if(w!=0)
            {
                printf(" -> %s(%d)",vrtcs[1],w);
            }
        }
        for(j=n-1;j>=2;j--)
        {
            if(j!=i)
            {
                w=getwght(i,j);
                if(w!=0)
                {
                    printf(" -> %s(%d)",vrtcs[j],w);
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
                w=getwght(i,j);
                if(w!=0)
                {
                    printf(" -> %s(%d)",vrtcs[j],w);
                }
            }
        }
    }
    printf("\n");
}
void adedg()
{
    char s1[NAME_LEN],s2[NAME_LEN];
    int src,dest,wght,i;
    if(scanf("%s",s1)!=1)
    {
        return;
    }
    if(scanf("%s",s2)!=1)
    {
        return;
    }
    src=fndvrtx(s1);
    if(src==-1)
    {
        return;
    }
    if(isnum(s2))
    {
        wght=atoi(s2);
        dest=-1;
        for(i=0;i<n;i++)
        {
            if(i!=src && !edgind(src,i))
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
        dest=fndvrtx(s2);
        wght=atoi(s3);
        if(dest==-1)
        {
            return;
        }
    }
    printf("Before adding Edge\n");
    dispgrph();
    inorup(src,dest,wght);
    printf("After adding Edge\n");
    dispgrph();
}
void frlst(Node*head)
{
    Node*temp;
    while(head!=NULL)
    {
        temp=head;
        head=head->next;
        free(temp);
    }
}
void inorup(int src,int dest,int wght)
{
    Node*temp=adj[src];
    while(temp!=NULL)
    {
        if(temp->dest==dest)
        {
            temp->wght=wght;
            return;
        }
        temp=temp->next;
    }
    Node*nnode=createNode(dest,wght);
    nnode->next=adj[src];
    adj[src]=nnode;
}
int edgind(int src,int dest)
{
    return getwght(src,dest)!=0;
}
int getwght(int src,int dest)
{
    Node*temp=adj[src];
    while(temp!=NULL)
    {
        if(temp->dest==dest)
            return temp->wght;
        temp=temp->next;
    }
    return 0;
}
void advrtx()
{
    char nm[NAME_LEN];
    if(scanf("%s",nm)!=1)
    {
        return;
    }
    printf("Before adding Vertex\n");
    dispgrph();
    if(fndvrtx(nm)==-1)
    {
        strcpy(vrtcs[n],nm);
        adj[n]=NULL;
        n++;
    }
    printf("After adding Vertex\n");
    dispgrph();
}
int main()
{
    int choice;
    int i;
    inigrph();
    if(scanf("%d",&choice)!=1)
    {
        dispgrph();
        for(i=0;i<n;i++)
        {
            frlst(adj[i]);
        }
        return 0;
    }
    switch(choice)
    {
        case 1:
            advrtx();
            break;
        case 2:
            adedg();
            break;
        case 3:
            rmvrtx();
            break;
        case 4:
            rmedg();
            break;
        case 5:
            chckedge();
            break;
        case 6:
            findNeighbors();
            break;
        case 7:
            dispgrph();
            break;
        case 8:
            break;
    }
    for(i=0;i<n;i++)
    {
        frlst(adj[i]);
    }
    return 0;
}