// COMSC-210 | Lab 21 | Jed Aficial 
// github link: https://github.com/jaficial/210-lab-21

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;
const int MAX_AGE = 20, MIN_AGE = 1;

// Goat class: contains two string arrays for an array of random color names, and an array for random names
/* NOTE: for the colors and names arrays, I do not have access to replit, thus not having access to the AI 
   mentioned in the lab docs. Instead, I came up with 15 different names and colors.*/
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
    // age, color, and name is randomized if default constructor is called
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
    // getters and setters for age, name, and color
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

    void push_back(Goat value) { // parameter is now a Goat object
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(Goat value) { // parameter is now a Goat object
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
    
    void delete_node(Goat value) { // value contains the Goat object from main, data is the temp Goat object
        if (!head) return; // Empty list

        Node* temp = head; // temp points to head
                           // NOTE: Need to test for each parameter in order to bypass the error when comparing objects  
        while (temp && ((temp->data.get_age() != value.get_age()) || (temp->data.get_name() !=value.get_name()) || (temp->data.get_color() != value.get_color()))) // advances the temp node, and deletes by term, not by position  
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }
    // NOTE: Call the getter attributes for data 
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty\n";
            return;
        };
        
        cout << "Forward:\n";
        while (current) {
            cout << setw(4) << "" << current->data.get_name() << " (" << current->data.get_color() << ", " << current->data.get_age() << ")\n";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        // NOTE: for some reason, when current is assigned to tail node, it points to random memory?
        // FIXED: Assigned current to head first to check if the list is empty
        Node* current = head; 
        if (!current) {        
            cout << "List is empty\n";
            return;
        };
        // if list isn't empty, current is then assigned to the tail node
        current = tail; 
        cout << "Backward:\n";
        while (current) {
            cout <<  setw(4) << "" << current->data.get_name() << " (" << current->data.get_color() << ", " << current->data.get_age() << ")\n";
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
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;
    // for loop sets the linked list with a random amount of Goat objects
    for (int i = 0; i < size; i++){
        Goat goat_value;
        list.push_back(goat_value);
    }

    // value2append is another random goat object that is appended to the tail of the doubly linked list
    Goat value2append;
    list.push_back(value2append);

    list.print();
    list.print_reverse();

    list.~DoublyLinkedList();
    list.print();
    list.print_reverse();

    return 0;
}
