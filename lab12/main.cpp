#include <iostream>
#include "math.h"

using namespace std;
int count = 0;

void swap(int *a, int *b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}

void heapifyDown(int heap[], int count, int i) {
    if (count == 1) {
        printf("Single element in the heap");
    } else {
        int minimum = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < count && heap[l] < heap[minimum])
            minimum = l;
        if (r < count && heap[r] < heap[minimum])
            minimum = r;
        if (minimum != i) {
            swap(&heap[i], &heap[minimum]);
            heapifyDown(heap, count, minimum);
        }
    }
}

void addElement(int el, int heap[]) {
    if (count < 10) {  // Assuming the heap size is fixed at 10
        heap[count] = el;
        count++;
    } else {
        cout << "Heap is full" << endl;
    }
}

void heapifyUp(int heap[], int count, int i) {
    if (count == 1) {
        printf("Single element in the heap");
    } else {
        int j = i;
        while( j>0 && heap[j/2]>heap[j]){
            swap(&heap[j/2],&heap[j]);
            j = j/2;
        }
    }
}

void buildMinHeap(int heap[], int count) {
    cout << "Choose: \n1-shiftDown\n2-shiftUp" << endl;
    int option;
    cin >> option;
    switch (option) {
        case 1: {
            for (int i = count / 2 - 1; i >= 0; i--) {
                heapifyDown(heap, count, i);
            }
            break;
        }
        case 2: {
            for (int i=0; i<count; i++) {
                heapifyUp(heap, count, i);
            }
            break;
        }
        default: {
            cout << "Not correct choice";
        }
    }
}

void deleteRoot(int heap[], int num) {
    int i;
    for (i = 0; i < count; i++) {
        if (num == heap[i])
            break;
    }

    swap(&heap[i], &heap[count - 1]);
    count -= 1;
}

void print(int heap[], int length) {
    int k = 0;
    int level = 0;
    while (k < length) {
        for (int i = 0; i < pow(2, level) && k < length; i++) {
            cout << heap[k++] << " ";
        }
        cout << endl;
        level++;
    }
}

int main() {
    int heap[10];
    int choice;
    do {
        cout << "Menu:" << endl;
        cout << "1. Add" << endl;
        cout << "2. Remove" << endl;
        cout << "3. Print" << endl;
        cout << "4. Build min heap" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int element;
                cout << "Input element to add: ";
                cin >> element;
                addElement(element, heap);
                break;
            }
            case 2: {
                int element;
                cout << "Input element to delete: ";
                cin >> element;
                deleteRoot(heap, element);
                break;
            }
            case 3: {
                cout << "Heap: " << endl;
                print(heap, count);
                cout << endl;
                break;
            }
            case 4: {
                buildMinHeap(heap, count);
                cout << "Min heap was built" << endl;
                break;
            }

            case 5: {
                cout << "Ending program" << endl;
                break;
            }

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);
    return 0;
}
