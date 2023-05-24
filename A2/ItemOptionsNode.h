
#include <string> 
// class ItemOptionsNode
// {
// public:
//     ItemOptionsNode();
//     ~ItemOptionsNode();
//     //setNode paramters
//     void setNode(std::string options);



//     // pointer to the data held for the node 
//     std::string* data;
//     // pointer to the next node in the list 
//     ItemOptionsNode* next;
   
// };

#ifndef IONODE_H
#define IONODE_H

class ItemOptionsNode {
public:
    std::string data;
    ItemOptionsNode* next;

    
    ItemOptionsNode(std::string);
    ~ItemOptionsNode();
};

#endif
