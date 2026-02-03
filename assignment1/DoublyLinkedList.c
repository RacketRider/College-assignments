#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node *prev;
    struct node *next;
};
struct node *head=NULL;
void create();
void display(char);
void search(int);
void insert(int, int);
void traverse(int, char);
/*Abhijit Prasad Mallick 
20252501001*/
void deletion(int val) 
{
    struct node *temp=head;
    if(head==NULL)
        return;
    if(head->data==val) 
    {
        temp=head;
        head=head->next;
        if(head!=NULL)
            head->prev=NULL;
        free(temp);
        return;
    }
    while(temp!=NULL && temp->data!=val)
        temp=temp->next;
    if(temp==NULL)
        return;
    if(temp->next!=NULL)
        temp->next->prev=temp->prev;
    temp->prev->next=temp->next;
    free(temp);
}
void create() 
{
    int n, i;
    scanf("%d", &n);
    struct node *temp = NULL, *nnode;
    for(i=0;i<n;i++) 
    {
        nnode=(struct node*)malloc(sizeof(struct node));
        scanf("%d", &nnode->data);
        nnode->next=NULL;
        nnode->prev=NULL;
        if(head==NULL) 
        {
            head=nnode;
            temp=nnode;
        } 
        else 
        {
            temp->next=nnode;
            nnode->prev=temp;
            temp=nnode;
        }
    }
}
void display(char dir) 
{
    struct node *temp;
    if(head==NULL) 
    {
        printf("Linked List (Forward): NULL");
        return;
    }
    if(dir=='F') 
    {
        printf("Linked List (Forward): ");
        temp=head;
        while(temp!=NULL) 
        {
            printf("%d <-> ",temp->data);
            temp=temp->next;
        }
        printf("NULL");
    }
    else 
    {
        temp=head;
        while(temp->next!=NULL)
            temp = temp->next;
        printf("Linked List (Backward): ");
        while(temp!=NULL) 
        {
            printf("%d <-> ", temp->data);
            temp=temp->prev;
        }
        printf("NULL");
    }
}
void search(int key) {
    struct node *temp=head;
    int pos=1;
    while(temp!=NULL) 
    {
        if(temp->data==key) 
        {
            printf("Node with value %d found at position %d.", key, pos);
            return;
        }
        temp=temp->next;
        pos++;
    }
    printf("Node with value %d not found.",key);
}
void insert(int val,int pos) 
{
    struct node *temp=head,*nnode;
    int i=1;
    nnode=(struct node*)malloc(sizeof(struct node));
    nnode->data=val;
    nnode->next=NULL;
    nnode->prev=NULL;
    if(pos==1) 
    {
        nnode->next=head;
        if(head!=NULL)
            head->prev=nnode;
        head=nnode;
        return;
    }
    while(i<pos-1 && temp!=NULL) 
    {
        temp=temp->next;
        i++;
    }
    if(temp==NULL)
        return;
    nnode->next=temp->next;
    if(temp->next!=NULL)
        temp->next->prev=nnode;
    temp->next=nnode;
    nnode->prev=temp;
}
void traverse(int val,char dir) 
{
    struct node *temp=head;
    while(temp!=NULL && temp->data!=val)
        temp=temp->next;
    if(temp==NULL)
        return;
    if(dir=='F') 
    {
        printf("Traversal from element %d in F direction: ", val);
        while(temp!=NULL) 
        {
            printf("%d <-> ",temp->data);
            temp=temp->next;
        }
        printf("NULL");
    }
    else 
    {
        printf("Traversal from element %d in B direction: ", val);
        while(temp!=NULL) 
        {
            printf("%d <-> ",temp->data);
            temp=temp->prev;
        }
        printf("NULL");
    }
}
int main() 
{
    int ch;
    scanf("%d",&ch);     
    if(ch==1) 
    {
        create();         
        scanf("%d",&ch);  
        if(ch==2)        
        {
            int val;
            scanf("%d", &val);
            deletion(val);
            scanf("%d",&ch);
            if(ch==4) 
            {
                char d;
                scanf(" %c",&d);
                display(d);
            }
        }
        else if(ch==3)     
        {
            int val,pos;
            scanf("%d %d",&val,&pos);
            insert(val,pos);
            scanf("%d",&ch);
            if(ch==4) 
            {
                char d;
                scanf(" %c",&d);
                display(d);
            }
        }
        else if(ch==4)    
        {
            char d;
            scanf(" %c",&d);
            display(d);
        }
        else if(ch==5)     
        {
            int x;
            scanf("%d", &x);
            search(x);
        }
        else if(ch==6)   
        {
            int x;
            char d;
            scanf("%d %c", &x, &d);
            traverse(x, d);
        }
    }
    return 0;
}
