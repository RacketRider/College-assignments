#include <stdio.h>
#include <stdlib.h>
struct node 
{
    int data;
    struct node *next;
};
struct node *head = NULL;
void create();
void insert();
void deletion();
void search();
void display();
/*Abhijit Prasad Mallick 
20252501001*/
void create() 
{
    int n,i,ele;
    struct node *temp,*nnode;
    head=NULL;
    printf("Enter number of elements: ");
    scanf("%d",&n);
    for (i=0;i<n;i++) 
    {
        nnode=(struct node *)malloc(sizeof(struct node));
        printf("Enter element %d:",i+1);
        scanf("%d",&ele);
        nnode->data=ele;
        nnode->next=NULL;
        if(head==NULL) 
        {
            head=nnode;
            temp=head;
        } 
        else 
        {
            temp->next=nnode;
            temp=nnode;
        }
    }
}
void insert()
{
    int ele;
    struct node *nnode;
    scanf("%d",&ele); 
    printf("Before insertion ");
    display();
    nnode=(struct node *)malloc(sizeof(struct node));
    nnode->data=ele;
    nnode->next=head;
    head=nnode;
    printf("After insertion ");
    display();
}

void deletion()
{
    int key;
    struct node *temp=head,*prev=NULL;
    scanf("%d",&key);
    if(head==NULL)
        return;
    printf("Before Delete ");
    display();
    if(head->data==key)
    {
        temp=head;
        head=head->next;
        free(temp);
        printf("Node with value %d deleted.\n", key);
        printf("After Delete ");
        display();
        return;
    }
    while(temp!=NULL && temp->data!=key)
    {
        prev=temp;
        temp=temp->next;
    }
    if(temp==NULL)
        return;
    prev->next=temp->next;
    free(temp);
    printf("Node with value %d deleted.\n", key);
    printf("After Delete ");
    display();
}

void search() 
{
    int key,pos=1;
    struct node *temp=head;
    if(head==NULL) 
    {
        printf("List is empty.\n");
        return;
    }
    printf("Enter element to search: ");
    scanf("%d",&key);
    display();
    while(temp!=NULL) 
    {
        if(temp->data==key) 
        {
            printf("Element %d found at position %d.\n",key,pos);
            return;
        }
        temp=temp->next;
        pos++;
    }
    printf("Element %d not found in the list.\n",key);
}
void display()
{
    struct node *temp=head;
    if(head==NULL)
    {
        printf("Linked List: NULL\n");
        return;
    }
    printf("Linked List: ");
    while(temp!=NULL)
    {
        printf("%d -> ",temp->data);
        temp=temp->next;
    }
    printf("NULL\n");
}
int main()
{
    int t=6;
    int ch;
    while (t--)
    {
        scanf("%d", &ch);
        switch (ch)
    {
        case 1:
            create();      
            break;
        case 2:
            deletion();
            break;
        case 3:
            search();
            break;
        case 4:
            insert();
            break;
        case 5:
            display();
            break;
        case 6:           
            display();
            break;
        case 7:
            return 0;
}

    }
}
