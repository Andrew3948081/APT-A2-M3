#include "ItemOptionsNode.h"
#include <iostream>

// ItemOptionsNode::ItemOptionsNode(){
//     std::string data;
//     next = nullptr;
  
// };


// ItemOptionsNode::~ItemOptionsNode()
// {
//     delete data;
// }

// void ItemOptionsNode::setNode(std::string option){
//     this->data = &option;
// }



ItemOptionsNode::ItemOptionsNode(std::string val) {
    data = val;
    next = NULL;
}

ItemOptionsNode::~ItemOptionsNode(){
    //
}