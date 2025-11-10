#include <iostream>
using namespace std;

#define SIZE 5   // Fixed size of the queue

class CircularQueue {
private:
    int arr[SIZE];
    int front, rear;

public:
    CircularQueue() {
        front = -1;
        rear = -1;
    }

    // Check if queue is full
    bool isFull() {
        return ((rear + 1) % SIZE == front);
    }

    // Check if queue is empty
    bool isEmpty() {
        return (front == -1 && rear == -1);
    }

    // Enqueue (Insert)
    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue is Full! Cannot insert " << value << endl;
            return;
        }
        if (isEmpty()) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % SIZE;
        }
        arr[rear] = value;
        cout << value << " inserted into the queue.\n";
    }

    // Dequeue (Delete)
    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is Empty! Cannot delete.\n";
            return;
        }
        cout << "Deleted: " << arr[front] << endl;
        if (front == rear) { // only one element
            front = rear = -1;
        } else {
            front = (front + 1) % SIZE;
        }
    }

    // Display the queue
    void display() {
        if (isEmpty()) {
            cout << "Queue is Empty!\n";
            return;
        }
        cout << "Queue elements: ";
        int i = front;
        while (true) {
            cout << arr[i] << " ";
            if (i == rear) break;
            i = (i + 1) % SIZE;
        }
        cout << endl;
    }
};

// Main program
int main() {
    CircularQueue q;
    int choice, value;

    do {
        cout << "\n===== Circular Queue Menu =====\n";
        cout << "1. Enqueue (Insert)\n";
        cout << "2. Dequeue (Delete)\n";
        cout << "3. Display\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                q.enqueue(value);
                break;
            case 2:
                q.dequeue();
                break;
            case 3:
                q.display();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while(choice != 4);

    return 0;
}
