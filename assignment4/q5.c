#include <stdio.h>
/*Abhijit Prasad Mallick
20252501001*/
int pt(int a[],int l,int h,int n);
void qst(int a[],int l,int h,int n,int d);
void prntarr(int a[],int n);
int tsplits=0;       
int tcmpr=0; 
int tswaps=0;    
void prntarr(int a[],int n) 
{
    for (int i=0;i<n;i++) 
    {
        printf("%d",a[i]);
        if(i!=n-1) 
            printf(" ");
    }
}
int main() 
{
    int n;
    scanf("%d",&n);
    int a[n];
    for(int i=0;i<n;i++) 
        scanf("%d",&a[i]);
    int isSorted=1,isReverse=1;
    for(int i=1;i<n;i++) 
    {
        if(a[i]<a[i-1]) 
            isSorted=0;
        if(a[i]>a[i-1]) 
            isReverse=0;
    }
    printf(" Initial Array: ");
    prntarr(a,n);
    printf("\n\n");
    printf("Sorting Steps:\n\n");
    qst(a,0,n-1,n,1);
    printf("Sorted Array: ");
    prntarr(a,n);
    printf("\n\n");
    printf("Performance Analysis:\n");
    printf("Total Splits: %d\n", tsplits);
    printf("Total Comparisons: %d\n", tcmpr);
    printf("Total Swaps: %d\n", tswaps);
    if (isSorted||isReverse)
        printf("Case: Worst Case (O(n^2))\n");
    else
        printf("Case: Best Case (O(n log n))\n");
    return 0;
}
void qst(int a[],int l,int h,int n,int d) 
{
    if(l>=h) 
        return;
    printf("Recursion depth %d: QuickSort(%d, %d)\n\n",d,l,h);
    int p=pt(a,l,h,n);
    qst(a,l,p-1,n,d+1);
    qst(a,p+1,h,n,d+1);
}
int pt(int a[],int l,int h,int n) 
{
    tsplits++;
    int pivot=a[h];
    int i=l-1;
    printf("Pivot: %d\n",pivot);
    for (int j = l; j <= h - 1; j++) {
        tcmpr++;
        printf("Pivot Index=%d, j=%d, Comparing: arr[%d]=%d and pivot=%d,  Updated Array: ",i, j, j,a[j],pivot);
        prntarr(a,n);
        printf("\n");
        if(a[j]<=pivot) 
        {
            i++;
            if(i==j) 
            {
                printf("No swap needed, already in place: arr[%d]=%d,  Updated Array: ",j,a[j]);
                prntarr(a,n);
                printf("\n");
            } 
            else 
            {
                printf("Updated Pivot Index=%d Swapped: arr[%d]=%d and arr[%d]=%d,  Updated Array: ",i,i,a[i],j,a[j]);
                int tmp=a[i];
                a[i]=a[j];
                a[j]=tmp;
                tswaps++;
                prntarr(a,n);
                printf("\n");
            }
        }
    }
    int ppos=i+1;
    int bfr=a[ppos];
    printf("Comparing all elements in array with Pivot is completed, Updated Pivot Index=%d, Swapped: pivot %d and arr[%d]=%d\n",ppos,pivot,ppos,bfr);
    if(ppos!=h) 
    {
        int tmp=a[ppos];
        a[ppos]=a[h];
        a[h]=tmp;
        tswaps++;
    } 
    printf("NowPlaced pivot %d at correct position\n", pivot);
    printf("Partitioned Array: ");
    prntarr(a, n);
    printf("\n\n");
    return ppos;
}