#include <iostream>
#include <fstream>
#include <vector>
#include "LinkedList.h"
#include "helper.h"
#include "Coin.h"
#include "ModifiedPurchaseItem.h"

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

/**
 * Getter functions so that the contents from PurchaseItem.cpp can be updated in ppd.cpp
*/
LinkedList* getStockList();
std::vector<Coin>* getWallet();

/**
 * Search the available stock by an ID
*/
Node* getItemByID(std::string ID);

/**
 * Check if the user entered ctrl-d or ""
*/
bool checkInputExists(std::string input);

/**
 * Check if the input is correct
*/
bool checkValidInput(std::string ID);

/**
 * Prompts the user and takes input
*/
void purchaseItemMenu();

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

/**
 * Handles the bulk of logic for purchasing an item
*/
ItemPurchasedInfo purchasingItem(int amountLeftToPay);
/**
 * Handles the rest of the logic for purchasing an item
*/
void purchaseItem(std::string ID);

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

/**
 * --------------------------------------------------------
 * Definition of Global Variables 
 * --------------------------------------------------------
*/

/**
 * Create copies of the LinkedList stockList and the vector wallet, that are found in ppd.cpp
*/
LinkedList* stockListPi;
std::vector<Coin>* walletPi;
/**
 * Create a vector that stores a list of different amounts of money
*/
std::vector<int> listOfDenoms;

/**
 * Define different flags (mostly used for recursive functions so they are not accidentally 
 * defined multiple times or changed during recursion unintentionally)
*/
int finalChange = 0;
bool finalChangeEdited = false;
bool itemPurchased = false;
bool wantToExit = false;
bool inputExists = true;

/**
 * --------------------------------------------------------
 * End of definitions
 * --------------------------------------------------------
*/

/**
 * --------------------------------------------------------
 * Functions
 * --------------------------------------------------------
*/

void setStockList(LinkedList* stockListPPD) {
    /**
     * Set the contents of the stockList copy
    */
    // set the stockList copy to what stockList is in PPD
    stockListPi = stockListPPD;
}

void setWallet(std::vector<Coin>* walletPPD) {
    /**
     * Set the contents of the wallet copy
    */
    walletPi = walletPPD;
}

LinkedList* getStockList() {
    /**
     * Return the copy of the stockList so that the stockList can be updated globally
    */
    return stockListPi;
}

std::vector<Coin>* getWallet() {
    /**
     * Return the copy of the wallet so that the wallet can be updated globally
    */
    return walletPi;
}

Node* getItemByID(std::string ID) {
    /**
     * Loop through the stockList LinkedList to try and find the item with id = ID
    */
    Node* item = stockListPi->searchID(ID);
    return item;
}

bool checkInputExists(std::string input) {
    bool inputExists = true;
    /**
     * If the user entered ctrl-d or "", the input does not exist
    */
    if ((std::cin.eof()) || (input.length() == 0)) {
        inputExists = false;
    }

    return inputExists;
}

bool checkValidInput(std::string ID) {
    bool validInput = true;
    /**
     * Search for the item to check if it exists
    */
    Node* item = getItemByID(ID);
    bool print = true;

    /**
     * If the user entered ctrl-d or "", it should not print any extra information as they wanted to cancel
    */
    if (!checkInputExists(ID)) {
        print = false;
    }
    
    /**
     * If the item is a nullptr, it means it is the default value thus ID does not exist
    */
    if (item == nullptr) {
        if (print) {
            std::cout << "Error: you did not enter a valid id. Please try again." << std::endl << std::endl;
        }
        
        validInput = false;
    }

    /**
     * Otherwise, if there is no available stock, the user cannot purchase the item
    */
    else if (item->data->on_hand == 0) {
        if (print) {
            std::cout << "Item is out of stock." << std::endl << std::endl;
        }
    
        validInput = false;
    }

    return validInput;
}

void purchaseItemMenu() {
    /**
     * Print the opening prompt
    */
    std::cout << "Please enter the id of the item you wish to purchase: ";

    std::string ID = Helper::readInput();

    
    if (ID == HELPOPTION){
            std::cout << "HELP: ENTER THE ID OF THE ITEM YOU WANT" << std::endl; 
            purchaseItemMenu();
    }
    else if (!checkInputExists(ID)) {
        /**
         * If the user entered ctrl-d or "", they wanted to cancel
        */
        std::cout << "The task Purchase Item failed to run successfully." << std::endl;
    }
    /**
     * Otherwise, if they did not enter a valid input (go to checkValidInput() to see what is valid), 
     * then recursively start this logic again
    */
    else if (!checkValidInput(ID)) {
        purchaseItemMenu();
    }
   
    /**
     * Otherwise, it can proceed to begin purchasing the item
    */
    else {
        purchaseItem(ID);
    }
}

