#include "Node.h"
#include <iostream>

//constructor
Node::Node(){
    Stock data;
    next = nullptr;
};


//deconstructor 
Node::~Node(){
    delete this->data;
};


void Node::createNode(std::string id, std::string name, std::string desc, Price price, int on_hand) {
    this->data = new Stock;
    this->data->id = id;
    this->data->name = name;
    this->data->description = desc;
    this->data->price = price;
    this->data->on_hand = on_hand;
}
