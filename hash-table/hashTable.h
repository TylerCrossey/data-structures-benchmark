#pragma once
#include "SLL.h"

template <class V>
class HashTable {
    int tableSize; // table size
    
    SLL<V>* table;
    
    public:
    // default constructor, which uses default table size 3
    HashTable(){
        tableSize = 3;
        table = new SLL<V>[tableSize];
    }
    
    // constructor, which use size as the table size
    HashTable(int size){
      tableSize = size;
      table = new SLL<V>[tableSize];
    }
    
    // search item in the table
    // if found, return true; otherwise, return false
    bool find(V item){
      //hashing function to find which sll the item will be in
      int index = item % tableSize;
      //search in that sll to find the item, if we find it return true otherwise it will return nullptr and this will return false
      return (table[index].search(item) != nullptr);
    }
    
    // insert (item1, item2) to the table
    // use item1 as the key
    // if inserted, return true
    // otherwise, return false
    bool insert(V item1, V item2){
      //hashing function to find sll index
      int index = item1 % tableSize;

      //check if ssn exists in that sll, if so dont insert
      if(table[index].search(item1)!=nullptr) return false;

      //we proceed with insertion, call insert function for that sll
      table[index].insert(item1, item2);
      return true;
    }
    
    // delete the pair whose key value is item
    // if deleted, return true
    // otherwise, return false 
    bool erase(V item){
      int index = item % tableSize;
      //simply find index, then call sll remove on that sll for the item
      return table[index].remove(item);
    }

    // return the total number of nodes in the hash table    
    int getSize(){
      //just add the size value of each ssl in table
      int total = 0;
      for(int i=0; i<tableSize; i++){
        total += table[i].getSize();
      }
      return total;
    }
    
    ~HashTable(){ delete[] table; }

    // copying would double-free the table, so forbid it
    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;
};
