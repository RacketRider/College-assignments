#include <stdio.h>

#define max 30

int queue[max];
int f=-1,r=-1;
void enqueue();
void dequeue();
void display();
void isEmpty();
void isFull();
void printStatus() {
    if(f==-1) 
    {
        printf("Front Index: -1, Front Value: NoVal\n");
        printf("Rear Index: -1, Rear Value: NoVal\n");
    } 
    else 
    {
        printf("Front Index: %d, Front Value: %d\n",f,queue[f]);
        printf("Rear Index: %d, Rear Value: %d\n",r,queue[r]);
    }
}
int main() 
{
    int ch,t=3;
    printf("\nQueue Operations:\n");
    printf("1. Enqueue multiple elements\n");
    printf("2. Dequeue\n");
    printf("3. Display Queue\n");
    printf("4. IsEmpty\n");
    printf("5. IsFull\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
    while (t--) 
    {
        scanf("%d", &ch);
        switch (ch) 
        {
            case 1:
                enqueue();
                break;
            case 2:
                if(f==-1) 
                {
                    printf("Queue is empty. Cannot dequeue.\n");
                    printf("Front Index: -1, Front Value: NoVal\n");
                    printf("Rear Index: -1, Rear Value: NoVal\n");
                } 
                else 
                {
                    printf("Before Dequeue\n");
                    display();
                    printf("After Dequeue\n");
                    dequeue();
                }
                return 0; 
                break;
            case 3:
                display();
                break;
            case 4:
                isEmpty();
                break;
            case 5:
                isFull();
                break;
            case 6:
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}
void enqueue() 
{
    int n,val;
    printf("Enter number of elements to enqueue: ");
    scanf("%d",&n);
    printf("Enter %d values: ",n);
    for(int i=0;i<n;i++) 
    {
        scanf("%d",&val);
        if (r==max-1) 
        {
            printf("Queue is full.\n");
            break;
        }
        if(f==-1)
            f=0;
        queue[++r]=val;
        printf("%d enqueued.\n",val);
    }
    display();
}
void dequeue() 
{
    int deleted=queue[f];
    printf("%d dequeued.\n",deleted);
    if(f==r) 
        f=r=-1;
    else 
        f++;
    display();
}
void display() 
{
    if(f==-1) 
    {
        printf("Queue elements:\n");
        printStatus();
        return;
    }
    printf("Queue elements: ");
    for(int i=f;i<=r;i++) 
        printf("%d ",queue[i]);
    printf("\n");
    printStatus();
}
void isEmpty() 
{
    if(f==-1)
        printf("Queue is empty.\n");
    else
        printf("Queue is not empty.\n");
}
void isFull() 
{
    if(r==max-1)
        printf("Queue is full.\n");
    else
        printf("Queue is not full.\n");
}