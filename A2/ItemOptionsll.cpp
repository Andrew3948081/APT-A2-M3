#include "ItemOptionsll.h"
#include <iostream>

// ItemOptionsLL::ItemOptionsLL() {
//     head = nullptr;
// }

// //deconstructor 
// ItemOptionsLL::~ItemOptionsLL() {
//     ItemOptionsNode* current = head;
//     while (current != nullptr) {
//         ItemOptionsNode* next = current->next;
//         delete current;
//         current = next;
//     }
// }

// bool ItemOptionsLL::addNode(ItemOptionsNode* newNode){
//     //loop through linked list and add to the end of the code
//     //std::cout << *newNode->data << std::endl;
//     if (this->head == nullptr) {
//         //std::cout << "something something" << std::endl;
//         this->head = newNode;
//         return true;
//     }
//     ItemOptionsNode* current = this->head;
//     while (current->next != nullptr) {
//         current = current->next;
//     }
//     current->next = newNode;
//     return true;

// }

// void ItemOptionsLL::printOptions(){
//     ItemOptionsNode* current = head;
//     while (current != nullptr) {
//         ItemOptionsNode* next = current->next;
//         std::cout << *current->data << std::endl;
//         current = next;
//     }
// }

ItemOptionsll::ItemOptionsll() {
    head = NULL;
}

ItemOptionsll::~ItemOptionsll() {
    ItemOptionsNode* temp = head;
    while (temp != NULL) {
        ItemOptionsNode* next = temp->next;
        delete temp;
        temp = next;
    }
}

void ItemOptionsll::insert(std::string val) {
    ItemOptionsNode* new_node = new ItemOptionsNode(val);
    new_node->data = val;
    new_node->next = NULL;

    if (head == NULL) {
        head = new_node;
    } else {
        ItemOptionsNode* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void ItemOptionsll::display() {
    ItemOptionsNode* current = head;

    while (current != NULL) {
        
        std::cout << current->data;
        if(current->next != NULL){
            std::cout << ", " ;
        }
        current = current->next;
    }

    std::cout << std::endl;
}

int ItemOptionsll::getTotalLength(){
    ItemOptionsNode* current = head;
    int length = 0;
    while (current != NULL) {
        length += current->data.length();
        
        current = current->next;
    }
    return length;
}