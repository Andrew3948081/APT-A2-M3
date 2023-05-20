#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include "ModifiedNode.h"


class DoublyLinkedList
{
public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    //This function inserts a node in alphabetical order into the linked list
    bool addNode(ModifiedNode* node);
    //Delete the node with the correnponding id
    bool deleteNode(std::string id);
    //returns the largest id in the list
    std::string getLargestId();
    //display all items
    void displayItems();
    //reset all stocks to default value
    void resetStocks();
    
    ModifiedNode* searchID(std::string id);
    void updateStockCount(std::string IDsearch);

    //first node in the list
    ModifiedNode* head;
    
};

#endif  // DOUBLYLINKEDLIST_H


