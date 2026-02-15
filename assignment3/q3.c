#include <stdio.h>
#define SIZE 100
/*Abhijit Prasad Mallick
20252501001*/
int q[SIZE];
int f=-1,r=-1;
int ldq=0;
int adq=0;
int isEmpty() 
{
    return f==-1;
}
void printq(int ob) 
{
    printf("Queue elements: ");
    for (int i=f;i<=r;i++)
        printf("%d ",q[i]);
    printf("\n");
    if(ob) 
    {
        printf("Front Index: %d, Front Value: %d\n",f+1,q[f]);
        printf("Rear Index: %d, Rear Value: %d\n",r+1,q[r]);
    } 
    else 
    {
        printf("Front Index: %d, Front Value: %d\n",f,q[f]);
        printf("Rear Index: %d, Rear Value: %d\n",r,q[r]);
    }
}
void dequeue() 
{
    printf("Before Dequeue:\n");
    if(isEmpty()) 
    {
        printf("Front Index: -1, Front Value: NoVal\n");
        printf("Rear Index: -1, Rear Value: NoVal\n");
        printf("Queue is empty. Cannot dequeue.\n");
        return;
    }
    printq(0);
    ldq=q[f];
    adq=1;
    printf("%d dequeued.\n",ldq);
    f++;
    printf("After Dequeue:\n");
    printq(0);
}
void enqueue(int val) 
{
    if (isEmpty())
        f=r=0;
    else
        r++;
    q[r]=val;
    printf("%d enqueued.\n", val);
}
int main() 
{
    int ch,n,val;
    while(scanf("%*[^0-9]%d",&ch)==1) 
    {  
        switch (ch) 
        {
            case 1:  
                scanf("%d",&n);
                for (int i=0;i<n;i++) 
                {
                    scanf("%d",&val);
                    if(adq) 
                    {
                        r++;
                        q[r]=q[r-1]+val+ldq;
                        adq=0;
                        ldq=0;
                    } 
                    else 
                        enqueue(val);
                }
                printq(0);
                break;
            case 2:
                printf("2\n");
                dequeue();
                break;
            case 3:
                if(isEmpty()) 
                {
                    printf("Front Index: -1, Front Value: NoVal\n");
                    printf("Rear Index: -1, Rear Value: NoVal\n");
                } 
                else
                    printq(1);
                break;
            case 4:   
                printf("Queue is empty.\n");
                break;
        }
    }
    return 0;
}