std::string priceToString(Price price) {
    /**
     * Convert a price object to a string in format: "${dollars}.{cents}" (e.g "$3.50")
    */
    std::string priceDisplay = "$" + std::to_string(price.dollars) + ".";

    /**
     * Correctly format the printing of cents, e.g when it is 5 cents, it will print as .05 instead of 0.5
    */
    if (10 > price.cents) {
        priceDisplay += "0";
    }

    priceDisplay += std::to_string(price.cents);

    return priceDisplay;
}

int priceToCents(Price price) {
    /**
     * Convert a price object to an int (total cents) by,
     * Multiplying the dollars by 100, and adding the coins
    */
    int priceInt = (price.dollars) * 100 + price.cents;
    return priceInt;
}

Price centsToPrice(int cents) {
    /**
     * Convert an int (total cents) to a price object by,
    */
    Price price;

    /**
     * Setting dollars to the hundreth column (e.g 350 -> 3 dollars) and,
    */
    price.dollars = cents / 100;

    /**
     * Setting cents to the tenth, and one column (e.g 350 -> 50 cents)
    */
    price.cents = cents % 100;

    return price;
}

bool checkWallet(Denomination moneyType) {
    bool validCoin = false;

    /**
     * Find the index of the note/coin that is being searched
    */
    int coinValue = denomToCents(moneyType);
    int moneyTypeIndex = findIndexOfDenom(coinValue);

    /**
     * If the index is -1, it means the denomination is not in the vending machine's wallet
     * But if it's anything else,
    */
    if (moneyTypeIndex != NOT_FOUND) {
        /**
         * Check if there is any of that denomination remaining
        */
        int quantity = walletPi->at(moneyTypeIndex).count;

        if (quantity > 0) {
            /**
             * If so, we can use that note/coin
            */
            validCoin = true;
            walletPi->at(moneyTypeIndex).count -= 1;
        }
    }

    /**
     * Return if we used the note/coin (true) or didn't use the note/coin (false)
    */
    return validCoin;
}

int denomToCents(Denomination coinType) {
    int coinValue = 0;

    /**
     * Convert a denomination to an int of total cents
    */
    if (coinType == FIVE_CENTS) {
        coinValue = FIVE_CENTS_IN_CENTS;
    }

    else if (coinType == TEN_CENTS) {
        coinValue = TEN_CENTS_IN_CENTS;
    }

    else if (coinType == TWENTY_CENTS) {
        coinValue = TWENTY_CENTS_IN_CENTS;
    }

    else if (coinType == FIFTY_CENTS) {
        coinValue = FIFTY_CENTS_IN_CENTS;
    }

    else if (coinType == ONE_DOLLAR) {
        coinValue = ONE_DOLLAR_IN_CENTS;
    }

    else if (coinType == TWO_DOLLARS) {
        coinValue = TWO_DOLLARS_IN_CENTS;
    }

    else if (coinType == FIVE_DOLLARS) {
        coinValue = FIVE_DOLLARS_IN_CENTS;
    }

    else if (coinType == TEN_DOLLARS) {
        coinValue = TEN_DOLLARS_IN_CENTS;
    }

    return coinValue;
}

Denomination centsToDenom(int coinValue) {
    Denomination coinType = INVALID;

    /**
     * Convert an int of total cents to it's denomination
    */
    if (coinValue == FIVE_CENTS_IN_CENTS) {
        coinType = FIVE_CENTS;
    }

    else if (coinValue == TEN_CENTS_IN_CENTS) {
        coinType = TEN_CENTS;
    }

    else if (coinValue == TWENTY_CENTS_IN_CENTS) {
        coinType = TWENTY_CENTS;
    }

    else if (coinValue == FIFTY_CENTS_IN_CENTS) {
        coinType = FIFTY_CENTS;
    }

    else if (coinValue == ONE_DOLLAR_IN_CENTS) {
        coinType = ONE_DOLLAR;
    }

    else if (coinValue == TWO_DOLLARS_IN_CENTS) {
        coinType = TWO_DOLLARS;
    }

    else if (coinValue == FIVE_DOLLARS_IN_CENTS) {
        coinType = FIVE_DOLLARS;
    }

    else if (coinValue == TEN_DOLLARS_IN_CENTS) {
        coinType = TEN_DOLLARS;
    }

    return coinType;
}

