#ifndef MODIFIEDNODE_H
#define MODIFIEDNODE_H
#include <string> 
#include "Coin.h"
#include "ItemOptionsll.h"


// Display coins indent
#define COINSPACE 10

// Empty file line count
#define NODATA 0

// Price tokens
#define DOLCENT 2

// CENT VALUES
#define TENDOLLAR "1000"
#define FIVDOLLAR "500"
#define TWODOLLAR "200"
#define ONEDOLLAR "100"
#define FIFTYCENT "50"
#define TWENTCENT "20"
#define TENCENTS "10"
#define FIVECENT "5"

// Menu Indent 4 spaces
#define MENU_INDENT "    "

// Number of whitespaces in item name menu
#define ITEM_COL_SPACE 41

// Stock elements, needs 5 for the file to be valid
#define STOCK_COLS 5

//Stock elements, for modified data
#define MODIFIED_STOCK_COLS 6

// Delimiter for stock data file
#define STOCKDELIM "|"

// Delimiter for coins data file
#define COINSDELIM ","

//The length of the id string not counting the nul terminator
#define IDLEN 5

//The maximum length of a product name not counting the nul terminator
#define NAMELEN 40

//The maximum length of a product description not counting the nul terminator.
#define DESCLEN 255

//The default coin level to reset the coins to on request
#define DEFAULT_COIN_COUNT 20

//The default stock level that all new stock should start at and that we should reset to on restock
#define DEFAULT_STOCK_LEVEL 20

//The number of denominations of currency available in the system 
#define NUM_DENOMS 8

// Delimiter for price data type
#define PRICEDELIM "."

//The number of colums for a price object to be valid
#define PRICE_COLS 2
//THE make length of a cents or dollars component
#define PRICESIZE 2
//options for the main menu
#define MENUOPTION1 "1"
#define MENUOPTION2 "2"
#define MENUOPTION3 "3"
#define MENUOPTION4 "4"
#define MENUOPTION5 "5"
#define MENUOPTION6 "6"
#define MENUOPTION7 "7"
#define MENUOPTION8 "8"
#define MENUOPTION9 "9"

//option to request help
#define HELPOPTION "help"

// /**
//  * a structure to represent a price. One of the problems with the floating
//  * point formats in C++ like float and double is that they have minor issues
//  * of inaccuracy due to rounding. In the case of currency this really is
//  * not acceptable so we introduce our own type to keep track of currency.
//  **/
// class ModifiedPrice
// {
// public:
//     // The dollar value, and the cents value for some price
//     unsigned dollars, cents;
// };

/**
 * data structure to represent a stock item within the system
 **/
class ModifiedStock
{
public:
    //the unique id for this item
    std::string id;

    //the name of this item
    std::string name;
    
    //the description of this item   
    std::string description;
    
    //the price of this item
    Price price;
    
    // how many of this item do we have on hand? 
    unsigned on_hand;    

    //different item options
    ItemOptionsll* itemOptions;
};

/**
 * the node that holds the data about an item stored in memory
 **/
class ModifiedNode
{
public:
    ModifiedNode();
    ~ModifiedNode();

    void createNode(std::string ID, std::string name, std::string desc, Price price, int on_hand, ItemOptionsll* itemOptions);

    // pointer to the data held for the node 
    ModifiedStock* data;
    // pointer to the next node in the list 
    ModifiedNode* next;
    // pointer to the previous node in the list 
    ModifiedNode* prev;
};

#endif // MODIFIEDNODE_H