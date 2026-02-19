#include <stdio.h>

int main() {
    int n, key;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    scanf("%d", &key);

    int low = 0, high = n - 1;
    int mid, step = 1;
    int comparisons = 0;

    int foundIndex = -1;
    int firstMidSuccess = 0;  
    printf("Stepwise Execution of Binary Search:\n");

    while (low <= high) {
        printf("Step %d:\n", step);

        printf("-> Current Range: Low = %d, High = %d\n", low, high);

        mid = low + (high - low) / 2;
        printf("-> Calculating Mid: mid = low + (high - low) / 2 = %d + (%d - %d) / 2 = %d\n",
               low, high, low, mid);

        printf("-> Checking arr[%d] = %d\n", mid, arr[mid]);
        comparisons++;

        if (arr[mid] == key) {
            foundIndex = mid;
            if (step == 1) firstMidSuccess = 1; 

            printf("Success: Element %d found at index %d (Position %d)\n", key, mid, mid + 1);
            printf("-> Comparisons made so far: %d\n", comparisons);
            break;
        } else if (key < arr[mid]) {
            printf("<= Moving left: key (%d) is less than arr[%d] = %d\n", key, mid, arr[mid]);
            high = mid - 1;
        } else {
            printf("=>Moving right: key (%d) is greater than arr[%d] = %d\n", key, mid, arr[mid]);
            low = mid + 1;
        }

        printf("\n");   
        step++;
    }

    int first = -1, last = -1, count = 0;

    if (foundIndex != -1) {
        first = last = foundIndex;
        int i = foundIndex - 1;
        while (i >= 0 && arr[i] == key) {
            first = i;
            comparisons++;
            i--;
        }
        i = foundIndex + 1;
        while (i < n && arr[i] == key) {
            printf("Checking right side: arr[%d] = %d\n", i, arr[i]);
            last = i;
            comparisons++;
            i++;
        }

        count = last - first + 1;
    }

    printf("\nFinal Search Summary:\n");
    if (foundIndex != -1) {
        printf("-> First Occurrence at Index: %d (Position %d)\n", first, first + 1);
        printf("-> Last Occurrence at Index: %d (Position %d)\n", last, last + 1);
        printf("-> Total Occurrences: %d\n", count);
    } else {
        printf("-> Element not found\n");
    }
    printf("-> Total Comparisons Made: %d\n\n", comparisons);

    printf(" Time Complexity Analysis:\n");
    if (firstMidSuccess) {
        printf("-> Best Case: O(1) (Found at middle position first try)\n");
    } else if (foundIndex == -1) {
        printf("-> Worst Case: O(log n) (Found at last position)\n");
    } else {
        printf("-> Average Case: O(log n) (Found in general search steps)\n");
    }

    return 0;
}
