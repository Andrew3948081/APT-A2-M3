#include "DoublyLinkedList.h"
#include <iostream>
#include <vector>

// constructor 
DoublyLinkedList::DoublyLinkedList() {
    head = nullptr;
}

//deconstructor 
DoublyLinkedList::~DoublyLinkedList() {
    ModifiedNode* current = head;
    while (current != nullptr) {
        ModifiedNode* next = current->next;
        delete current;
        current = next;
    }
}



bool DoublyLinkedList::addNode(ModifiedNode* newNode) {
    //loop trhough linked list and add to the end of the code
    if (this->head == nullptr) {
        this->head = newNode;
        return true;
    }
    ModifiedNode* current = this->head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newNode;
    newNode->prev = current;
    return true;

}

//updating stock count
void DoublyLinkedList::updateStockCount(std::string IDsearch) {
    ModifiedNode* currNode = this->head;
    bool itemUpdated = false;

    while ((currNode != nullptr) && !itemUpdated) {
        if (currNode->data->id == IDsearch) {
            currNode->data->on_hand -= 1;
            itemUpdated = true;
        }

        else {
            currNode = currNode->next;
        }
    }
}

ModifiedNode* DoublyLinkedList::searchID(std::string IDsearch) {
    ModifiedNode* currNode = this->head;
    ModifiedNode* returnNode = nullptr;

    while ((currNode != nullptr) && (returnNode == nullptr)) {
        if (currNode->data->id == IDsearch) {
            returnNode = currNode;
        }

        else {
            currNode = currNode->next;
        }
    }

    return returnNode;
}

//delete
bool DoublyLinkedList::deleteNode(std::string id){
    if(this->head){
        ModifiedNode* currNode = this->head;
        if(this->head->data->id == id){
            //delete head
            std::cout << "\"" << this->head->data->id << " - " << this->head->data->name << " - " ;
            std::cout << this->head->data->description << "\" has been removed from the system."  <<std::endl;
            this -> head = currNode->next;
            this -> head -> prev = nullptr;
            delete currNode;

            return true;
        }

        while(currNode->next){
             if(currNode->data->id == id){
                //remove current node and set previous node's next to current node's next
                std::cout << "\"" << currNode->data->id << " - " << currNode->data->name << " - ";
                std::cout << currNode->data->description << "\" has been removed from the system." <<std::endl;
                ModifiedNode* prevNode = currNode -> prev;
                ModifiedNode* nextNode = currNode -> next;
                prevNode -> next = nextNode;
                if(nextNode != nullptr) {
                    nextNode -> prev = prevNode;
                }
                delete currNode;
                return true;

            }
            currNode = currNode->next;
        } 
        //node not found
        return false;
    }
    else{
        //list empty 
        return false;
    }
}

std::string DoublyLinkedList::getLargestId(){
    ModifiedNode* currNode = this->head;
    std::string largestId;
    while(currNode != nullptr){
        ModifiedStock* data = currNode->data;
        if (largestId.empty() || data->id > largestId) {
            largestId = data->id;
        }
        currNode = currNode->next;
    }
    return largestId;
}



void DoublyLinkedList::displayItems(){
    
    //put linked list into vecto
    std::vector<ModifiedStock*> values;
    ModifiedNode* current = head;
    while (current != nullptr) {
        values.push_back(current->data);
        current = current->next;
    }
    //sort list
    for (size_t i = 0; i < values.size(); i++) {
        for (size_t j = i + 1; j < values.size(); j++) {
            if (values[i]->name > values[j]->name) {
                std::swap(values[i], values[j]);
            }
        }
    }
 

    for (const ModifiedStock* data : values) {
        std::cout << data->id << "|" << data->name;
        std::cout.width(ITEM_COL_SPACE - data->name.length());
        std::cout << std::right << "|" << data->on_hand << "         |$ " << data->price.dollars << ".";
        if (data->price.cents == 0) {
            std::cout << "00";
        }
        else if (data->price.cents < 10) {
            std::cout << "0" << data->price.cents; 
        }
        else {
            std::cout << data->price.cents; 
        }
        //item options
        std::cout << " | ";
        data->itemOptions->display();
        
    }
    std::cout << std::endl;
}

void DoublyLinkedList::resetStocks(){
    ModifiedNode* currNode = this->head;
    while(currNode != nullptr){
        currNode->data->on_hand = DEFAULT_STOCK_LEVEL;
        currNode = currNode->next;
    }
    std::cout << "All stock has been reset to the default level of " << DEFAULT_STOCK_LEVEL << std::endl;
}

std::string DoublyLinkedList::itemOptionsBorder(){
    //set length to a min value of 15
    int length = 15;
    ModifiedNode* currNode = this->head;
    //get the largest space required for item options
    int space = 0;
    while(currNode != nullptr){
        int itemOptsLen = currNode->data->itemOptions->getTotalLength();
        if(itemOptsLen > length){
            space+=5;
            length = itemOptsLen;
        }
        currNode = currNode->next;
    }
    length += space;
    //print out the remaining lines
    std::string output = "";
    for (int i = 0; i <= length; i++) {
        output += '-';
    }
    return output;
}