#include "ItemOptionsNode.h"
#include <iostream>



ItemOptionsNode::ItemOptionsNode(std::string val) {
    data = val;
    next = NULL;
}

ItemOptionsNode::~ItemOptionsNode(){
    //not required
}