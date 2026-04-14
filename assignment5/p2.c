#include <stdio.h>
#include <stdlib.h>
/*Abhijit Prasad Mallick
20252501001*/
int mvm = 0;  

int gm(int arr[], int n) {
    int mx = arr[0];
    for(int i = 1; i < n; i++) {
        if(arr[i] > mx)
            mx = arr[i];
    }
    return mx;
}

void ctrsort(int arr[], int n, int exp) {
    int op[n];
    int ctr[10] = {0};


    for(int i = 0; i < n; i++)
        ctr[(arr[i] / exp) % 10]++;

    
    for(int i = 1; i < 10; i++)
        ctr[i] += ctr[i - 1];

    
    for(int i = n - 1; i >= 0; i--) {
        int ix = (arr[i] / exp) % 10;
        op[ctr[ix] - 1] = arr[i];
        ctr[ix]--;
        mvm++;
    }

  
    for(int i = 0; i < n; i++)
        arr[i] = op[i];
}

int main() {
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("\nEnter the elements: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("\nOriginal Array: ");
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    int mx = gm(arr, n);
    int passes = 0;


    for(int exp = 1; mx / exp > 0; exp *= 10) {
        ctrsort(arr, n, exp);
        passes++;

        if(exp == 1)
            printf("\n\nSorting by 1's place: ");
        else if(exp == 10)
            printf("\nSorting by 10's place: ");
        else if(exp == 100)
            printf("\nSorting by 100's place: ");
        else
            printf("\nSorting by %d's place: ", exp);

        for(int i = 0; i < n; i++)
            printf("%d ", arr[i]);
    }

    printf("\n\n\nSorted Array: ");
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n\n\nPerformance Analysis:\n");
    printf("\nNumber of Splits (Digit Passes): %d", passes);
    printf("\nNumber of Element Movements: %d", mvm);
    printf("\nTime Complexity: O(d * (n + k))");
    printf("\nSpace Complexity: O(n + k) (for counting sort auxiliary array)");

    return 0;
}
