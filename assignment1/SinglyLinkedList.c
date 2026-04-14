#include <stdio.h>
#include <stdlib.h>
/*Abhijit Prasad Mallick
20252501001*/
void display();
void traverse();
void create();
void search();
void delete();
void insert();
struct Node
{
    int data;
    struct Node *next;
};
struct Node *head=NULL;
void traverse()
{
    struct Node *temp=head;
    if(head==NULL)
    {
        printf("empty list");
        return ;
    }
    while(temp!=NULL)
    {
        printf("%d->",temp->data);
        temp=temp->next;
    }
    printf("NULL");
}
void create()
{
    struct Node *nnode,*temp;
    int n;
    scanf("%d",&n);
    if(n<=0)
    {
        printf(" invalid size");
        return ;
    }
    int i;
    for(i=0;i<n;i++)
    {
        nnode=(struct Node*)malloc(sizeof(struct Node));
        scanf("%d",&nnode->data);
        nnode->next=NULL;
        if(head==NULL){
        head=nnode;
        temp=nnode;
    }
    else
    {
        temp->next=nnode;
        temp=nnode;
    }
    }
}
void delete()
{
    struct Node *temp,*prev=NULL;
    int val;
    if(head == NULL){
        printf("List is empty!\n");
        return;
    }
    printf("Before Delete ");
    display();
    scanf("%d", &val);
    temp = head;
    if(temp->data==val)
    {
        head=temp->next;
        printf("\nNode with value %d deleted.\n",temp->data);
        free(temp);
        printf("After Delete ");
        display();
        return;
    }
    while(temp!=NULL && temp->data!=val)
    {
        prev=temp;
        temp=temp->next;
    }
    if(temp==NULL)
    {
        printf("\nValue not found!\n");
        printf("After Delete ");
        display();
        return;
    }
    prev->next=temp->next;
    printf("\nNode with value %d deleted.\n", temp->data);
    free(temp);
    printf("After Delete ");
    display();
}
void search()
{
    struct Node *temp=head;
    int ele,pos=1;
    if(head==NULL){
        printf("List is empty\n");
        return;
    }
    printf("Enter the element:");
    scanf("%d", &ele);
    while(temp!=NULL)
    {
        if(temp->data==ele)
        {
            display();
            printf("\nElement %d found at position %d.\n", ele, pos);
            return;
        }
        temp=temp->next;
        pos++;
    }
    display();
    printf("\nElement %d not found in the list.\n",ele);
}
void display()
{
    struct Node *temp=head;    
    if(head==NULL)
    {    
        printf("Linked List: NULL\n");
        return ;
    }
    printf("Linked List:");
    while(temp!=NULL)
    {
        printf(" %d -> ",temp->data);
        temp=temp->next;
    }
    printf("NULL\n");
}
void insert()
{
    struct Node *nnode;
    printf("Before insertion ");
    display();
    nnode=(struct Node*)malloc(sizeof(struct Node));
    scanf("%d",&nnode->data);
    nnode->next=head;
    head=nnode;
    printf("After insertion ");
    display();
}
int main()
{
    int j;
    int k=3;
    printf("1.Create\n");
    printf("2.Delete\n");
    printf("3.Search\n");
    printf("4.Insert\n");
    printf("5.Display\n");
    printf("6.Traverse\n");
    printf("Enter your choice:\n");
    while(k--)
    {
        scanf("%d",&j);
        switch(j)
        {
            case 1:
                create();
                break;
            case 2:
                delete();
                return 0;;
            case 5:
                display();
                return 0;
            case 3:
                search();
                break;
            case 4:
                insert();
                break;
            case 6:
                traverse();
                break;
            default:
                printf("not a valid choice");
                return 0;
        }
    }
}