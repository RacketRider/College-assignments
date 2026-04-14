#include <stdio.h>

int main() 
{
    int n;
    scanf("%d", &n);

    int ar[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &ar[i]);

    int mx = ar[0];
    for (int i = 1; i < n; i++)
        if (ar[i] > mx)
            mx = ar[i];

    int ctr[mx];
    for (int i = 0; i < mx; i++)
        ctr[i] = 0;

    printf("Original Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d", ar[i]);
        if (i < n - 1) printf(" ");
    }

    printf("\n\nStep 1: Initialize count array\n");
    for (int i = 0; i < mx; i++) {
        printf("%d", ctr[i]);
        if (i < mx - 1) printf(" ");
    }

    for (int i = 0; i < n; i++)
        ctr[ar[i] - 1]++;

    printf("\n\nStep 2: Count occurrences\n");
    for (int i = 0; i < mx; i++) {
        printf("%d", ctr[i]);
        if (i < mx - 1) printf(" ");
    }

    for (int i = 1; i < mx; i++)
        ctr[i] += ctr[i - 1];

    printf("\n\nStep 3: Cumulative count\n");
    for (int i = 0; i < mx; i++) {
        printf("%d", ctr[i]);
        if (i < mx - 1) printf(" ");
    }

    int op[n];
    for (int i = 0; i < n; i++)
        op[i] = -1;

    printf("\n\nStep 4: Placing elements in sorted order\n\n");
    printf("Original Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d", ar[i]);
        if (i < n - 1) printf(" ");
    }
    printf("\n");

    int swaps = 0;

    for (int i = n - 1; i >= 0; i--) {
        int index = ctr[ar[i] - 1] - 1;
        op[index] = ar[i];
        ctr[ar[i] - 1]--;
        swaps++;

        printf("Placing %d at index %d\n", ar[i], index);

        printf("Updated Count Array: ");
        for (int j = 0; j < mx; j++) {
            printf("%d", ctr[j]);
            if (j < mx - 1) printf(" ");
        }

        printf("\nUpdated Output Array: ");
        for (int j = 0; j < n; j++) {
            printf("%d", op[j]);
            if (j < n - 1) printf(" ");
        }
        printf("\n\n");
    }

    printf("Step 4: Sorted output array\n");
    for (int i = 0; i < n; i++) {
        printf("%d", op[i]);
        if (i < n - 1) printf(" ");
    }

    printf("\n\nTime Complexity Analysis:\n");
    printf("Best Case: O(n + k)\n");
    printf("Worst Case: O(n + k)\n");
    printf("Average Case: O(n + k)\n");
    printf("Space Complexity: O(n + k)\n");
    printf("Total Swaps: %d\n", swaps);

    printf("\nSorted Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d", op[i]);
        if (i < n - 1) printf(" ");
    }

    return 0;
}