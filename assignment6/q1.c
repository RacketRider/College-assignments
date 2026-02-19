#include <stdio.h>

void linearsearch(int arr[], int n, int key)
{
    int first = -1, last = -1, count = 0;
    printf("\nStepwise Execution of Linear Search:\n");
    for (int i = 0; i < n; i++) 
    {
        printf("\nStep %d: Comparing key (%d) with arr[%d] = %d",
               i + 1, key, i, arr[i]);
        if (arr[i] == key) {
            if (first == -1)
                first = i;
            last = i;
            count++;
            printf("\nSuccess: Element %d found at index %d (Position %d)",
                   key, i, i + 1);
            printf("\nComparisons made so far: %d\n", i + 1);
        }
    }
    printf("\nFinal Search Summary:\n");

    if (count > 0) {
        printf("-> First Occurrence at Index: %d (Position %d)\n",
               first, first + 1);
        printf("-> Last Occurrence at Index: %d (Position %d)\n",
               last, last + 1);
        printf("-> Total Occurrences: %d\n", count);
    } else {
        printf("-> Element not found\n");
    }

    printf("-> Total Comparisons Made: %d\n", n);

    printf("\nTime Complexity Analysis:\n");
    printf("-> Average Case: O(n) (Found in middle positions, comparisons = n/2)\n");
}

int main()
{
    int n, key;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter the search key: ");
    scanf("%d", &key);

    linearsearch(arr, n, key);

    return 0;
}