bool searchValidDenoms(int coinValue) {
    /**
     * Equivalent to - 5c, 10c, 20c, 50c, $1, $2, $5, $10
    */
    std::vector<int> validDenominations = {FIVE_CENTS_IN_CENTS, TEN_CENTS_IN_CENTS, 
    TWENTY_CENTS_IN_CENTS, FIFTY_CENTS_IN_CENTS, ONE_DOLLAR_IN_CENTS, TWO_DOLLARS_IN_CENTS, 
    FIVE_DOLLARS_IN_CENTS, TEN_DOLLARS_IN_CENTS};
    bool validDenom = false;

    /**
     * Loop through each valid coin/note and, 
    */
    for (int i = 0; i < int(validDenominations.size()); i++) {
        /**
         * Find if the value that is being searched is valid or not
        */
        if (validDenominations[i] == coinValue) {
            validDenom = true;
        }
    }

    return validDenom;
}

void resetDefaultValues() {
    /**
     * Reset global variables to their default values
     * 
     * This ensures the variables have their default value since global variables are only defined 
     * once and not each time a new item is being bought
    */
    finalChangeEdited = false;
    itemPurchased = false;
    wantToExit = false;
    listOfDenoms.clear();
    inputExists = true;
}

int findIndexOfDenom(int cents) {
    /**
     * Convert total cents to it's denomination
    */
    Denomination moneyType = centsToDenom(cents);
    int foundIndex = NOT_FOUND;

    /**
     * Loop through each denomination that the vending machine can hold and,
    */
    for (int i = 0; i < int(walletPi->size()); i++) {
        /**
         * Find the index of the denomination that is being searched and,
        */
        Denomination currDenom = walletPi->at(i).denom;

        if (currDenom == moneyType) {
            foundIndex = i;
        }
    }

    /**
     * Return the index
    */
    return foundIndex;
}

void completePayment(std::string itemID) {
    /**
     * Loop through each note / coin that was used to pay for an item and, 
    */
    for (int i = 0; i < int(listOfDenoms.size()); i++) {
        /**
         * Add it to the vending machine's wallet
        */
        int indexOfDenom = findIndexOfDenom(listOfDenoms[i]);
        walletPi->at(indexOfDenom).count += 1;
    }

    /**
     * Update the stock of the item that was bought (-1 from the total stock)
    */
    stockListPi->updateStockCount(itemID);
}

ItemPurchasedInfo purchasingItem(int amountLeftToPay) {
    /**
     * Convert the total cents remaining to a Price object
    */
    Price amountLeftPrice = centsToPrice(amountLeftToPay);
    std::string inputMoneyString = "temp";
    int inputMoney = 0;
    /**
     * Create a struct ItemPurchasedInfo() that tracks both a) if the item was purchased, and b)
     * the amount of change that should be given
    */
    ItemPurchasedInfo itemPurchasedInfo = ItemPurchasedInfo();

    /**
     * If the amount left to pay is 0, or negative then the amount of money required to buy the item
     * has been paid
     * 
     * Therefore the item is purchased, and the function should exit
    */
    if (0 >= amountLeftToPay) {
        wantToExit = true;
        itemPurchased = true;
    }

    /**
     * Otherwise there is still money that is needed to be paid, and the user should be prompted
     * 
     * But to ensure there are no errors, there is a check that the item is not purchased, and the 
     * change that is needed to be given has not been set
    */
    else if ((!finalChangeEdited) && (!itemPurchased)) {
        std::cout << "You still need to give us " << priceToString(amountLeftPrice) << ": ";
        /**
         * Check if the user entered ctrl-d or "", as this would indicate they want to cancel
        */
       
        inputMoneyString = Helper::readInput();
       
        inputExists = checkInputExists(inputMoneyString);
        
        
    }

    /**
     * If the user entered ctrl-d or "", they want to cancel
     * 
     * Therefore, the function should exit, and the item is not purchased (the user can only 
     * enter an input if the item has not been purchased)
    */
    if (!inputExists) {
        wantToExit = true;
        itemPurchased = false;
    }

    /**
     * If the function should exit (and it hasn't tried to exit prior), set the amount of change
    */
    if (wantToExit && !finalChangeEdited) {
        finalChange = amountLeftToPay;
        finalChangeEdited = true;
    }

    /**
     * Otherwise, the user still needs to enter more money
    */
    else if ((!finalChangeEdited) && (inputExists)) {

        if(inputMoneyString == HELPOPTION){
            std::cout << "HELP: ENTER THE VALUE OF CURRENCY IN CENTS I.E. TO ENTER $1.00, TYPE 100" << std::endl; 
            purchasingItem(amountLeftToPay);
        }
        else if (!Helper::isNumber(inputMoneyString)) {
            /**
             * If the user doesn't enter a number, it cannot be used to pay for the item
             * Recursively call the function
            */
            std::cout << "Error: input was not a number. Please try again." << std::endl;
            std::cout << "Error: you did not enter a valid integer. Please try again." << std::endl;
            purchasingItem(amountLeftToPay);
        }

        /**
         * Otherwise, convert the input to an integer
        */
        else {
            inputMoney = stoi(inputMoneyString);
        }

        /**
         * If the denomination that the user entered is valid,
        */
        if (searchValidDenoms(inputMoney)) {
            /**
             * Subtract the value of the denomination from the total remaining
             * Keep track of the denomination that was given (so that it can be 
             * added to the vending machine's wallet later)
             * Recursively call the function again
            */
            amountLeftToPay -= inputMoney;
            listOfDenoms.push_back(inputMoney);
            purchasingItem(amountLeftToPay);
        }

        /**
         * Otherwise, it's not an acceptable note or coin and,
        */
        else if (inputExists && inputMoneyString != HELPOPTION) {
            /**
             * Recursively call the function again
            */
            Price attemptedPayment = centsToPrice(inputMoney);
            std::cout << "Error: " << priceToString(attemptedPayment) << " is not a valid denomination of money. Please try again." << std::endl;
            purchasingItem(amountLeftToPay);
        }
    }

    /**
     * Set whether or not the item was purchased, and the change that should be given to the user
    */
    itemPurchasedInfo.purchased = itemPurchased;
    itemPurchasedInfo.amountOfChange = finalChange;

    /**
     * Return the struct containing information on the purchase
    */
    return itemPurchasedInfo;
}

