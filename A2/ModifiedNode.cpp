#include "ModifiedNode.h"
#include <iostream>

//constructor
ModifiedNode::ModifiedNode(){
    ModifiedStock data;
    next = nullptr;
    prev = nullptr;
};


ModifiedNode::~ModifiedNode()
{
    delete data;
}



void ModifiedNode::createNode(std::string id, std::string name, std::string desc, Price price, int on_hand, ItemOptionsll* itemOptions) {
    this->data = new ModifiedStock;
    this->data->id = id;
    this->data->name = name;
    this->data->description = desc;
    this->data->price = price;
    this->data->on_hand = on_hand;
    this->data->itemOptions = itemOptions;
}
