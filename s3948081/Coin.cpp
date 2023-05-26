#include "Coin.h"
 
 // implement functions for managing coins; this may depend on your design.
Coin::Coin() {
    denom = Denomination::INVALID;
    count = 0;
}

Coin::Coin(Denomination denom, unsigned count) {
    this->denom = denom;
    this->count = count;
}

Coin::~Coin() {
    // not required 
}