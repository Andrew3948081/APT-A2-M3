#include "ItemOptionsll.h"
#include <iostream>


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

bool ItemOptionsll::itemExist(const std::string s){
    ItemOptionsNode* current = head;
    while (current != NULL) {
        if(current->data == s){
            return true;
        }
        
        current = current->next;
    }
    //item does not exist
    return false;
}

std::string ItemOptionsll::getItems() {
    ItemOptionsNode* current = head;
    std::string items;
    while (current != NULL) {
        
        items += current->data;
        if(current->next != NULL){
            items += "," ;
        }
        current = current->next;
    }
    return items;
}