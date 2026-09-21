#include <iostream>
using namespace std;

#define SIZE 5

class CircularQueue {
    int queue[SIZE];
    int front, rear;

public:
    CircularQueue() {
        front = -1;
        rear = -1;
    } // Fixed constructor bracket

    void enqueue() {
        int value;
        if (front == (rear + 1) % SIZE) 
        {
            cout << "\nQueue Overflow";
            return;
        }
        cout << "\nEnter Element : ";
        cin >> value;
        if (front == -1) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % SIZE;
        }
        queue[rear] = value;
        cout << "\nElement Inserted Successfully.";
    }

    void dequeue() {
        if (front == -1) {
            cout << "\nQueue Underflow";
            return;
        }
        cout << "\nDeleted Element : " << queue[front];
        if (front == rear) {
            front = rear = -1;
        } else {
            front = (front + 1) % SIZE;
        }
    } // Fixed dequeue bracket position

    void display() {
        if (front == -1) {
            cout << "\nQueue is Empty";
            return;
        }
        cout << "\nQueue Elements : ";
        int i = front;
        while (true) {
            cout << queue[i] << " ";
            if (i == rear)
                break;
            i = (i + 1) % SIZE;
        }
        cout << endl;
    }
};

int main() { 
    CircularQueue q;
    int choice;
    do {
        cout << "\n\n===== CIRCULAR QUEUE =====";
        cout << "\n1. Enqueue";
        cout << "\n2. Dequeue";
        cout << "\n3. Display";
        cout << "\n4. Exit";
        cout << "\n\nEnter Choice : ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                q.enqueue();
                break;
            case 2:
                q.dequeue();
                break;
            case 3:
                q.display();
                break;
            case 4:
                cout << "\nProgram Terminated\n";
                break;
            default:
                cout << "\nInvalid Choice";
        }
    } while(choice != 4);
    
    return 0;
} // Added missing closing bracket for main()
