#include <stdio.h>
/*Abhijit Prasad Mallick
20252501001*/
void prntarrb(int a[],int n) 
{
    int i;
    printf("[");
    for(i=0;i<n;i++) 
    {
        printf("%d", a[i]);
        if(i!=n-1) 
            printf(", ");
    }
    printf("]");
}
int main() 
{
    int n;
    scanf("%d",&n);
    int a[n];
    for(int i=0;i<n;i++) 
        scanf("%d",&a[i]);
    int asort=1;
    for(int i=1;i<n;i++) 
    {
        if(a[i]<a[i-1]) 
        {
            asort=0;
            break;
        }
    }
    int comp=0;
    int sft=0;
    printf("Sorting process:\n\n");
    for(int i=1;i<n;i++) 
    {
        int key=a[i];
        int j=i-1;
        printf("Pass %d (i=%d, key=%d):\n",i,i,key);
        int dshift=0;
        while(j>=0) 
        {
            comp++;
            if(key<a[j]) 
            {
                printf("Comparing %d and %d -> Shifted %d to right\n", key, a[j], a[j]);
                a[j+1]=a[j];
                sft++;
                dshift=1;
                j--;
            } 
            else 
                break;
        }
        a[j+1]=key;
        if(!dshift) 
        {
            printf("No shifts needed, %d remains at position %d -> ",key,i);
            prntarrb(a,n);
            printf(".\n\n");
        } else {
            printf("Insert %d at index %d -> ",key,j+1);
            prntarrb(a,n);
            printf(".\n\n");
        }
    }
    printf("Final Sorted array: ");
    for(int i=0;i<n;i++) 
    {
        printf("%d",a[i]);
        if(i!=n-1) 
            printf(" ");
    }
    printf("\n");
    printf("Total Comparisons: %d\n",comp);
    printf("Total Shifts: %d\n",sft);
    if(asort) 
        printf("Best Case: O(n) - Already Sorted Input.\n");
    else 
        printf("Average Case: O(n^2) - Random Order Input.\n");
    return 0;
}