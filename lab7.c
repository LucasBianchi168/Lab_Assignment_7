/*
COP 3502C, Spring 2024, Session 0003, Lab 0024
Lucas Bianchi, Lab Assignment 7
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// this structure will be used to store the amount of times a number was swapped in the array
typedef struct element {
    int value;
    int count;
    struct element* next;
} Element;

// create a linked list using the element structure
Element* createLL(int arr[], int n) {
    Element* head = (Element*)malloc(sizeof(Element));
    if (head != NULL) {
        head->value = arr[0];
        head->count = 0;
        head->next = NULL;
        Element* temp = head;
        head->next = temp;
        for (int i = 1; i < n; ++i) {
            Element* newNode = (Element*)malloc(sizeof(Element));
            if (newNode != NULL) {
                newNode->value = arr[i];
                newNode->count = 0;
                newNode->next = NULL;
                temp->next = newNode;
                temp = temp->next;
            }
        }
        return head;
    }
    else {
        return NULL;
    }
}

// add one to the amount of times a number was swapped
void increment(Element** head, int num) {
    Element* temp = *head;
    while (temp != NULL) {
        if (temp->value == num) {
            temp->count += 1;
            break;
        }
        temp = temp->next;
    }
}

// clear the linked list to avoid a memory leak
Element* clearLL(Element** head) {
    if (*head != NULL) {
        Element* temp = *head;
        Element* toDel = *head;
        while (temp != NULL) {
            temp = temp->next;
            free(toDel);
            toDel = temp;
        }
        return NULL;
    }
    return *head;
}

// print the swap count of a particular number
void printSwapCount(Element* head, int num) {
    Element* temp = head;
    while (temp != NULL) {
        if (temp->value == num) {
            printf("%d: %d\n", temp->value, temp->count);
            break;
        }
        temp = temp->next;
    }
}

// swap the values of two elements, then increment each element's swap count by one if they are not the same value
void swap(int arr[], int i, int j, Element** head) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    if (i != j) {
        increment(head, arr[i]);
        increment(head, arr[j]);
    }
}

int selectionSort(int arr[], int n, Element** head) {
    int mindex; // used to store the minimum index to swap with
    int total = 0; // total amount of swaps
    for (int i = 0; i < n - 1; i++) {
        mindex = i; // set the minimum index to i
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[mindex]) {
                mindex = j; // if the current element is less than the mindex, change the mindex to be at that element
            }
        }
        swap(arr, i, mindex, head);
        if (i != mindex) {
            total += 1;
        }
    }
    return total;
}

int bubbleSort(int arr[], int n, Element** head) {
    int total = 0; // total amount of swaps
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // swap the element with the next one if its value is greater than that of the next element
                swap(arr, j, j + 1, head);
                total += 1;
            }
        }
    }
    return total;
}

void main(void)
{
    int array1[] = { 97, 16, 45, 63, 13, 22, 7, 58, 72 };
    int array2[] = { 90, 80, 70, 60, 50, 40, 30, 20, 10 };
    int array3[] = { 97, 16, 45, 63, 13, 22, 7, 58, 72 };
    int array4[] = { 90, 80, 70, 60, 50, 40, 30, 20, 10 };
    Element* head1 = createLL(array3, 9);
    Element* head2 = createLL(array4, 9);
    int total;

    printf("array1 bubble sort\n\n");
    total = bubbleSort(array3, 9, &head1);
    for (int i = 0; i < 9; i++) {
        printSwapCount(head1, array3[i]);
    }
    printf("%d\n\n", total);
    clearLL(&head1);

    printf("array2 bubble sort\n\n");
    total = bubbleSort(array4, 9, &head2);
    for (int i = 0; i < 9; i++) {
        printSwapCount(head2, array4[i]);
    }
    printf("%d\n\n", total);
    clearLL(&head2);

    head1 = createLL(array1, 9);
    head2 = createLL(array2, 9);

    printf("array1 selection sort\n\n");
    total = selectionSort(array1, 9, &head1);
    for (int i = 0; i < 9; i++) {
        printSwapCount(head1, array1[i]);
    }
    printf("%d\n\n", total);
    clearLL(&head1);

    printf("array2 selection sort\n\n");
    total = selectionSort(array2, 9, &head2);
    for (int i = 0; i < 9; i++) {
        printSwapCount(head2, array2[i]);
    }
    printf("%d\n\n", total);
    clearLL(&head2);
}