std::string printChangeGiven() {
    std::string changeString = "";
    /**
     * Loop through each coin/note that should be given as change and, 
    */
    for (int i = 0; i < int(listOfDenoms.size()); i++) {
        int currCoin = 0;

        /**
         * Create a string represenation of the change that was given
         * If the change is a dollar note, it's in the format of " ${dollar}" - e.g "$2"
         * If the change is a cents coin, it's in the format of " {cents}c" - e.g "50c"
        */
        if (listOfDenoms[i] >= ONE_DOLLAR_IN_CENTS) {
            currCoin = listOfDenoms[i] / 100;
            changeString += " $" + std::to_string(currCoin);
        }

        else {
            currCoin = listOfDenoms[i] % 100;
            changeString += " " + std::to_string(currCoin) + "c";
        }
    }

    return changeString;
}

ChangeGivenInfo calculateChange(Price change) {
    /**
     * Use a struct - ChangeGivenInfo() to return both a) if change was given, and b) what change was given
    */
    ChangeGivenInfo changeGivenInfo = ChangeGivenInfo();
    bool machineHasMoney = true;
    std::vector<Coin>* machineWalletCopy = walletPi;

    /**
     * If the amount of change that can be given is greater than $10, remove $10 from the amount left 
     * (only if the machine has a $10 available)
     * Keep track that the vending machine gave a $10 note back to the user (adding to listOfDenoms),
     * and repeat for each subsequent denomination
    */

    if ((change.dollars >= 10) && checkWallet(centsToDenom(TEN_DOLLARS_IN_CENTS))) {
        change.dollars -= 10;
        listOfDenoms.push_back(TEN_DOLLARS_IN_CENTS);
        calculateChange(change);
    }

    else if ((change.dollars >= 5) && checkWallet(centsToDenom(FIVE_DOLLARS_IN_CENTS))) {
        change.dollars -= 5;
        listOfDenoms.push_back(FIVE_DOLLARS_IN_CENTS);
        calculateChange(change);
    }

    else if ((change.dollars >= 2) && checkWallet(centsToDenom(TWO_DOLLARS_IN_CENTS))) {
        change.dollars -= 2;
        listOfDenoms.push_back(TWO_DOLLARS_IN_CENTS);
        calculateChange(change);
    }

    else if ((change.dollars >= 1) && checkWallet(centsToDenom(ONE_DOLLAR_IN_CENTS))){
        change.dollars -= 1;
        listOfDenoms.push_back(ONE_DOLLAR_IN_CENTS);
        calculateChange(change);
    }
    
    else if ((change.cents >= 50) && checkWallet(centsToDenom(FIFTY_CENTS_IN_CENTS))) {
        change.cents -= 50;
        listOfDenoms.push_back(FIFTY_CENTS_IN_CENTS);
        calculateChange(change);
    }

    else if ((change.cents >= 20) && checkWallet(centsToDenom(TWENTY_CENTS_IN_CENTS))) {
        change.cents -= 20;
        listOfDenoms.push_back(TWENTY_CENTS_IN_CENTS);
        calculateChange(change);
    }

    else if ((change.cents >= 10) && checkWallet(centsToDenom(FIVE_CENTS_IN_CENTS))) {
        change.cents -= 10;
        listOfDenoms.push_back(TEN_CENTS_IN_CENTS);
        calculateChange(change);
    }

    else if ((change.cents >= 5) && checkWallet(centsToDenom(TEN_CENTS_IN_CENTS))) {
        change.cents -= 5;
        listOfDenoms.push_back(FIVE_CENTS_IN_CENTS);
        calculateChange(change);
    }

    /**
     * If there is still money left over, the machine must have run out of notes / coins
    */

    else if ((change.cents) || (change.dollars)) {
        machineHasMoney = false;
    }

    std::string changeString = "";

    /**
     * If the machine doesn't have enough money, don't give any change 
    */
    if (!machineHasMoney) {
        setWallet(machineWalletCopy);
        changeGivenInfo.validChange = false;
    }

    /**
     * Otherwise, get the string representation of the change given
    */
    else {
        std::string changeString = printChangeGiven();

        changeGivenInfo.validChange = true;
        changeGivenInfo.descriptionOfChange = changeString;
    }

    /**
     * Return the struct containing information on the change given
    */
    return changeGivenInfo;
}

