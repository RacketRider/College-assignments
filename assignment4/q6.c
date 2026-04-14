#include <stdio.h>
#define max 100
/*Abhijit Prasad Mallick
20252501001*/
void disp(int sz);
void prntmrkd(int sz,int c,int d);
void heap(int sz,int i);
int a[max];
int n,c=0,s=0;
int main() 
{
    scanf("%d",&n);
    for (int i=0;i<n;i++) 
    scanf("%d",&a[i]);
    printf("Initial array: ");
    disp(n);
    printf("\n\nBuilding Max Heap:\n\n");
    for(int i=n/2-1;i>=0;i--) 
    {
        printf("Heapifying subtree rooted at index %d (%d):\n",i,a[i]);
        heap(n,i);
        printf("Subtree after heapify: ");
        prntmrkd(n,i,-1);
        printf("\n\n");
    }
    printf("\nSorting Phase:\n\n");
    for(int i=n-1;i>0;i--) 
    {
        printf("=== Moving root %d (index 0) to final position %d ===\n",a[0],i);
        printf(" Before swap: ");
        prntmrkd(i+1,0,i);
        printf("\n");
        int temp=a[0];
        a[0]=a[i];
        a[i]=temp;
        s++;
        printf(" After swap:  ");
        prntmrkd(n, 0, i);
        printf("\n");
        printf("Heapifying new root:");
        if (i>1) 
            printf(" ");
        printf("\n");
        heap(i,0);
        printf("\n\n");
    }
    printf("Final sorted array: ");
    disp(n);
    printf("\n");
    printf("Total comparisons: %d\n",c);
    printf("Total swaps: %d\n",s);
    return 0;
}
void prntmrkd(int sz,int c,int d) 
{
    for(int i=0;i<sz;i++) 
    {
        if(i==c||i==d)
            printf("[%d]",a[i]);
        else
            printf("%d",a[i]);
        if(i<sz-1) 
            printf(" ");
    }
}
void heap(int sz,int i) 
{
    int lrg=i;
    int l=2*i+1;
    int r=2*i+2;
    if(l<sz) 
    {
        c++;
        printf(" Comparing %d (index %d) with left child %d (index %d)\n",a[i],i,a[l],l);
        if(a[l]>a[lrg])
            lrg=l;
    }
    if(r<sz) 
    {
        c++;
        printf(" Comparing %d (index %d) with right child %d (index %d)\n",a[lrg],lrg, a[r], r);
        if (a[r] >a[lrg])
            lrg=r;
    }
    if(lrg!=i) 
    {
        printf(" !! SWAPPING %d (index %d) with %d (index %d)\n",a[i],i,a[lrg],lrg);
        int temp=a[i];
        a[i]=a[lrg];
        a[lrg]=temp;
        s++;
        printf(" Array state: ");
        prntmrkd(sz, i, lrg);
        printf("\n");
        heap(sz, lrg);
    }
}
void disp(int sz) 
{
    for(int i=0;i<sz;i++) 
    {
        printf("%d",a[i]);
        if(i<sz-1) 
            printf(" ");
    }
}