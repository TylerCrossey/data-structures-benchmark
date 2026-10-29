#include "DLL.h"
#include <iostream>
#include <string>
using namespace std;


DLL::DLL(){
    headPtr = nullptr;
    itemCount=0;
}

// return the head pointer of the list
Node* DLL::getHeadPtr(){
    return headPtr;
}

// copy construct, which copies an existing list n
// the new list is a different object from n
// the new list and object n have the same contents
DLL::DLL(const DLL& n){
    headPtr = nullptr;
    itemCount = 0;
    Node* tail = nullptr;
    for (Node* cur = n.headPtr; cur != nullptr; cur = cur->succ){
        Node* newNode = new Node{cur->ssn, cur->name, nullptr, tail}; // succ, pred
        if (tail == nullptr) headPtr = newNode;
        else tail->succ = newNode;
        tail = newNode;
        itemCount++;
    }
}


// destructor
// release every node of the list
DLL::~DLL(){
    Node* current = headPtr;
    while (current != nullptr){
        //next to track next in dll, then delete current and walk both forwards one
        Node* next = current->succ;
        delete current;
        current = next;
    }
    //initialize empty list values
    headPtr = nullptr;
    itemCount = 0;
}

// if some node has SSN matcthes string ss
// return the index value of the node
// the index value of the first node is 0, the second node is 1, etc.
// if there is node matching ss, return -1
int DLL::search(string ss)const{
    const Node* current = headPtr;
    int index = 0;

    while (current != nullptr){
        if (current->ssn == ss){
            return index;
        }
        current = current -> succ;
        index++;
    }

    return -1;
}


// insert (ss, name) to the existing list
// the SSN values OF each node are organized in INCREASING order
// if there is a node matching ss value, return false; otherwise true
// else create a node with (ss, name), insert the node to the proper position
bool DLL::insert(string ss, string name, int & count){
    
    //check for dupes and find position, tracking the node before current
    Node* prev = nullptr;
    Node* current = headPtr;
    while (current != nullptr && current->ssn <= ss){
        if(current->ssn == ss){
           return false; // dupe found
        }
        prev = current;
        current = current->succ; //walk to next node
    }
        //create the new node to insert
        Node* newNode = new Node();
        newNode->ssn = ss;
        newNode->name = name;
        newNode->succ = nullptr;
        newNode->pred = nullptr;

        //empty case
        if (headPtr == nullptr){
            headPtr = newNode;
            itemCount++;
            count++;
            return true;
        }

        //beginning case
        if (current == headPtr){
            newNode->succ = headPtr;
            headPtr->pred = newNode;
            headPtr = newNode;
            itemCount++;
            count++;
            return true;
        }

        //end case
        if (current == nullptr){
            prev->succ = newNode;
            newNode->pred = prev;
            itemCount++;
            count++;
            return true;
        }
        

        //middle case (default)
        newNode->succ = current;
        newNode->pred = current->pred;
        current->pred->succ = newNode;
        current->pred = newNode;
        itemCount++;
        count++;
        return true;
    


    
}


// remove node containing ss value
// if there is no node containing ss, return false; otherwise true
bool DLL::remove(string ss, int & count){
    //use current to find node with matching ssn
    Node* current = headPtr;
    while (current != nullptr && current->ssn < ss){
        current = current->succ; //walk to next node
    }

    //false case (empty or no match)
    if (current == nullptr || current->ssn != ss) {
        return false;
    }

    //first node
    if (current == headPtr) {
        headPtr = current->succ;
        if (headPtr != nullptr){
            headPtr->pred = nullptr;
        }
        delete current;
        itemCount--;
        count++;
        return true;
    }

    //last node
    if (current->succ == nullptr){
        current->pred->succ = nullptr;
        delete current;
        itemCount--;
        count++;
        return true;
    }

    //middle node
    current->pred->succ = current->succ;
    current->succ->pred = current->pred;
    delete current;
    itemCount--;
    count++;
    return true;
}

// return the number of the nodes
int DLL::size(){
    
    return itemCount;
}

// iterate through each node
// print out SSN and memory address of each node
void DLL::display(){
    Node* temp;
    temp = headPtr;
    while (temp!= nullptr) {
        cout << temp->ssn << "\t" << temp << endl;
        temp = temp->succ;
    }
}
