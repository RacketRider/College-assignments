#include<stdio.h>
#include<stdlib.h>
#define Max 100
/*
Abhijit Prasad Mallick 
Roll No: 20252501001
*/
int heap[Max];
int n=0;

void insertElements();
void deleteRoot();
void search();
void printProperties();

void heapifyUp(int i);
void heapifyDown(int i);

void inorder(int i);
void preorder(int i);
void postorder(int i);

int height();
int isPerfect();

void heapifyUp(int i)
{
    int temp,parent;
    while(i>0)
    {
        parent=(i-1)/2;
        if(heap[parent]<heap[i])
        {
            temp=heap[parent];
            heap[parent]=heap[i];
            heap[i]=temp;
            i=parent;
        }
        else
            break;
    }
}

void heapifyDown(int i)
{
    int lt,rt,lrgst,temp;
    while(1)
    {
        lt=2*i+1;
        rt=2*i+2;
        lrgst=i;

        if(lt<n && heap[lt]>heap[lrgst])
            lrgst=lt;

        if(rt<n && heap[rt]>heap[lrgst])
            lrgst=rt;

        if(lrgst!=i)
        {
            temp=heap[i];
            heap[i]=heap[lrgst];
            heap[lrgst]=temp;
            i=lrgst;
        }
        else
            break;
    }
}

void insertElements()
{
    int m,i,val;
    scanf("%d",&m);

    for(i=0;i<m;i++)
    {
        scanf("%d",&val);
        heap[n]=val;
        heapifyUp(n);
        n++;
    }

    printf("Inorder Traversal: ");
    inorder(0);
    printf("\n");

    printf("Preorder Traversal: ");
    preorder(0);
    printf("\n");

    printf("Postorder Traversal: ");
    postorder(0);
    printf("\n");
}

void deleteRoot()
{
    int i;

    if(n==0)
        return;

    printf("Heap before deletion: ");
    for(i=0;i<n;i++)
        printf("%d ",heap[i]);
    printf("\n");

    heap[0]=heap[n-1];
    n--;

    if(n>0)
        heapifyDown(0);

    printf("Heap after deletion: ");
    for(i=0;i<n;i++)
        printf("%d ",heap[i]);
    printf("\n");

    printf("Inorder Traversal: ");
    inorder(0);
    printf("\n");

    printf("Preorder Traversal: ");
    preorder(0);
    printf("\n");

    printf("Postorder Traversal: ");
    postorder(0);
    printf("\n");
}

void search()
{
    int key,i,cmp=0,fnd=0;
    scanf("%d",&key);

    for(i=0;i<n;i++)
    {
        cmp++;
        if(heap[i]==key)
        {
            printf("Element found with %d comparisons\n",cmp);
            fnd=1;
            break;
        }
    }

    if(!fnd)
        printf("Element not found after %d comparisons\n",cmp);
}

int height()
{
    int h=-1;
    int nodes=1;
    int count=n;

    while(count>0)
    {
        h++;
        count=count-nodes;
        nodes=nodes*2;
    }
    return h;
}

int isPerfect()
{
    int x=n+1;
    while(x%2==0)
        x=x/2;

    if(x==1)
        return 1;
    else
        return 0;
}

void printProperties()
{
    printf("Heap Size: %d\n",n);
    printf("Heap Height: %d\n",height());

    if(isPerfect())
        printf("Tree Type: Perfect Binary Tree\n");
    else
        printf("Tree Type: Complete Binary Tree\n");
}

void inorder(int i)
{
    if(i<n)
    {
        inorder(2*i+1);
        printf("%d ",heap[i]);
        inorder(2*i+2);
    }
}

void preorder(int i)
{
    if(i<n)
    {
        printf("%d ",heap[i]);
        preorder(2*i+1);
        preorder(2*i+2);
    }
}

void postorder(int i)
{
    if(i<n)
    {
        postorder(2*i+1);
        postorder(2*i+2);
        printf("%d ",heap[i]);
    }
}

int main()
{
    int ch;

    while(scanf("%d",&ch)==1)
    {
        switch(ch)
        {
            case 1:
                insertElements();
                break;

            case 2:
                deleteRoot();
                break;

            case 3:
                search();
                break;

            case 4:
                printProperties();
                break;

            case 5:
                return 0;
        }
    }

    return 0;
}