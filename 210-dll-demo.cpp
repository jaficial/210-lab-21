#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;
const int MAX_AGE = 20, MIN_AGE = 1;

/* NOTES: need to make "Goat" class:
            - DONE || Private members: (int) age, (string) name, (string) color
              (string array) colors[15], (string array) names[15]
            - DONE || Default constructors: random age (1-20), random name from "name" array
              random color from the color array
            - DONE || Parameter constructor: will be a general 3-element parameter setup for age, name, color:
          
          DONE || MODIFY: "DoublyLinkedList class's "push_front()" and "push_back()"
                    so that it has the Goat object as the parameter instead of int   
          WORKING? || IN MAIN: - create a DLL object, and append it to a random number of Goat objects range 5-20 
                   - call methods to print both forward and backwards to show traversals
          DONE || PRINT():  Update both of the print methods in the class;
                        - Should display "List is empty" if list empty
                        - Otherwise output as expected (Check example)*/

// GOAT CLASS DONE
class Goat {
private:
    int age;
    string name;
    string color;
    string colors[15] = {"Beige", "Brown", "Blue", "Pink", "Black", "Grey", "Orange",
                        "Violet", "Teal", "Green", "Ivory", "Yellow", "Salmon", 
                        "Olive", "White"};
    string names[15] = {"Lyla", "Dylan", "Mary", "Brian", "AJ", "Dawn", "Lindsy",
                        "Jordan", "Meg", "Marcy", "Jesus", "Mo", "Gary",
                        "Demar", "Sam"};
public:
    // default constructor
    Goat(){
        age = rand() % ((MAX_AGE - MIN_AGE) + 1) + MIN_AGE;
        color = colors[rand() % ((14-0) + 1)]; // picks random index number between 0-14 from color array
        name = names[rand() % ((14-0) + 1)]; // picks random index number between 0-14 from names array
    }
    // parameter constructor
    Goat(int goat_age, string goat_color, string goat_name){
        age = goat_age;
        color = goat_color;
        name = goat_name;
    }
    
    void set_age(int goat_age) {age = goat_age;}
    int get_age() {return age;}

    void set_name(string goat_name) {name = goat_name;}
    string get_name() {return name;}

    void set_color(string goat_color) {color = goat_color;}
    string get_color() {return color;}

};

class DoublyLinkedList {
private:
    struct Node {
        Goat data;
        Node* prev;
        Node* next;
        Node(Goat val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(Goat value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(Goat value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(Goat value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }
    // COME BACK HERE ----------------------------------------------
    void delete_node(int value) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }
//
        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }
    // NOTE: Call the getter attribute for data 
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty\n";
            return;
        };

        while (current) {
            cout << current->data.get_name() << " (" << current->data.get_color() << ", " << current->data.get_age() << ")\n";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) {
            cout << "List is empty\n";
            return;
        };
        while (current) {
            cout << current->data.get_name() << " (" << current->data.get_color() << ", " << current->data.get_age() << ")\n";
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    srand(time(0));
    DoublyLinkedList list;
    










    /*
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);
    cout << "List forward: ";
    list.print();

    cout << "List backward: ";
    list.print_reverse();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();
    */ 
    // ORIGINAL CODE ^^
    return 0;
}
