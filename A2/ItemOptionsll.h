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

    
public:
    ItemOptionsNode* head;
    ItemOptionsll();
    ~ItemOptionsll();
    //insert item to the list
    void insert(std::string val);
    //display the items for displaying 
    void display();
    //get the total length of the string
    int getTotalLength();
    //check if item exists in list
    bool itemExist(const std::string s);
    //get all the items in the list for save file
    std::string getItems();
};

#endif //ITEMOPTSLINKEDLIST_H