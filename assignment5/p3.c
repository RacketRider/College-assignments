#include <stdio.h>

#define mx 100
/*Abhijit Prasad Mallick
20252501001*/

int ts = 0;
int ti = 0;

void insertionSortFloat(float bucket[], int size)
{
    for (int i = 1; i < size; i++) {
        float key = bucket[i];
        int j = i - 1;
        while (j >= 0 && bucket[j] > key) {
            bucket[j + 1] = bucket[j];
            j--;
        }
        bucket[j + 1] = key;
    }
}

void bucketSortIntegers()
{
    int n;
    scanf("%d", &n);

    int arr[mx];
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Original Array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(" ");
    }

    printf("\n\nStep 1: Buckets Created (Count = %d)\n", n);

    float bucket[mx][mx];
    int bc[mx] = {0};

    for (int i = 0; i < n; i++) {
        int index = arr[i] % n;
        bucket[index][bc[index]++] = arr[i];
        ti++;
        printf("Inserted %.2f into Bucket[%d]\n", (float)arr[i], index);
    }

    printf("\nStep 2: Sorting Buckets Using Insertion Sort\n");

    int k = 0;
    for (int i = 0; i < n; i++) {
        if (bc[i] > 0) {
            insertionSortFloat(bucket[i], bc[i]);
            for (int j = 0; j < bc[i]; j++) {
                arr[k] = (int)bucket[i][j];
                printf("Bucket[%d]: Placing %.2f back into array at index %d\n",
                       i, bucket[i][j], k);
                k++;
                ts++;
            }
        }
    }

    printf("\n---- Sorting Statistics ----\n");
    printf("Total Swaps: %d\n", ts);
    printf("Total Insertions into Buckets: %d\n", ti);
    printf("Space Complexity: O(n + k) where k is number of buckets (%d)\n", n);

    printf("\nSorted Array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(" ");
    }
}

void bucketSortFloat()
{
    int n;
    scanf("%d", &n);

    float arr[mx];
    for (int i = 0; i < n; i++)
        scanf("%f", &arr[i]);

    printf("Original Array:\n");
    for (int i = 0; i < n; i++) {
        printf("%.2f", arr[i]);
        if (i < n - 1) printf(" ");
    }

    printf("\n\nStep 1: Buckets Created (Count = %d)\n", n);

    float bucket[mx][mx];
    int bc[mx] = {0};

    for (int i = 0; i < n; i++) {
        int index = (int)(arr[i] * n);
        if (index >= n) index = n - 1;
        bucket[index][bc[index]++] = arr[i];
        ti++;
        printf("Inserted %.2f into Bucket[%d]\n", arr[i], index);
    }

    printf("\nStep 2: Sorting Buckets Using Insertion Sort\n");

    int k = 0;
    for (int i = 0; i < n; i++) {
        if (bc[i] > 0) {
            insertionSortFloat(bucket[i], bc[i]);
            for (int j = 0; j < bc[i]; j++) {
                arr[k] = bucket[i][j];
                printf("Bucket[%d]: Placing %.2f back into array at index %d\n",
                       i, bucket[i][j], k);
                k++;
                ts++;
            }
        }
    }

    printf("\n---- Sorting Statistics ----\n");
    printf("Total Swaps: %d\n", ts);
    printf("Total Insertions into Buckets: %d\n", ti);
    printf("Space Complexity: O(n + k) where k is number of buckets (%d)\n", n);

    printf("\nSorted Array:\n");
    for (int i = 0; i < n; i++) {
        printf("%.2f", arr[i]);
        if (i < n - 1) printf(" ");
    }
}

void bucketSortCharacters()
{
    int n;
    scanf("%d", &n);

    char arr[mx];
    for (int i = 0; i < n; i++)
        scanf(" %c", &arr[i]);

    printf("Original Array: ");
    for (int i = 0; i < n; i++)
        printf("%c", arr[i]);

    printf("\n\nStep 1: Buckets Created (Count = 26 for a-z)\n");

    char bucket[26][mx];
    int bc[26] = {0};

    for (int i = 0; i < n; i++) {
        int index = arr[i] - 'a';
        bucket[index][bc[index]++] = arr[i];
        ti++;
        printf("Inserted '%c' into Bucket[%d]\n", arr[i], index);
    }

    printf("\nStep 2: Sorting Buckets Using Insertion Sort\n");

    int k = 0;
    for (int i = 0; i < 26; i++) {
        if (bc[i] > 0) {
            for (int j = 0; j < bc[i]; j++) {
                arr[k] = bucket[i][j];
                printf("Bucket[%d]: Placing '%c' back into array at index %d\n",
                       i, bucket[i][j], k);
                k++;
                ts++;
            }
        }
    }

    printf("\n---- Sorting Statistics ----\n");
    printf("Total Swaps: %d\n", ts);
    printf("Total Insertions into Buckets: %d\n", ti);
    printf("Space Complexity: O(n + k) where k is 26 for characters\n");

    printf("\nSorted Array: ");
    for (int i = 0; i < n; i++)
        printf("%c", arr[i]);
}

int main()
{
    int choice;
    scanf("%d", &choice);

    ts = 0;
    ti = 0;

    if (choice == 1)
        bucketSortIntegers();
    else if (choice == 2)
        bucketSortFloat();
    else if (choice == 3)
        bucketSortCharacters();

    return 0;
}