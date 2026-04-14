#include <stdio.h>
/*Abhijit Prasad Mallick
20252501001*/
long long tsplt = 0;
long long tcomp = 0;
long long tswp  = 0;   
void prntrb(int a[], int l, int r) {
    printf("[");
    for(int i = l; i <= r; i++) printf("%d ", a[i]);
    printf("]");
}
void prntlr(int a[], int l, int m, int r) {
    printf("Left=[");
    for(int i = l; i <= m; i++) printf("%d ", a[i]);
    printf("], Right=[");
    for(int i = m + 1; i <= r; i++) printf("%d ", a[i]);
    printf("]");
}
void merge(int a[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for(int i = 0; i < n1; i++) 
        L[i] = a[l + i];
    for(int j = 0; j < n2; j++) 
        R[j] = a[m + 1 + j];
    printf("Merging (Indices: left=%d, mid=%d, right=%d):\n", l, m, r);

    printf("Left=[");
    for(int i = 0; i < n1; i++) printf("%d ", L[i]);
    printf("], Right=[");
    for(int j = 0; j < n2; j++) printf("%d ", R[j]);
    printf("]\n");

    int i = 0, j = 0, k = l;

    while(i < n1 && j < n2) {
        tcomp++;
        if(L[i] <= R[j]) {
            printf("Compare %d with %d, place %d.\n", L[i], R[j], L[i]);
            a[k++] = L[i++];
            tswp++; 
        } else {
            printf("Compare %d with %d, place %d.\n", L[i], R[j], R[j]);
            a[k++] = R[j++];
            tswp++; 
        }
    }

    while(i < n1) {
        printf("Place the remaining %d.\n", L[i]);
        a[k++] = L[i++];
        tswp++; 
    }

    while(j < n2) {
        printf("Place the remaining %d.\n", R[j]);
        a[k++] = R[j++];
        tswp++; 
    }

    printf("After Merge: ");
    prntrb(a, l, r);
    printf("\n\n");
}

void mergeSort(int a[], int l, int r) {
    if(l >= r) return;

    int m = l + (r - l) / 2;
    tsplt++;

    printf("Splitting (Indices: left=%d, mid=%d, right=%d):\n", l, m, r);
    prntrb(a, l, r);
    printf(" -> ");
    prntlr(a, l, m, r);
    printf("\n\n");

    mergeSort(a, l, m);
    mergeSort(a, m + 1, r);
    merge(a, l, m, r);
}

int main() {
    int n;
    scanf("%d", &n);

    int a[n];
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);

    int isSorted = 1, isReverse = 1;
    for(int i = 1; i < n; i++) {
        if(a[i] < a[i - 1]) isSorted = 0;
        if(a[i] > a[i - 1]) isReverse = 0;
    }

    printf("Starting Merge Sort...\n\n");

    mergeSort(a, 0, n - 1);

    printf("Sorted Array: ");
    prntrb(a, 0, n - 1);
    printf("\n\n");

    printf("Performance Analysis:\n");
    printf("Total Splits: %lld\n", tsplt);
    printf("Total Comparisons: %lld\n", tcomp);
    printf("Total Swaps: %lld\n", tswp);

    if(isSorted) printf("Input Type: Best Case\n\n");
    else if(isReverse) printf("Input Type: Worst Case\n\n");
    else printf("Input Type: Average Case\n\n");

    printf("Time Complexity Analysis:\n");
    printf("Best Case (Already Sorted)   : O(n log n)\n");
    printf("Worst Case (Reversed Order)  : O(n log n)\n");
    printf("Average Case                 : O(n log n)\n");

    return 0;
}
