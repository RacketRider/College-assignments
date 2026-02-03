#include <stdio.h>
#define mx 30
int stack[mx];
int top=-1;
/*Abhijit Prasad Mallick 
20252501001*/
void create();
void push();
void pop();
void peek();
void size();
void isEmpty();
void isFull();
void display();
int main() 
{
    int ch,t=4;
    printf("\n--- Stack Operations ---\n");
    printf("1. Create Stack (Reinitialize)\n");
    printf("2. Push an element\n");
    printf("3. Pop an element\n");
    printf("4. Peek/Top of the stack\n");
    printf("5. Get size of the stack\n");
    printf("6. Check if stack is empty\n");
    printf("7. Check if stack is full\n");
    printf("8. Display stack\n");
    printf("9. Exit\n");
    printf("Enter your choice: ");
    while (t--) 
    {
        scanf("%d",&ch);
        switch(ch) 
        {
            case 1: create(); break;
            case 2: push(); break;
            case 3: pop(); break;
            case 4: peek(); break;
            case 5: size(); break;
            case 6: isEmpty(); break;
            case 7: isFull(); break;
            case 8: display(); break;
            case 9: return 0;
            default: printf("Invalid choice!\n");
        }
    }
}
void create() 
{
    top=-1;
    printf("Stack reinitialized.\n");
}
void push() 
{
    int x;
    if(top==mx-1) 
    {
        printf("Stack overflow! Cannot push.\n");
        return;
    }
    printf("Enter element to push: ");
    scanf("%d",&x);
    stack[++top]=x;
    printf("%d pushed onto the stack.\n", x);
}
void pop() 
{
    if(top==-1) 
    {
        printf("Stack underflow! Cannot pop.\n");
        return;
    }
    printf("Popped element: %d\n",stack[top--]);
}
void peek() 
{
    if(top==-1) 
    {
        printf("Stack is empty.\n");
        return;
    }
    printf("Top element: %d\n",stack[top]);
}
void size() 
{
    printf("Stack size: %d\n",top+1);
}
void isEmpty() 
{
    if(top==-1)
        printf("Stack is empty.\n");
    else
        printf("Stack is not empty.\n");
}
void isFull() 
{
    if(top==mx-1)
        printf("Stack is full.\n");
    else
        printf("Stack is not full.\n");
}
void display() 
{
    int i;
    if(top==-1) 
    {
        printf("Stack is empty! Nothing to display.\n");
        return;
    }
    for(i=top;i>=0;i--) 
        printf("%d\n",stack[i]);
}