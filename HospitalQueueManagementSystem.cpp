#include <iostream>
#include <string>
using namespace std;

class Patient {
public:
    string name;
    int age;
    string problem;
    int priority; // 1 = High, 2 = Medium, 3 = Low
};

// =============== Normal Circular Queue ===============
class CircularQueue {
private:
    class Node {
    public:
        Patient data;
        Node* next;
        Node(Patient val) {
            data = val;
            next = NULL;
        }
    };
    Node* front;
    Node* rear;

public:
    CircularQueue() {
        front = rear = NULL;
    }

    void enqueue(Patient val) {
        Node* n = new Node(val);
        if (front == NULL) {
            front = rear = n;
            rear->next = front;
        }
        else {
            rear->next = n;
            rear = n;
            rear->next = front;
        }
    }

    bool isEmpty() {
        return front == NULL;
    }

    Patient dequeue() {
        Patient tempData;
        if (front == NULL) {
            cout << "Queue is empty.\n";
            return tempData;
        }

        Node* temp = front;
        tempData = temp->data;

        if (front == rear) {
            front = rear = NULL;
        }
        else {
            front = front->next;
            rear->next = front;
        }

        delete temp;
        return tempData;
    }

    void display() {
        if (front == NULL) {
            cout << "Normal Queue is empty.\n";
            return;
        }

        cout << "Normal Queue:\n";
        Node* temp = front;
        do {
            cout << temp->data.name << " (" << temp->data.problem << ")\n";
            temp = temp->next;
        } while (temp != front);
    }
};

// =============== Priority Circular Queue ===============
class PriorityCircularQueue {
private:
    class Node {
    public:
        Patient data;
        Node* next;
        Node(Patient val) {
            data = val;
            next = NULL;
        }
    };
    Node* front;
    Node* rear;

public:
    PriorityCircularQueue() {
        front = rear = NULL;
    }

    void enqueue(Patient val) {
        Node* n = new Node(val);

        if (front == NULL) {
            front = rear = n;
            rear->next = front;
        }
        else if (val.priority < front->data.priority) {
            n->next = front;
            rear->next = n;
            front = n;
        }
        else {
            Node* temp = front;
            while (temp->next != front && temp->next->data.priority <= val.priority) {
                temp = temp->next;
            }
            n->next = temp->next;
            temp->next = n;
            if (temp == rear) {
                rear = n;
            }
        }
    }

    bool isEmpty() {
        return front == NULL;
    }

    Patient dequeue() {
        Patient tempData;
        if (front == NULL) {
            cout << "Queue is empty.\n";
            return tempData;
        }

        Node* temp = front;
        tempData = temp->data;

        if (front == rear) {
            front = rear = NULL;
        }
        else {
            front = front->next;
            rear->next = front;
        }

        delete temp;
        return tempData;
    }

    void display() {
        if (front == NULL) {
            cout << "Emergency Queue is empty.\n";
            return;
        }

        cout << "Emergency Priority Queue:\n";
        Node* temp = front;
        do {
            cout << temp->data.name << " (" << temp->data.problem << "), Priority: " << temp->data.priority << "\n";
            temp = temp->next;
        } while (temp != front);
    }
};

// =============== Bill Calculator ===============
int calculateBill(Patient p, bool isEmergency) {
    if (isEmergency)
    {
        if (p.priority == 1) return 5000;
        else if (p.priority == 2) return 3000;
        else return 1000;
    }
    return 500;
}

// =============== Main Menu ===============
int main() 
{
    CircularQueue normalQueue;
    PriorityCircularQueue emergencyQueue;

    int choice;

    do 
    {
        cout << "\n=== Hospital Queue Management ===\n";
        cout << "1. Add Patient\n";
        cout << "2. Serve Patient\n";
        cout << "3. Display Queues\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Validate choice input
        while (cin.fail() || choice < 1 || choice > 4)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Enter a valid option (1-4): ";
            cin >> choice;
        }

        if (choice == 1)
        {
            Patient p;

            cout << "Enter patient name: ";
            cin.ignore();  // clear leftover newline
            getline(cin, p.name);
            // Age input with validation
            cout << "Enter age: ";
            cin >> p.age;
            while (cin.fail() || p.age <= 0)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input! Enter a valid positive age: ";
                cin >> p.age;
            }

            cin.ignore(); // clear newline for next getline
            cout << "Enter problem: ";
            getline(cin, p.problem);

            int type;
            cout << "Patient type (1 = Emergency, 2 = Normal): ";
            cin >> type;
            while (cin.fail() || (type != 1 && type != 2)) 
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input! Enter 1 for Emergency or 2 for Normal: ";
                cin >> type;
            }

            if (type == 1) 
            {
                cout << "Enter priority (1 = High, 2 = Medium, 3 = Low): ";
                cin >> p.priority;
                while (cin.fail() || p.priority < 1 || p.priority > 3) 
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input! Enter priority (1-3): ";
                    cin >> p.priority;
                }
                emergencyQueue.enqueue(p);
            }
            else 
            {
                p.priority = 0; // optional, for normal patients
                normalQueue.enqueue(p);
            }

        }
        else if (choice == 2) 
        {
            if (!emergencyQueue.isEmpty())
            {
                Patient p = emergencyQueue.dequeue();
                int bill = calculateBill(p, true);
                cout << "\n--- Emergency Patient Served ---\n";
                cout << "Name: " << p.name << "\nProblem: " << p.problem
                    << "\nTotal Bill: Rs. " << bill << "\n";
            }
            else if (!normalQueue.isEmpty())
            {
                Patient p = normalQueue.dequeue();
                int bill = calculateBill(p, false);
                cout << "\n--- Normal Patient Served ---\n";
                cout << "Name: " << p.name << "\nProblem: " << p.problem
                    << "\nTotal Bill: Rs. " << bill << "\n";
            }
            else 
            {
                cout << "No patients in queue.\n";
            }

        }
        else if (choice == 3)
        {
            emergencyQueue.display();
            normalQueue.display();
        }
        else if (choice == 4) 
        {
            cout << "Exiting program...\n";
        }

    } while (choice != 4);

    return 0;
}
