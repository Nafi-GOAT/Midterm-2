//
//  main.cpp
//  Midterm #2
//
//  COMSC 210|| Mehraj Hasan Nafi
// IDE used:Xcode
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        string data;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val;
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = tail = nullptr; }
    
    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void pop_front() {
        if (!head) return;
        Node* temp = head;
        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        } else
            head = tail = nullptr;
        delete temp;
    }
    
    void pop_back() {
        if (!tail) return;
        Node* temp = tail;
        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        } else
            head = tail = nullptr;
        delete temp;
    }
    
    bool empty() { return head == nullptr; }

    int size() {
        int count = 0;
        Node* current = head;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }
    
    
    string get_front() { return head ? head->data : ""; }
    string get_back() { return tail ? tail->data : ""; }

    // remove node at random position
     string remove_at_pos(int pos) {
         if (pos <= 0 || empty()) return "";
         Node* temp = head;
         for (int i = 1; i < pos && temp; i++)
             temp = temp->next;
         if (!temp) return "";

         string val = temp->data;
         if (temp->prev)
             temp->prev->next = temp->next;
         else
             head = temp->next;

         if (temp->next)
             temp->next->prev = temp->prev;
         else
             tail = temp->prev;

         delete temp;
         return val;
     }

    void print() {
        if (empty()) {
            cout << "    (empty)" << endl;
            return;
        }
        Node* current = head;
        while (current) {
            cout << "    " << current->data << endl;
            current = current->next;
        }
    }
};

int main() {
    srand(time(0));
    
    // Load names
    vector<string> names;
    ifstream fin("names.txt");
    string name;
    while (fin >> name)
        names.push_back(name);
    fin.close();
    
    if (names.empty()) {
        cout << "Error: names.txt missing or empty." << endl;
        return 1;
    }
    
    DoublyLinkedList line;
    
    cout << "Store opens:" << endl;
    
    // Add 5 customers initially
    for (int i = 0; i < 5; i++) {
        string cname = names[rand() % names.size()];
        cout << "    " << cname << " joins the line" << endl;
        line.push_back(cname);
    }
    
    cout << "    Resulting line:" << endl;
    line.print();
    
    // Run 20 minutes simulation
    for (int minute = 2; minute <= 20; minute++) {
        cout << "Time step #" << minute << ":" << endl;
        
        // 40% - serve front
        if (!line.empty() && (rand() % 100) < 40) {
            string served = line.get_front();
            cout << "    " << served << " is served" << endl;
            line.pop_front();
        }
        
        if ((rand() % 100) < 60) {
             string cname = names[rand() % names.size()];
             cout << "    " << cname << " joins the line" << endl;
             line.push_back(cname);
         }

         // 20% - rear leaves
         if (!line.empty() && (rand() % 100) < 20) {
             string rear = line.get_back();
             cout << "    " << rear << " (at the rear) left the line" << endl;
             line.pop_back();
         }

         // 10% - random customer leaves
         if (!line.empty() && (rand() % 100) < 10) {
             int pos = rand() % line.size() + 1;
             string left = line.remove_at_pos(pos);
             if (left != "")
                 cout << "    " << left << " left the line" << endl;
         }

         // 10% - VIP joins front
         if ((rand() % 100) < 10) {
             string cname = names[rand() % names.size()];
             cout << "    " << cname << " (VIP) joins the front of the line" << endl;
             line.push_front(cname + " (VIP)");
         }

         cout << "    Resulting line:" << endl;
         line.print();
         cout << endl;
     }

     return 0;
 }
        


