#include <stdio.h>
/*Abhijit Prasad Mallick
20252501001*/
int main() {
    int n;
    scanf("%d", &n);

    int a[n];
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    int comp = 0, swps = 0;
    int inc = 1, dec = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] < a[i - 1]) inc = 0;
        if (a[i] > a[i - 1]) dec = 0;
    }

    printf("Sorting process:\n\n");

    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        printf("Pass %d:\n", i + 1);

        for (int j = 0; j < n - i - 1; j++) {
            comp++;

            if (a[j] > a[j + 1]) {
                int beforeLeft = a[j];
                int beforeRight = a[j + 1];

                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;

                swps++;
                swapped = 1;

                printf("Comparing %d and %d -> Swapped to get: ", beforeLeft, beforeRight);
                for (int k = 0; k < n; k++) {
                    printf("%d", a[k]);
                    if (k != n - 1) printf(" ");
                }
                printf("\n");
            } else {
                printf("Comparing %d and %d -> No Swap, so Same previous View: ", a[j], a[j + 1]);
                for (int k = 0; k < n; k++) {
                    printf("%d", a[k]);
                    if (k != n - 1) printf(" ");
                }
                printf("\n");
            }
        }

        printf("\n");
        if (!swapped) break;
    }

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i != n - 1) printf(" ");
    }
    printf("\n");

    printf("Total Comparisons: %d\n", comp);
    printf("Total Swaps: %d\n", swps);

    if (inc)
        printf("Best Case: O(n) - Already Sorted Input.\n");
    else if (dec)
        printf("Worst Case: O(n^2) - Reverse Sorted Input.\n");
    else
        printf("Average Case: O(n^2) - Random Order Input.\n");

    return 0;
}
