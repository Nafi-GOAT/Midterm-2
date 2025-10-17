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
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS; // dummy statement to avoid compiler warning
    return 0;
}


