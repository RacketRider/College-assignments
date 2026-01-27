#include<stdio.h>
#include<stdlib.h>
#define Max 10
int ar[Max];
int n=0;
void create();
void insert();
void deletion();
void search();
void display();
/*Abhijit Prasad Mallick 
20252501001*/
void create() 
{
    int i;
    printf("Enter number of elements (max %d):",Max);
    scanf("%d",&n);
    if(n<0||n>Max) 
    {
        printf("Invalid size!\n");
        n=0;
        return;
    }
    for(i=0;i<n;i++) 
    {
        printf("Enter element %d:",i+1);
        scanf("%d",&ar[i]);
    }
}
void insert() 
{
    int pos,ele,i;
    if(n>=Max) 
    {
        printf("List is full.Can't insert.\n");
        return;
    }
    printf("Enter position to insert (1 to %d): ",n+1);
    scanf("%d",&pos);
    if(pos<1||pos>n+1) 
    {
        printf("Invalid position!\n");
        return;
    }
    printf("Enter element to insert:");
    scanf("%d",&ele);
    for(i=n;i>=pos;i--) 
    {
     ar[i]=ar[i-1];
    }
    ar[pos-1]=ele;
    n++;
    printf("Element inserted successfully.\n");
    display();
}
void deletion() 
{
    int pos,i;
    if(n==0) 
    {
        printf("List is empty.Can't delete.\n");
        return;
    }
    printf("Enter position to delete (1 to %d): ",n);
    scanf("%d",&pos);
    if (pos<1||pos>n) 
    {
        printf("Invalid position!\n");
        return;
    }
    for (i = pos - 1; i < n - 1; i++)
        ar[i] = ar[i + 1];
    n--;
    printf("Element deleted successfully.\n");
    display();
}
void search() 
{
    int se,i,fnd = 0;
    if (n==0) 
    {
        printf("List is empty.\n");
        return;
    }
    printf("Enter element to search: ");
    scanf("%d",&se);
    for (i=0;i<n;i++) 
    {
        if (ar[i]==se) 
        {
            printf("Element %d found at position %d.\n",se,i+1);
            fnd=1;
            break;
        }
    }
    if(!fnd) 
        printf("Element not found.\n");
}
void display() 
{
    if(n<=0)
    {
        printf("List is empty.\n");
        return;
    }
    printf("List elements: ");
    for (int i = 0; i < n; i++)
        printf("%d ",ar[i]);
    printf("\n");
}
int main() 
{
    int ch;
    while(1) 
    {
        printf("\n--- ABL MENU ---\n");
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