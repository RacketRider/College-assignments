#include <stdio.h>
#include <stdlib.h>
/*Abhijit Prasad Mallick 
20252501001*/
struct node 
{
    int data;
    struct node *next;
};
struct node *top=NULL;
void create() 
{
    struct node *temp;
    while(top!=NULL) 
    {
        temp=top;
        top=top->next;
        free(temp);
    }
}
void push() 
{
    int x;
    struct node *n=(struct node *)malloc(sizeof(struct node));
    scanf("%d",&x);
    n->data=x;
    n->next=top;
    top=n;
}
void pop() 
{
    if(top==NULL) 
    {
        printf("Stack underflow! Cannot pop.\n");
        return;
    }
    struct node *temp=top;
    top=top->next;
    free(temp);
}
void peek() 
{
    if(top!=NULL) 
        printf("Top element: %d\n", top->data);
}
void size() 
{
    int ctr=0;
    struct node *temp=top;
    while(temp!=NULL) 
    {
        ctr++;
        temp=temp->next;
    }
    printf("Stack size: %d\n",ctr);
}
void isEmpty() 
{
    if(top==NULL)
        printf("Stack is empty.\n");
    else
        printf("Stack is not empty.\n");
}
void display() 
{
    if(top==NULL) 
    {
        printf("Stack is empty! Nothing to display.\n");
        return;
    }
    printf("Stack elements (top to bottom):\n");
    struct node *temp=top;
    while(temp!=NULL) 
    {
        printf("%d\n",temp->data);
        temp=temp->next;
    }
}
int main() 
{
    int ch,t=5;
    while(t--)
    {
        scanf("%d",&ch);
        switch(ch) 
        {
            case 1: 
                create(); 
                break;
            case 2: 
                push(); 
                break;
            case 3: 
                pop(); 
                break;
            case 4: 
                peek(); 
                break;
            case 5: 
                size(); 
                break;
            case 6: 
                isEmpty(); 
                break;
            case 7: 
                display(); 
                break;
            case 8: 
                return 0;
        }
    }
    return 0;
}