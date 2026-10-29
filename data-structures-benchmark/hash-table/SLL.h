#pragma once
#include <iostream>
#include "node.h"

template <class U>
class SLL {
    
    Node<U> * headPtr;
    int size;
    
    public:
    // default constructor
    SLL(){
      headPtr = nullptr;
      size = 0;
    }

    // destructor    
    ~SLL(){
      // implement this method
      //make temp current node
      Node<U>* current = headPtr;
      //loop to walk each node in list and delete while setting temp and current each time
      while(current != nullptr){
        Node<U>* nextNode = current->next;
        delete current;
        current = nextNode;
      }
      //redo constructor code
      headPtr = nullptr;
      size = 0;
    }
    
    Node<U>* getHeadPtr(){
        return headPtr;
    }
    
    // insert (item1, item2) to the list
    void insert(U item1, U item2){
      //implement this method
      //create the new node to insert
      Node<U>* newNode = new Node<U>();
      //assign the passed values to it
      newNode->SSN = item1;
      newNode->name = item2;
      //new node becomes the new headptr and points to previous one as next (we can add to front because 
      //searching for hash table doesn't care about order)
      newNode->next = headPtr;
      headPtr = newNode;
      size++;
    }
    
    // if find the item1 value, return the pointer to the node
    // otherwise, return nullptr
    Node<U>* search(U item1){
      //implement this method
      //make a temp node for walking
      Node<U>* temp = headPtr;
      //loop to walk the list, each run check the current node SSN against the one we are searching for
      while(temp != nullptr){
        if (temp->SSN == item1) return temp;
        temp = temp->next;
      }
      return nullptr;
    }
    
    // remove the node with key value: item1
    bool remove(U item1){
      //implement this method
      //empty list case
      if(headPtr == nullptr) return false;
      
      Node<U>* curr = headPtr;
      //head has key case
      if (headPtr->SSN == item1){
        headPtr = headPtr->next;
        delete curr;
        size--;
        return true;
      }

      //general case (walking loop)
      //walk curr one so we can have a temp for previous (needed for patching hole)
      curr=headPtr->next;
      Node<U>* prev = headPtr;
      while(curr!=nullptr){
        //handle match
        if(curr->SSN == item1){
          prev->next = curr->next;
          delete curr;
          size--;
          return true;
        }
        //walk both temps 1
        prev = curr;
        curr = curr->next;
      }
      //default case
      return false;
    

    }
    
    int getSize(){
        
        return size;
    }
    
    // display the SSN values of each node in the linked list
    void display(){
        Node<U>* temp;
        temp = headPtr;
        while (temp!= nullptr) {
            std::cout << temp->SSN << std::endl;
            temp = temp->next;
        }
    }
};


