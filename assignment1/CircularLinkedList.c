#include <stdio.h>
#include <stdlib.h>
struct node 
{
    int data;
    struct node *prev;
    struct node *next;
};
struct node *head=NULL;
void create();
void display(char dir);
void search(int val);
void insert(int pos, int val);
void traverse(int val, char dir);
void deletion(int val);
/*Abhijit Prasad Mallick
20252501001*/
int main() 
{
    int ch,t=3,val,pos;
    char dir;
    printf("\n--- CDLL MENU ---\n");
    printf("1. Create\n2. Delete\n3. Insert\n4. Display\n5. Search\n6. Traverse\n7. Exit\n");
    printf("Enter your choice: ");
    while(t--) 
    {
        scanf("%d",&ch);
        switch(ch) 
        {
            case 1:
                create();
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d",&val);
                deletion(val);
                return 0;   
            case 3:
                printf("Enter position to insert: ");
                scanf("%d",&pos);
                printf("Enter value to insert: ");
                scanf("%d",&val);
                insert(pos,val);
                break;
            case 4:
                printf("Enter direction (F/B): ");
                scanf(" %c",&dir);
                display(dir);
                break;
            case 5:
                printf("Enter value to search: ");
                scanf("%d",&val);
                search(val);
                break;
            case 6:
                printf("Enter value to start traversal: ");
                scanf("%d",&val);
                printf("Enter direction (F/B): ");
                scanf(" %c",&dir);
                traverse(val,dir);
                return 0;   
            case 7:
                exit(0);
        }
    }
    return 0;
}
void create() 
{
    int n,i,ele;
    struct node *temp,*nnode;
    head=NULL;
    printf("Enter number of elements: ");
    scanf("%d",&n);
    for(i=1;i<=n;i++) 
    {
        printf("Enter element %d: ",i);
        scanf("%d",&ele);
        nnode=(struct node*)malloc(sizeof(struct node));
        nnode->data=ele;
        if(head==NULL) 
        {
            nnode->next=nnode->prev=nnode;
            head=nnode;
        } 
        else 
        {
            temp=head->prev;
            temp->next=nnode;
            nnode->prev=temp;
            nnode->next=head;
            head->prev=nnode;
        }
    }
}
void display(char dir) 
{
    struct node *temp;
    if(head==NULL) 
    {
        printf("The list is empty.\n");
        return;
    }
    if(dir=='F' || dir=='f') 
    {
        printf("List (Forward): ");
        temp=head;
        do 
        {
            printf("%d", temp->data);
            temp=temp->next;
            if(temp!=head) 
                printf(" <-> ");
        } 
        while(temp!=head);
        printf(" <-> (back to head)\n");
    } 
    else if(dir=='B' || dir=='b') 
    {
        printf("List (Backward): ");
        temp=head->prev;
        struct node *start=temp;
        do 
        {
            printf("%d",temp->data);
            temp=temp->prev;
            if(temp!=start) printf(" <-> ");
        } 
        while(temp!=start);
        printf(" <-> (back to head)\n");
    } 
    else 
        printf("Invalid direction!\n");
}
void search(int val) 
{
    struct node *temp=head;
    int pos=1,fnd=0;
    if(head==NULL) 
    {
        printf("The list is empty.\n");
        return;
    }
    do 
    {
        if(temp->data==val) 
        {
            printf("Node with value %d found at position %d.\n", val, pos);
            fnd=1;
        }
        temp=temp->next;
        pos++;
    } 
    while(temp!=head);
    if(!fnd) 
        printf("Node with value %d not found.\n", val);
}
void insert(int pos,int val) 
{
    struct node *nnode,*temp;
    int i;
    if(pos<1) 
    {
        printf("Invalid position\n");
        return;
    }
    nnode=(struct node*)malloc(sizeof(struct node));
    nnode->data=val;
    if(head==NULL) 
    {
        if(pos!=1) 
        {
            printf("Invalid position\n");
            free(nnode);
            return;
        }
        nnode->next=nnode->prev=nnode;
        head=nnode;
        return;
    }
    if(pos==1) 
    {
        temp=head->prev;
        nnode->next=head;
        nnode->prev=temp;
        temp->next=nnode;
        head->prev=nnode;
        head=nnode;
        return;
    }
    temp=head;
    for(i=1;i<pos-1;i++) 
    {
        temp=temp->next;
        if(temp==head) 
            break;
    }
    if(i!=pos-1) 
    {
        printf("Invalid position\n");
        free(nnode);
        return;
    }
    nnode->next=temp->next;
    nnode->prev=temp;
    temp->next->prev=nnode;
    temp->next=nnode;
}
void traverse(int val,char dir) 
{
    struct node *temp=head,*first=NULL,*second=NULL;
    if(head==NULL) 
    {
        printf("\nThe list is empty.\n");
        return;
    }
    do 
    {
        if(temp->data==val) 
        {
            if(first==NULL)
                first=temp;
            else 
            {
                second=temp;
                break;
            }
        }
        temp=temp->next;
    } 
    while(temp!=head);
    if(first==NULL) 
    {
        printf("\nNode with value %d not found.\n",val);
        return;
    }
    if(dir=='B' || dir=='b') 
    {
        printf("Traversing backward from value %d: ",val);
        temp=first;
        do 
        {
            printf("%d", temp->data);
            temp=temp->prev;
            if(temp!=first) printf("<->");
        } 
        while(temp!=first);
        printf("<->(back to head)\n");
        if(second!=NULL) 
        {
            printf("Traversing backward from value %d: ", val);
            temp=second;
            do 
            {
                printf("%d", temp->data);
                temp=temp->prev;
                if(temp!=second) printf("<->");
            } 
            while(temp!=second);
            printf("<->(back to head)\n");
        }
    }
    else if(dir=='F' || dir=='f') 
    {
        printf("Traversing forward from value %d: ", val);
        temp=first;
        do 
        {
            printf("%d", temp->data);
            temp=temp->next;
            if(temp!=first)
                printf("<->");
        } 
        while(temp!=first);
        printf("<->(back to head)\n");
        if(second!=NULL) 
        {
            printf("Traversing forward from value %d: ", val);
            temp=second;
            do 
            {
                printf("%d", temp->data);
                temp=temp->next;
                if(temp!=second) printf("<->");
            } 
            while(temp!=second);
            printf("<->(back to head)\n");
        }
    }
}
void deletion(int val) {
    struct node *temp=head,*target = NULL;
    int pos=1,foundPos=-1,i=1;
    if(head==NULL) 
    {
        printf("The list is empty.\n");
        return;
    }
    do 
    {
        if(temp->data==val) 
        {
            target=temp;
            foundPos=i;
        }
        temp=temp->next;
        i++;
    } 
    while(temp!=head);
    if(target==NULL) 
    {
        printf("Node with value %d not found.\n",val);
        return;
    }
    printf("\nKey %d found at position %d\n",val,foundPos);
    printf("Before deletion: ");
    temp=head;
    do 
    {
        printf("%d",temp->data);
        temp=temp->next;
        if(temp!=head) printf(" <-> ");
    } 
    while(temp!=head);
    printf(" <-> (back to head)\n");
    if(target->next==target) 
    {
        free(target);
        head=NULL;
        printf("\nNode with value %d deleted.\n", val);
        printf("After deletion: (back to head)\n");
        return;
    }
    target->prev->next=target->next;
    target->next->prev=target->prev;
    if(target==head)
        head=target->next;
    free(target);
    printf("Node with value %d deleted.\n", val);
    printf("After deletion: ");
    temp=head;
    do 
    {
        printf("%d", temp->data);
        temp=temp->next;
        if(temp!=head) 
            printf(" <-> ");
    } 
    while(temp!=head);
    printf(" <-> (back to head)\n");
}