void purchaseItem(std::string ID) {
    /**
     * Search for the stock by the ID that was entered by the user
     * All validation is handled in getItemByID()
    */
    Node* item = getItemByID(ID);

    /**
     * There is a new item being purchased so all flags and vectors should be reset
    */
    resetDefaultValues();

    std::string itemID = item->data->id;
    std::string itemName = item->data->name;
    std::string itemDescription = item->data->description;
    Price itemPrice = item->data->price;

    /**
     * Print the opening menu and tutorial
    */
    std::cout << "You have selected \"" << itemName << " - " << itemDescription << "\". ";
    std::cout << "This will cost you " << priceToString(itemPrice) << "." << std::endl;
    std::cout << "Please hand over the money - type in the value of each note/coin in cents." << std::endl;
    std::cout << "Press enter or ctrl-d on a new line to cancel this purchase: " << std::endl;

    int itemPriceCents = priceToCents(itemPrice);

    /**
     * Start purchasing an item
    */
    resetDefaultValues();
    ItemPurchasedInfo itemPurchasedInfo = purchasingItem(itemPriceCents);
    int changeToGiveCents = itemPurchasedInfo.amountOfChange;
    bool purchased = itemPurchasedInfo.purchased;

    /**
     * If there was an item that was purchased,
    */
    if (purchased) {
        /**
         * Add the coins to the vending machine, and remove 1 stock
        */
        completePayment(itemID);

        /**
         * If there is change to be given,
        */
        if (0 > changeToGiveCents) {
            Price changeToGivePrice = centsToPrice(abs(changeToGiveCents));

            /**
             * Get the string explanation of what change in coins was given back
            */
            resetDefaultValues();
            ChangeGivenInfo changeGivenInfo = calculateChange(changeToGivePrice);
            bool validChange = changeGivenInfo.validChange;
            std::string descriptionOfChange = changeGivenInfo.descriptionOfChange;

            /**
             * Print that either the change was given, or it couldn't be completed
            */
            if (validChange) {
                std::cout << "Here is your " << itemName << " and your change of " << priceToString(changeToGivePrice) << ":";
                std::cout << descriptionOfChange << std::endl;
            }

            else {
                std::cout << "Error: The change cannot be given as the machine does not have enough money. The ";
                std::cout << "purchase will not go through." << std::endl;
            }
        }
    }

    /**
     * If there was not an item that got purchased (the purchase was cancelled),
    */
    else {
        std::cout << "Change of mind - here is your change:" << std::endl;
        
        /**
         * And if there was any coins that were given to the machine, refund them
        */
        if (listOfDenoms.size() != 0) {
            std::string changeString = printChangeGiven();
            std::cout << changeString;
        }

        std::cout << std::endl;       
    }

    std::cout << "Please come again soon." << std::endl;
}

/**
 * --------------------------------------------------------
 * End of functions
 * --------------------------------------------------------
*/