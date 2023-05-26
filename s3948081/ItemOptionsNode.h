
#include <string> 


#ifndef IONODE_H
#define IONODE_H

//node that holds the item options 
class ItemOptionsNode {
public:
    std::string data;
    ItemOptionsNode* next;

    
    ItemOptionsNode(std::string);
    ~ItemOptionsNode();
};

#endif
