/*
    ***** CENG205 DATA STRUCTURES ****
                ASSIGNMENT 2

        EMIRHAN ERSOY -- 22118080001                                            */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // For String compare function

#define MAX_SIZE 20 // As given to us, we set the maximum array size to be equal to 20

// Define an array
int queue[MAX_SIZE];
// Initialize front and rear indices for first queue
int firstFront = 0;
int firstRear = 0;
// Initialize front and rear indices for second queue
int secondFront = 10;
int secondRear = 10;
//Initialize the size variables for tracking the number of elements
int firstSize = 0;
int secondSize = 0;

// Enqueue a value into the queue
void enqueue(int value, int queueNumber) {
        // Check if there is enough space in queue
        if ((queueNumber == 1 && firstSize < secondFront-1 ) || (queueNumber == 2 && secondSize < (MAX_SIZE - firstRear)))
        {
        // Insert the value into appropiate queue
        if (queueNumber == 1) {
            queue[firstRear] = value;
            firstRear = (firstRear + 1) % MAX_SIZE;
            firstSize++;
        } else if (queueNumber == 2) {
            queue[secondRear] = value;
            secondRear = (secondRear + 1) % MAX_SIZE;
            secondSize++;
        }
        // Success message
        printf("%d\t is inserted to queue %s\n", value, (queueNumber == 1) ? "FIRST" : "SECOND");
    } else {
        // The queue is full message
        printf("Queue %s is full\n", (queueNumber == 1) ? "FIRST" : "SECOND");
    }
}

// Dequeue a value from the queue
void dequeue(int queueNumber) {
    int value;
    //Check if queue is not empty
    if ((queueNumber == 1 && firstSize > 0) || (queueNumber == 2 && secondSize > 0)) {
            //remove the front item from appropriate queue
        if (queueNumber == 1) {
            value = queue[firstFront];
            firstFront = (firstFront + 1) % MAX_SIZE;
            firstSize--;
        } else if (queueNumber == 2) {
            value = queue[secondFront];
            secondFront = (secondFront + 1) % MAX_SIZE;
            secondSize--;
        }
    // Success message
        printf("%d\t is deleted from queue %s\n", value, (queueNumber == 1) ? "FIRST" : "SECOND");
    } else {
        // Error message if the queue is empty
        printf("Queue %s is empty\n", (queueNumber == 1) ? "FIRST" : "SECOND");
    }
}

// Function to print queues
void Print(int queueNumber) {
    int front, rear, size;
    // Determine te front rear and size of appropriate queue
    if (queueNumber == 1) {
        front = firstFront;
        rear = firstRear;
        size = firstSize;
    } else {
        front = secondFront;
        rear = secondRear;
        size = secondSize;
    }
    // Print the informations about queue
    printf("QUEUE:%s\t FRONT:%d\t REAR:%d \tSIZE:%d\n", (queueNumber == 1) ? "FIRST" : "SECOND", front, rear, size);

    // Check if the queue is not empty
    if (size > 0) {
        int i = front;
        // Print the items of the queue
        while (i != rear) {
            printf("%d \t", queue[i]);
            i = (i + 1) % MAX_SIZE;
        }
        printf("\n");
    } else {
        // Message to show queue is empty
        printf("NO_CONTENT\n");
    }
}

int main() {
    FILE *file = fopen("input.txt", "r");

    // Check if the file is opened
    if (file == NULL) {
            // Error message
        fprintf(stderr, "File cannot be opened\n");
        return 1;
    }

    char command[10];
    char queue[10];
    int value;

        // Through the file until the end is reached

    while (fscanf(file, "%s", command) != EOF) {
            // Check the command type and call appropriate function
        if (strcmp(command, "ENQUEUE") == 0) {
            fscanf(file, "%s %d", queue, &value);
            enqueue(value, (strcmp(queue, "FIRST") == 0) ? 1 : 2);
        } else if (strcmp(command, "DEQUEUE") == 0) {
            fscanf(file, "%s", queue);
            dequeue((strcmp(queue, "FIRST") == 0) ? 1 : 2);
        } else if (strcmp(command, "PRINT") == 0) {
            fscanf(file, "%s", queue);
            Print((strcmp(queue, "FIRST") == 0) ? 1 : 2);
        }
    }

    // Close the file
    fclose(file);

    return 0;
}
