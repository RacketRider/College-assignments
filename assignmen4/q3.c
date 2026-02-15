#include <stdio.h>
/*Abhijit Prasad Mallick
20252501001*/
void prntab(int a[], int n) {
    printf("[");
    for(int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if(i != n - 1) printf(", ");
    }
    printf("]");
}
void prntub(int a[], int start, int n) {
    printf("[");
    for(int i = start; i < n; i++) {
        printf("%d", a[i]);
        if(i != n - 1) printf(", ");
    }
    printf("]");
}
int main() {
    int n;
    scanf("%d", &n);
    int a[n];
    for(int i = 0; i < n; i++) 
        scanf("%d", &a[i]);
    int comparisons = 0, swaps = 0;
    int inc = 1;
    for(int i = 1; i < n; i++) {
        if(a[i] < a[i - 1]) { inc = 0; break; }
    }
    printf("Sorting process:\n\n");
    for(int i = 0; i < n - 1; i++) {
        int minIdx = i;

        printf("Pass %d (i=%d):\n", i + 1, i);
        printf("Unsorted: ");
        prntub(a, i, n);
        printf("\n");

        for(int j = i + 1; j < n; j++) {
            comparisons++;
            if(a[j] < a[minIdx]) {
                printf("Comparing %d and %d ==> Now Min %d\n", a[minIdx], a[j], a[j]);
                minIdx = j;
            } else {
                printf("Comparing %d and %d ==> Min remains %d\n", a[minIdx], a[j], a[minIdx]);
            }
        }
        printf("Final Minimum: %d (index %d).\n", a[minIdx], minIdx);
        if(minIdx != i) {
            int original_ai = a[i];  
            int minval = a[minIdx];
            int temp = a[i];
            a[i] = a[minIdx];
            a[minIdx] = temp;
            swaps++;
            printf("Swapped %d (index %d) and %d (index %d) -> ", original_ai, minIdx, minval, i);
            prntab(a, n);
            printf("\n\n");
        } else {
            printf("No Swap needed, %d remains at position %d -> ", a[i], i);
            prntab(a, n);
            printf("\n\n");
        }
    }
    printf("Final Sorted array: ");
    prntab(a, n);
    printf("\n\n");

    printf("Total Comparisons: %d\n", comparisons);
    printf("Total Swaps: %d\n", swaps);

    if(inc)
        printf("Best Case: O(n^2) - Already Sorted Input.\n");
    else
        printf("Average Case: O(n^2) - Random Order Input.\n");

    return 0;
}