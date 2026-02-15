#include <stdio.h>

#define SIZE 100

int q[SIZE];
int front = -1, rear = -1;
int lastDequeued = 0;
int afterDequeue = 0;

int isEmpty() {
    return front == -1;
}

void printQueue(int oneBased) {
    printf("Queue elements: ");
    for (int i = front; i <= rear; i++)
        printf("%d ", q[i]);
    printf("\n");

    

    if (oneBased) {
        printf("Front Index: %d, Front Value: %d\n", front + 1, q[front]);
        printf("Rear Index: %d, Rear Value: %d\n", rear + 1, q[rear]);
    } else {
        printf("Front Index: %d, Front Value: %d\n", front, q[front]);
        printf("Rear Index: %d, Rear Value: %d\n", rear, q[rear]);
    }
}

void enqueue(int val) {
    if (isEmpty())
        front = rear = 0;
    else
        rear++;

    q[rear] = val;
    printf("%d enqueued.\n", val);
}

void dequeue() {
    printf("Before Dequeue:\n");

    if (isEmpty()) {
        printf("Front Index: -1, Front Value: NoVal\n");
        printf("Rear Index: -1, Rear Value: NoVal\n");
        printf("Queue is empty. Cannot dequeue.\n");
        return;
    }

    printQueue(0);
    lastDequeued = q[front];
    afterDequeue = 1;
    printf("%d dequeued.\n", lastDequeued);

    front++;

    printf("After Dequeue:\n");
    printQueue(0);
}

int main() {
    int choice, n, val;

    while (scanf("%*[^0-9]%d", &choice) == 1) {   

        switch (choice) {

            case 1:   
                scanf("%d", &n);
                for (int i = 0; i < n; i++) {
                    scanf("%d", &val);

                    if (afterDequeue) {
                        rear++;
                        q[rear] = q[rear - 1] + val + lastDequeued;
                        afterDequeue = 0;
                        lastDequeued = 0;
                    } else {
                        enqueue(val);
                    }
                }
                printQueue(0);
                break;

            case 2:
                printf("2\n");
                dequeue();
                break;

            case 3:
                if (isEmpty()) {
                    printf("Front Index: -1, Front Value: NoVal\n");
                    printf("Rear Index: -1, Rear Value: NoVal\n");
                } else {
                    printQueue(1);
                }
                break;

            case 4:   
                printf("Queue is empty.\n");
                break;
        }
    }
    return 0;
}
