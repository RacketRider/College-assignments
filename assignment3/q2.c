#include <stdio.h>
#include <stdlib.h>
/*Abhijit Prasad Mallick
20252501001*/
struct Node {
    int data;
    struct Node *next;
};
struct Node *f=NULL;
struct Node *r=NULL;
void enqueue(int n);
void dequeue();
void display();
void isEmpty();
int main() 
{
    int ch;
    scanf("%d",&ch);
    if(ch==1) 
    {
        int n;
        scanf("%d",&n);
        enqueue(n);
        scanf("%d",&ch);
        if(ch==2) 
        {
            printf("Before Dequeue\n");
            display();
            printf("After Dequeue\n");
            dequeue();
        }
        else if(ch==3) 
        {
            display();
        }
        else if(ch==4) 
        {
            isEmpty();
        }
    }
    else if(ch==2) 
    {
        printf("Enter your choice: 2\n");
        printf("Before Dequeue\n");
        display();
        printf("After Dequeue\n");
        dequeue();
    }
    else if(ch==3) 
    {
        display();
    }
    else if(ch==4) 
    {
        isEmpty();
    }
    return 0;
}
void enqueue(int n) 
{
    int val;
    for(int i=0;i<n;i++) 
    {
        scanf("%d",&val);
        struct Node *temp=(struct Node *)malloc(sizeof(struct Node));
        temp->data=val;
        temp->next=NULL;
        if(r==NULL) 
            f=r=temp;
        else 
        {
            r->next=temp;
            r=temp;
        }
    }
}
void dequeue() 
{
    if(f==NULL) 
    {
        printf("Queue is empty. Cannot dequeue.\n");
        return;
    }
    struct Node *temp=f;
    printf("%d dequeued.\n",temp->data);
    f=f->next;
    free(temp);
    if(f==NULL)
        r=NULL;
    display();
}
void display() 
{
    if(f==NULL) 
    {
        printf("Queue is empty.\n");
        printf("Front Value: NULL\n");
        printf("Rear Value: NULL\n");
        return;
    }
    struct Node *temp=f;
    printf("Queue elements: ");
    while (temp!=NULL) {
        printf("%d ",temp->data);
        temp=temp->next;
    }
    printf("\n");
    printf("Front Value: %d\n",f->data);
    printf("Rear Value: %d\n",r->data);
}
void isEmpty() 
{
    if(f==NULL)
        printf("Queue is empty.\n");
    else
        printf("Queue is not empty.\n");
}
