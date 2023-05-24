#ifndef ITEMOPTSLINKEDLIST_H
#define ITEMOPTSLINKEDLIST_H
#include "ItemOptionsNode.h"


// class ItemOptionsLL
// {
// public:
//     ItemOptionsLL();
//     ~ItemOptionsLL();
//     //This function inserts a node in alphabetical order into the linked list
//     bool addNode(ItemOptionsNode* node);
//     //Delete the node with the correnponding id
//     bool deleteNode(std::string id);
//     //function that prints out the items in the list
//     void printOptions();
    
//     //first node in the list
//     ItemOptionsNode* head;
    
// };

class ItemOptionsll {
private:
    ItemOptionsNode* head;
public:
    ItemOptionsll();
    ~ItemOptionsll();
    void insert(std::string val);
    void display();
    int getTotalLength();
};

#endif //ITEMOPTSLINKEDLIST_H