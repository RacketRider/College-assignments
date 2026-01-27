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
    int pos,ele,i;
    struct node *nnode,*temp;
    nnode=(struct node *)malloc(sizeof(struct node));
    printf("Enter position to insert:");
    scanf("%d",&pos);
    printf("Enter element to insert:");
    scanf("%d",&ele);
    nnode->data=ele;
    if(pos==1) 
    {
        nnode->next=head;
        head=nnode;
        display();
        return;
    }
    temp=head;
    for(i=1;i<pos-1 && temp!=NULL;i++) 
        temp=temp->next;
    if (temp==NULL) 
    {
        printf("Invalid position!\n");
        free(nnode);
        return;
    }
    nnode->next=temp->next;
    temp->next=nnode;
    printf("Element inserted successfully.\n");
    display();
}
void deletion() 
{
    int pos,i;
    struct node *temp,*prev;
    if(head==NULL) 
    {
        printf("List is empty. Can't delete.\n");
        return;
    }
    printf("Enter position to delete: ");
    scanf("%d",&pos);
    if(pos==1) 
    {
        temp=head;
        head=head->next;
        free(temp);
        display();
        return;
    }
    temp=head;
    for(i=1;i<pos && temp!=NULL;i++) 
    {
        prev=temp;
        temp=temp->next;
    }
    if(temp==NULL) 
    {
        printf("Invalid position!\n");
        return;
    }
    prev->next=temp->next;
    free(temp);
    printf("Element deleted successfully.\n");
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
    printf("List elements: ");
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
        printf("\n--- SLL MENU ---\n");
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