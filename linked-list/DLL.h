#pragma once
#include <string>

struct Node{
    std::string ssn;
    std::string name;
    Node* succ;
    Node* pred;
};

class DLL{
    private:
    Node* headPtr;
    int itemCount;
    
    public:
    DLL();
    DLL(const DLL& n);
    virtual ~DLL();
    Node* getHeadPtr();
    int search(std::string ss) const;
    bool insert(std::string ss, std::string name, int & count);
    bool remove(std::string ss, int & count);
    int size();
    void display();
};