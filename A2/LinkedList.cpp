#include "LinkedList.h"
#include <iostream>
#include <vector>

// constructor 
LinkedList::LinkedList() {
    head = nullptr;
}

//deconstructor 
LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}



bool LinkedList::addNode(Node* newNode) {
    //loop trhough linked list and add to the end of the code
    if (this->head == nullptr) {
        this->head = newNode;
        return true;
    }
    Node* current = this->head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newNode;
    return true;

}

//updating stock count
void LinkedList::updateStockCount(std::string IDsearch) {
    Node* currNode = this->head;
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

Node* LinkedList::searchID(std::string IDsearch) {
    Node* currNode = this->head;
    Node* returnNode = nullptr;

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
bool LinkedList::deleteNode(std::string id){
    if(this->head){
        Node* currNode = this->head;
        if(this->head->data->id == id){
            //delete head
            std::cout << "\"" << this->head->data->id << " - " << this->head->data->name << " - " ;
            std::cout << this->head->data->description << "\" has been removed from the system."  <<std::endl;
            this -> head = currNode->next;
            delete currNode;

            return true;
        }

        while(currNode->next){
            if(currNode->next->data->id == id){
                //remove next node and set current nodes next to next nodes next
                std::cout << "\"" << currNode->next->data->id << " - " << currNode->next->data->name << " - ";
                std::cout << currNode->next->data->description << "\" has been removed from the system."  <<std::endl;
                Node* newNext = currNode->next->next;
                delete currNode->next;
                currNode->next = newNext;
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

std::string LinkedList::getLargestId(){
    Node* currNode = this->head;
    std::string largestId;
    while(currNode != nullptr){
        Stock* data = currNode->data;
        if (largestId.empty() || data->id > largestId) {
            largestId = data->id;
        }
        currNode = currNode->next;
    }
    return largestId;
}



void LinkedList::displayItems(){
    
    //put linked list into vecto
    std::vector<Stock*> values;
    Node* current = head;
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
 

    for (const Stock* data : values) {
        std::cout << data->id << "|" << data->name;
        std::cout.width(ITEM_COL_SPACE - data->name.length());
        std::cout << std::right << "|" << data->on_hand << "         |$ " << data->price.dollars << ".";
        if (data->price.cents == 0) {
            std::cout << "00" << std::endl;
        }
        else if (data->price.cents < 10) {
            std::cout << "0" << data->price.cents << std::endl;
        }
        else {
            std::cout << data->price.cents << std::endl;
        }
        
    }
}

void LinkedList::resetStocks(){
    Node* currNode = this->head;
    while(currNode != nullptr){
        currNode->data->on_hand = DEFAULT_STOCK_LEVEL;
        currNode = currNode->next;
    }
    std::cout << "All stock has been reset to the default level of " << DEFAULT_STOCK_LEVEL << std::endl;
}