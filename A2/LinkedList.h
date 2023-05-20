#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"


class LinkedList
{
public:
    LinkedList();
    ~LinkedList();
    //This function inserts a node in alphabetical order into the linked list
    bool addNode(Node* node);
    //Delete the node with the correnponding id
    bool deleteNode(std::string id);
    //returns the largest id in the list
    std::string getLargestId();
    //display all items
    void displayItems();
    //reset all stocks to default value
    void resetStocks();
    
    Node* searchID(std::string id);
    void updateStockCount(std::string IDsearch);

    //first node in the list
    Node* head;
    
};

#endif  // LINKEDLIST_H


