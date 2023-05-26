#ifndef PURCHASE_ITEM
#define PURCHASE_ITEM

#include <iostream>
#include <fstream>
#include "LinkedList.h"
#include "helper.h"
#include "DoublyLinkedList.h"

/**
 * Create a definition for denomination into total cents
*/
#define FIVE_CENTS_IN_CENTS 5
#define TEN_CENTS_IN_CENTS 10
#define TWENTY_CENTS_IN_CENTS 20
#define FIFTY_CENTS_IN_CENTS 50
#define ONE_DOLLAR_IN_CENTS 100
#define TWO_DOLLARS_IN_CENTS 200
#define FIVE_DOLLARS_IN_CENTS 500
#define TEN_DOLLARS_IN_CENTS 1000

/**
 * Create a definition of -1 indicating that it is not found
*/
#define NOT_FOUND -1

/**
 * --------------------------------------------------------
 * Definition of structs
 * --------------------------------------------------------
*/

/**
 * Create a struct that handles:
 * a) did the item get purchased? (bool purchased)
 * b) what is the change that should be given? (int amountOfChange)
*/
struct ItemPurchasedInfo {
    bool purchased = false;
    int amountOfChange = 0;
};

/**
 * Create a struct that handles:
 * a) can the change be given? (bool validChange)
 * b) what is the description of the change given? (std::string descriptionOfChange)
*/
struct ChangeGivenInfo {
    bool validChange = false;
    std::string descriptionOfChange = "";
};

/**
 * --------------------------------------------------------
 * End of definition of structs
 * --------------------------------------------------------
*/

/**
 * --------------------------------------------------------
 * Definition of functions
 * --------------------------------------------------------
*/

/**
 * Setter functions so that the contents from ppd.cpp can be updated in PurchaseItem.cpp
*/
void setStockList(LinkedList* stockListPPD);
void setWallet(std::vector<Coin>* walletPPD);
void modifiedSetStockList(DoublyLinkedList* stockListPPD);

/**
 * Getter functions so that the contents from PurchaseItem.cpp can be updated in ppd.cpp
*/
LinkedList* getStockList();
std::vector<Coin>* getWallet();
DoublyLinkedList* modifiedGetStockList();

/**
 * Search the available stock by an ID
*/
Node* getItemByID(std::string ID);
ModifiedNode* modifiedGetItemByID(std::string ID);
/**
 * Check if the user entered ctrl-d or ""
*/
bool checkInputExists(std::string input);

/**
 * Check if the input is correct
*/
bool checkValidInput(std::string ID);
bool modifiedCheckValidInput(std::string ID);
/**
 * Prompts the user and takes input
*/
void PurchaseItemMenu();
/**
 * Prompts the user and takes input
*/
void modifedPurchaseItemMenu();

/**
 * Convert a Price object to a string description (e.g Price(3, 50) -> $3.50)
*/
std::string priceToString(Price price);

/**
 * Convert a Price object to an int (total cents) (e.g Price(3, 50) -> 350)
*/
int priceToCents(Price price);

/**
 * Convert an int (total cents) to a Price object (e.g 350 -> Price(3, 50))
*/
Price centsToPrice(int cents);

/**
 * Convert a denomination to an int (total cents) (e.g FIVE_CENTS -> 5)
*/
int denomToCents(Denomination coinType);

/**
 * Convert an int (total cents) to it's denominaton (e.g 5 -> FIVE_CENTS)
*/
Denomination centsToDenom(int coinValue);

/**
 * Update the vending machine's wallet with the chosen note/coin if it exists
*/
bool checkWallet(Denomination moneyType);

/**
 * Check to see if a certain amount of money is a valid denomination of money
*/
bool searchValidDenoms(int cents);

/**
 * Reset all global variables
*/
void resetDefaultValues();

/**
 * Return the index of a particular note/coin in the vending machine's wallet
*/
int findIndexOfDenom(int cents);

/**
 * Add the notes/coins that were used to pay for the item to the vending machine's wallet
*/
void completePayment(std::string itemID);
void modifiedCompletePayment(std::string itemID);

/**
 * Handles the bulk of logic for purchasing an item
*/
ItemPurchasedInfo purchasingItem(int amountLeftToPay);
/**
 * Handles the rest of the logic for purchasing an item
*/
void purchaseItem(std::string ID);
/**
 * Handles the bulk of logic for purchasing an item
*/
ItemPurchasedInfo modifiedPurchasingItem(int amountLeftToPay);
/**
 * Handles the rest of the logic for purchasing an item
*/
void modifiedPurchaseItem(std::string ID);

/**
 * Return in string format the change that was given
*/
std::string printChangeGiven();
ChangeGivenInfo calculateChange(Price change);

/**
 * --------------------------------------------------------
 * End of definitions
 * --------------------------------------------------------
*/

#endif