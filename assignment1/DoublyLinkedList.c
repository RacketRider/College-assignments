#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node *prev;
    struct node *next;
};
struct node *head=NULL;
void create();
void insert();
void deletion();
void search();
void display();
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
        nnode->prev=NULL;
        nnode->next=NULL;
        if(head==NULL) 
        {
            head=nnode;
            temp=head;
        } 
        else 
        {
            temp->next=nnode;
            nnode->prev=temp;
            temp=nnode;
        }
    }
}
void insert() 
{
    int pos,ele,i;
    struct node *nnode,*temp;
    nnode=(struct node *)malloc(sizeof(struct node));
    printf("Enter position to insert:");
    scanf("%d",&pos);
    printf("Enter element to insert: ");
    scanf("%d",&ele);
    nnode->data=ele;
    if(pos==1) 
    {
        nnode->prev=NULL;
        nnode->next=head;
        if(head!=NULL)
            head->prev=nnode;
        head=nnode;
        display();
        return;
    }
    temp=head;
    for(i=1;i<pos-1 && temp!=NULL;i++) 
        temp=temp->next;
    if(temp==NULL) 
    {
        printf("Invalid position!\n");
        free(nnode);
        return;
    }
    nnode->next=temp->next;
    nnode->prev=temp;
    if(temp->next!=NULL)
        temp->next->prev=nnode;
    temp->next=nnode;
    printf("Element inserted successfully.\n");
    display();
}
void deletion() 
{
    int pos,i;
    struct node *temp;
    if(head==NULL) 
    {
        printf("List is empty. Can't delete.\n");
        return;
    }
    printf("Enter position to delete: ");
    scanf("%d",&pos);
    temp=head;
    if(pos==1) {
        head=temp->next;
        if(head!=NULL)
            head->prev=NULL;
        free(temp);
        display();
        return;
    }
    for(i=1;i<pos && temp!=NULL;i++) 
        temp=temp->next;
    if(temp==NULL) 
    {
        printf("Invalid position!\n");
        return;
    }
    if(temp->next!=NULL)
        temp->next->prev=temp->prev;
    temp->prev->next=temp->next;
    free(temp);
    printf("Element deleted successfully.\n");
    display();
}
void search() 
{
    int se,pos=1;
    struct node *temp=head;
    if(head==NULL) 
    {
        printf("List is empty.\n");
        return;
    }
    printf("Enter element to search: ");
    scanf("%d",&se);
    while(temp!=NULL) 
    {
        if(temp->data==se) 
        {
            printf("Element %d found at position %d.\n",se,pos);
            return;
        }
        temp=temp->next;
        pos++;
    }
    printf("Element not found.\n");
}
void display() 
{
    struct node *temp=head;
    if(head==NULL) 
    {
        printf("List is empty.\n");
        return;
    }
    printf("List elements:");
    while(temp!=NULL) 
    {
        printf("%d ",temp->data);
        temp=temp->next;
    }
    printf("\n");
}
int main() 
{
    int ch;
    while(1) 
    {
        printf("\n--- DLL MENU ---\n");
        printf("1. Create\n");
        printf("2. Insert\n");
        printf("3. Delete\n");
        printf("4. Search\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&ch);
        switch(ch) 
        {
            case 1:
                create(); 
                break;
            case 2:
                insert(); 
                break;
            case 3:
                deletion(); 
                break;
            case 4: 
                search(); 
                break;
            case 5:
                display(); 
                break;
            case 6: 
                return 0;
            default: 
                printf("Invalid choice! Try again.\n");
        }
    }
}