#include <stdio.h>
#include <stdlib.h>
struct node 
{
    int data;
    struct node *next;
};
struct node *last=NULL;
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
    struct node *newnode;
    last=NULL;
    printf("Enter number of elements: ");
    scanf("%d",&n);
    for(i=0;i<n;i++) 
    {
        newnode=(struct node *)malloc(sizeof(struct node));
        printf("Enter element %d: ",i+1);
        scanf("%d",&ele);
        newnode->data=ele;
        if(last==NULL) 
        {
            last=newnode;
            last->next=last;
        } 
        else 
        {
            newnode->next=last->next;
            last->next=newnode;
            last=newnode;
        }
    }
}
void insert() 
{
    int pos,ele,i;
    struct node *newnode,*temp;
    newnode=(struct node *)malloc(sizeof(struct node));
    printf("Enter position to insert: ");
    scanf("%d",&pos);
    printf("Enter element to insert: ");
    scanf("%d",&ele);
    newnode->data=ele;
    if(last==NULL) 
    {
        last=newnode;
        last->next=last;
        display();
        return;
    }
    temp=last->next;
    if(pos==1) 
    {
        newnode->next=temp;
        last->next=newnode;
        display();
        return;
    }
    for(i=1;i<pos-1 && temp->next!=last->next;i++)
        temp = temp->next;
    newnode->next=temp->next;
    temp->next=newnode;
    if(temp==last)
        last=newnode;
    printf("Element inserted successfully.\n");
    display();
}
void deletion() 
{
    int pos,i;
    struct node *temp,*prev;
    if(last==NULL) 
    {
        printf("List is empty. Can't delete.\n");
        return;
    }
    printf("Enter position to delete: ");
    scanf("%d",&pos);
    temp=last->next;
    if(pos==1) 
    {
        if(temp==last) 
        {
            free(temp);
            last=NULL;
        } 
        else 
        {
            last->next=temp->next;
            free(temp);
        }
        display();
        return;
    }
    for(i=1;i<pos && temp->next!=last->next;i++) 
    {
        prev=temp;
        temp=temp->next;
    }
    if(temp->next==last->next && i<pos) 
    {
        printf("Invalid position!\n");
        return;
    }
    prev->next=temp->next;
    if(temp==last)
        last=prev;
    free(temp);
    printf("Element deleted successfully.\n");
    display();
}
void search() 
{
    int key,pos=1;
    struct node *temp;
    if(last==NULL) 
    {
        printf("List is empty.\n");
        return;
    }
    printf("Enter element to search: ");
    scanf("%d",&key);
    temp=last->next;
    do 
    {
        if(temp->data==key)
        {
            printf("Element %d found at position %d.\n",key,pos);
            return;
        }
        temp=temp->next;
        pos++;
    } 
    while(temp!=last->next);
    printf("Element not found.\n");
}
void display() 
{
    struct node *temp;
    if(last==NULL) 
    {
        printf("List is empty.\n");
        return;
    }
    temp=last->next;
    printf("List elements: ");
    do 
    {
        printf("%d ", temp->data);
        temp=temp->next;
    } 
    while(temp!=last->next);
    printf("\n");
}
int main() 
{
    int ch;
    while(1) 
    {
        printf("\n--- CLL MENU ---\n");
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