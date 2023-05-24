#include <iostream>
#include <fstream>
#include "LinkedList.h"
#include "helper.h"
#include "PurchaseItem.h"
#include "DoublyLinkedList.h"



/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/


//void mainMenu();
bool mainMenu(LinkedList* stockList, std::vector<Coin> wallet, std::vector<std::string> fileName);
// MENU OPTION 1
void printItems(LinkedList* stockList);
// MENU OPTION 2
void purchaseItemMenu();
// MENU OPTION 3
void saveExit(LinkedList* sL, std::vector<Coin> wlt, std::vector<std::string> fileName);
// bool purchasingItem();
void purchaseItem(std::string ID);
// MENU OPTION 4
bool addItem(LinkedList* stockList);
// MENU OPTION 5
bool deleteItem(LinkedList* stockList);
// MENU OPTION 6
void displayCoins(std::vector<Coin> wallet);
//MENU OPTION 7
void setDefaultCoinCounts(std::vector<Coin>& wallet);

//modified main menu
bool modifiedMainMenu(DoublyLinkedList* stockList, std::vector<Coin> wallet, std::vector<std::string> fileName);
// MENU OPTION 1
void modifiedPrintItems(DoublyLinkedList* stockList);
// MODIFIED MENU OPTION 2
void modifiedPurchaseItemMenu();
// MENU OPTION 3
void modifiedSaveExit(DoublyLinkedList* sL, std::vector<Coin> wlt, std::vector<std::string> fileName);
// MODIFIED MENU OPTION 4
bool modifiedAddItem(DoublyLinkedList* stockList);
// MODIFIED MENU OPTION 5
bool modifiedDeleteItem(DoublyLinkedList* stockList);

int main(int argc, char **argv)
{
    /* validate command line arguments */
    // Argument Error flags
    bool noArg = false;
    bool argError1 = false;
    bool argError2 = false;
    bool argError3 = false;

    // Stock Error flags
    int getLineCount = NODATA;
    bool isEmpty = false;
    bool prcError = false;
    bool isInvalid = false;
    bool qtyError = false;
    
    // Coin Error flags
    bool coinIsEmpty = false;
    bool badDenom = false;
    bool badCount = false;
    bool coinDupe = false;

    //Version Error flags 
    bool versionError = false;

    //initialise linked list and coin vector
    LinkedList* stockList = new LinkedList;
    std::vector<Coin> wallet;
    std::vector<std::string> fileName;

    //init modified linked list 
    

    bool runModified = false;
    DoublyLinkedList* modifiedStockList = new DoublyLinkedList;

   
    
    if (argc == 4) {
        // HANDLE FIRST COMMAND LINE ARGUMENT
        // Stock file handler/validator
        std::string arg1(argv[1]);
        fileName.push_back(arg1);
        
        // Each row is an object called stock
        std::ifstream stockFile(arg1); // Open stock file
        bool quit = false;

        // HANDLE THE THIRD COMMAND LINE ARGUMENT
        
        if (!Helper::isbool(argv[3])){
            //argument 3 is incorrect
            std::cout << "arg3 error: [m3]" << std::endl;
            argError3 = true; 
            versionError = true; 
            quit = true;
        }
        else{
            //if arg is boolean
          
            if (std::string(argv[3]) == "true"){
                runModified = true;
            }
            else{
                runModified = false;
            }
        }


        // Checks if the file has data inside
        if (stockFile.good() && stockFile.is_open()) {
            std::string stockLine = "";

            // Create a linkedlist heap of stock list
            while(std::getline(stockFile, stockLine) && quit == false) {
                Price price;
                std::vector<std::string> token;
                Helper::splitString(stockLine, token, STOCKDELIM);
                //std::cout << token[1] << std::endl;

                // Check if the line has the 5 elements, [id],[name],[desc],[price],[on_hand]
                if (int(token.size()) == STOCK_COLS || (int(token.size()) == MODIFIED_STOCK_COLS && runModified == true)) {

                    // // Create a stock node heap
                    Node* stockNode = new Node();
                    ModifiedNode* modifiedStockNode = new ModifiedNode();
    
                    
                    // Check if the price has a '.' (full stop) char
                    std::string* stockPrice = &token[3];
                    bool checkPrice = Helper::priceValidator(stockPrice);
                    if (!checkPrice) {
                        prcError = true;
                       
                        quit = true;
                    } 
                    // If the price is valid, input stock price object values
                    else {
                        std::vector<std::string> priceToken;
                        Helper::splitString(token[3], priceToken, PRICEDELIM);
                        bool dolValid = false;
                        bool centValid = false;

                        if (priceToken.size() == 2){
                            dolValid = Helper::isValidDollar(priceToken[0]);
                            centValid = Helper::isValidCent(priceToken[1]);
                        }
                        
                        if (dolValid && centValid) {
                            price.dollars = std::stoi(priceToken[0]);
                            price.cents = std::stoi(priceToken[1]);

                        }
                        else {
                            prcError = true;
                            
                            quit = true;
                            
                        }
                    }

                    // Check if quantity is a valid number
                    bool qtyValid = Helper::isNumber(token[4]);
                    if (qtyValid){
                        if(runModified == true){
                            ItemOptionsll* itemOptsLL = new ItemOptionsll;
                           
                            //if running the modified program do this

                            //handle item options
                            //std::cout<<token[5]<<std::endl;
                            if (Helper::isWhitespaceOrNewline(token[5])){ 
                                //no itemopts maybe make blank
                               
                            }
                            else if (token[5].find(",") != std::string::npos) {
                                //split string into vector and put into LL
                                
                                std::vector<std::string> optionsToken;
                                Helper::splitString(token[5], optionsToken, ",");
                                for(unsigned int i = 0; i < optionsToken.size(); i++)
                                {
                                   
                                   //newItemOptions->data = &optionsToken[i];
                                   //newItemOptions->setNode(optionsToken[i]);
                                   itemOptsLL->insert(optionsToken[i]);
                                }
                            }
                            else{
                                //single item 
                            
                                itemOptsLL->insert(token[5]);
                            }
                           
                            //itemOptsLL->display();

                            modifiedStockNode->createNode(token[0],token[1],token[2],price,std::stoi(token[4]), itemOptsLL);
                            // Append node to linkedlist
                            modifiedStockList->addNode(modifiedStockNode);
                            
                        }
                        else{
                            stockNode->createNode(token[0],token[1],token[2],price,std::stoi(token[4]));
                            // Append node to linkedlist
                            stockList->addNode(stockNode);
                        }
                        
                    }
                    else {
                        // Quantity error flag
                        qtyError = true;
                       
                    }
                    
                    // Confirm node addage
                    getLineCount++;
                   
                }
                else {
                    quit = true;
                    isInvalid = true;
              
                }
                if (qtyError == true) {
                    quit = true;
                }
            }
            if (getLineCount == NODATA && !isInvalid) {
                isEmpty = true;

            }
        } else {
            std::cout << "arg1 error: [stock.dat]" << std::endl;
            argError1 = true;
        }
        // HANDLE THE SECOND COMMAND LINE ARGUMENT
        // Coins file handler
        std::string arg2(argv[2]);
        fileName.push_back(arg2);
        std::ifstream coinFile(arg2);

        quit = false;
        getLineCount = NODATA;
        if (coinFile.good() && coinFile.is_open()) {
            std::string coinLine = "";
            // Create a linked list of the coins list
            // LinkedList* coinList = new LinkedList;
            while(std::getline(coinFile, coinLine) && quit == false) {
                std::vector<std::string> coinsToken;
                Helper::splitString(coinLine, coinsToken, COINSDELIM);
                // Check the coin tokens denomination and assign to new Coin
                if (int(coinsToken.size()) == 2) {
                    Coin coin;
                    if (coinsToken[0] == "1000") {
                        coin.denom = TEN_DOLLARS;
                    } 
                    else if (coinsToken[0] == "500") {
                        coin.denom = FIVE_DOLLARS;
                    }
                    else if (coinsToken[0] == "200") {
                        coin.denom = TWO_DOLLARS;
                    }
                    else if (coinsToken[0] == "100") {
                        coin.denom = ONE_DOLLAR;
                    }
                    else if (coinsToken[0] == "50") {
                        coin.denom = FIFTY_CENTS;
                    }
                    else if (coinsToken[0] == "20") {
                        coin.denom = TWENTY_CENTS;
                    }
                    else if (coinsToken[0] == "10") {
                        coin.denom = TEN_CENTS;
                    }
                    else if (coinsToken[0] == "5") {
                        coin.denom = FIVE_CENTS;
                    }
                    else {
                        quit = true;
                        // Bad denomination error flag
                        badDenom = true;
                    }

                    std::string::const_iterator cntString = coinsToken[1].begin();
                    while (cntString != coinsToken[1].end() && std::isdigit(*cntString)) {
                        cntString++;
                    }
                    
                    if (!coinsToken[1].empty() && cntString == coinsToken[1].end()){
                        coin.count = std::stoi(coinsToken[1]);

                        // Check for coin duplicate
                        for (int i = 0; i < int(wallet.size()); i++) {
                            if (wallet[i].denom == coin.denom) {
                                coinDupe = true;
                                quit = true;
                            }
                        }
                        if (!coinDupe) {
                            wallet.push_back(coin);
                            
                        }
                    }
                    else {
                        // Count value error flag
                        badCount = true;
                        
                        quit = true;

                    }
                    getLineCount++;
                }
                else {
                    badCount = true;
                    quit = true;
                }
            }
            if (getLineCount == NODATA) {
                coinIsEmpty = true;
            }
        }
        else {
            std::cout << "arg2 error: [coins.dat]" << std::endl;
            argError2 = true;
        }
        
        coinFile.close();
        stockFile.close();

    }
    else {
        std::cout << "Error: invalid arguments passed in." << std::endl;
        std::cout << "Correct arguments are:" << std::endl;
        std::cout << "\t./ppd <stockfile> <coinfile> <m3>" << std::endl;
        std::cout << "Where <stockfile> and <coinfile> are two valid files in the expected format and ";
        std::cout << "<m3> is a boolean value that decides what configuration the program is in " << std::endl;
        
        noArg = true;
    }
   
    //Main menu goes here then we can handle userinput to run different functions
    if (!noArg && !argError1 && !argError2 && !argError3 && !isEmpty && !qtyError && !isInvalid && !prcError && 
        !coinDupe && !coinIsEmpty && !badDenom && !badCount && !versionError ) {

        if (runModified == true){
            //run program with milestone 3 modifications
            modifiedMainMenu(modifiedStockList, wallet, fileName);
        }
        else{
            mainMenu(stockList, wallet, fileName);
        }
        
    }
    
    // Error print statements
    if (isEmpty || qtyError || isInvalid || prcError) {
        std::cout << "Stock file arg error: ";
        if (isEmpty) {
            std::cout << "empty stock file" << std::endl;
        }
        else if (qtyError) {
            std::cout << "invalid quantity" << std::endl;
        }
        else if (isInvalid) {
            std::cout << "invalid item" << std::endl;
        }
        else if (prcError) {
            std::cout << "invalid price" << std::endl;
        }
    }
    if (coinIsEmpty || badDenom || badCount || coinDupe) {
        std::cout << "Coin file arg error: ";
        if (coinIsEmpty) {
            std::cout << "empty coin data" << std::endl;
        }
        else if (badDenom) {
            std::cout << "invalid coin denomination" << std::endl;
        }
        else if (badCount) {
            std::cout << "invalid coin count" << std::endl;
        }
        else if (coinDupe) {
            std::cout << "coin duplicate" << std::endl;
        }
    }
    if (versionError) {
        std::cout << "invalid version argument" << std::endl;
    }
    
    delete stockList;

    return EXIT_SUCCESS;
}

//Main Menu
bool mainMenu(LinkedList* stockList, std::vector<Coin> wallet, std::vector<std::string> fileName) {
    //initializing variables 
    std::string input;
    bool exit = false;
    bool saved = true;
    // main loop 
    while(!(std::cin.eof()) && !(exit)){
        std::cout << "Main Menu:" << std::endl;
        std::cout << "    1.Display Items" << std::endl;
        std::cout << "    2.Purchase Items" << std::endl;
        std::cout << "    3.Save and Exit" << std::endl;
        std::cout << "Administrator-Only Menu:" << std::endl;
        std::cout << "    4.Add Item" << std::endl;
        std::cout << "    5.Remove Item" << std::endl;
        std::cout << "    6.Display Coins" << std::endl;
        std::cout << "    7.Reset Stock" << std::endl;
        std::cout << "    8.Reset Coins" << std::endl;
        std::cout << "    9.Abort Program" << std::endl << std::endl;
        std::cout << "Select your option (1-9): ";

        //taking the input from user 
        input = Helper::readInput();

        //option 1 
        if(input == MENUOPTION1){
            printItems(stockList);
        }
        
        //option 2
        else if(input == MENUOPTION2){
            std::cout << "Purchase Item" << std::endl;
            std::cout << "-------------" << std::endl;
            std::vector<Coin>* walletPtr = &wallet;
            setStockList(stockList);
            setWallet(walletPtr);
            purchaseItemMenu();
            stockList = getStockList();
            walletPtr = getWallet();
            wallet = *walletPtr;
        }
        //option 3 
        else if(input == MENUOPTION3){
            saveExit(stockList, wallet, fileName);
            exit = true;
            saved = true;
        }
        //option 4
        else if(input == MENUOPTION4){
            if(addItem(stockList) == false){
                std::cout << "The task Add Item failed to run successfully." << std::endl; 
            }
            
        }
        //option 5
        else if(input == MENUOPTION5){
            if(deleteItem(stockList) == false){
                std::cout << "The task Remove Item failed to run successfully." << std::endl; 
            }
        }
        //option 6
        else if(input == MENUOPTION6){
            displayCoins(wallet);
        }
        //option 7
        else if(input == MENUOPTION7){
            stockList->resetStocks();
        }
        //option 8
        else if(input == MENUOPTION8){
            setDefaultCoinCounts(wallet);
            setWallet(&wallet);
        }
        //option 9
        else if(input == MENUOPTION9){
            exit = true;
            saved = false;
        }
        
        else if(Helper::emptyString(input)){
            //if user presses enter on empty line abort program
            exit = true;
            saved = false;
        }
        else if(!Helper::isMenuNumber(input)){
            //input is not number
            std::cout << "Error: input was not a number. Please try again." << std::endl << std::endl;

        }
        //input is beyond the number range in the main menu
        else {
            std::cout << "Error: menu item selected is not valid." << std::endl << std::endl; 
        }

    }

    return saved;
}

//Modified Main Menu
bool modifiedMainMenu(DoublyLinkedList* stockList, std::vector<Coin> wallet, std::vector<std::string> fileName) {
    //initializing variables 
    std::string input;
    bool exit = false;
    bool saved = true;
    // main loop 
    while(!(std::cin.eof()) && !(exit)){
        std::cout << "Main Menu:" << std::endl;
        std::cout << "    1.Display Items" << std::endl;
        std::cout << "    2.Purchase Items" << std::endl;
        std::cout << "    3.Save and Exit" << std::endl;
        std::cout << "Administrator-Only Menu:" << std::endl;
        std::cout << "    4.Add Item" << std::endl;
        std::cout << "    5.Remove Item" << std::endl;
        std::cout << "    6.Display Coins" << std::endl;
        std::cout << "    7.Reset Stock" << std::endl;
        std::cout << "    8.Reset Coins" << std::endl;
        std::cout << "    9.Abort Program" << std::endl << std::endl;
        std::cout << "Select your option (1-9): ";

        //taking the input from user 
        input = Helper::readInput();

        

        //option 1 
        if(input == MENUOPTION1){
            modifiedPrintItems(stockList);
        }
        //option 2
        else if(input == MENUOPTION2){
            std::cout << "Purchase Item" << std::endl;
            std::cout << "-------------" << std::endl;
            std::vector<Coin>* walletPtr = &wallet;
            modifiedSetStockList(stockList);
            setWallet(walletPtr);
            modifiedPurchaseItemMenu();
            stockList = modifiedGetStockList();
            walletPtr = getWallet();
            wallet = *walletPtr;
        }
        //option 3 
        else if(input == MENUOPTION3){
            modifiedSaveExit(stockList, wallet, fileName);
            exit = true;
            saved = true;
        }
        //option 4
        else if(input == MENUOPTION4){
            if(modifiedAddItem(stockList) == false){
                std::cout << "The task Add Item failed to run successfully." << std::endl; 
            }
            
        }
        //option 5
        else if(input == MENUOPTION5){
            if(modifiedDeleteItem(stockList) == false){
                std::cout << "The task Remove Item failed to run successfully." << std::endl; 
            }
        }
        //option 6
        else if(input == MENUOPTION6){
            displayCoins(wallet);
        }
        //option 7
        else if(input == MENUOPTION7){
            stockList->resetStocks();
        }
        //option 8
        else if(input == MENUOPTION8){
            setDefaultCoinCounts(wallet);
            setWallet(&wallet);
        }
        //option 9
        else if(input == MENUOPTION9){
            exit = true;
            saved = false;
        }
        else if(input == HELPOPTION){
            std::cout << "HELP: ENTER A NUMBER BETWEEN 1-9 TO DO THE CORRESPONDING TASK" << std::endl;
        }
        else if(Helper::emptyString(input)){
            //if user presses enter on empty line abort program
            exit = true;
            saved = false;
        }
        else if(!Helper::isMenuNumber(input)){
            //input is not number
            std::cout << "Error: input was not a number. Please try again." << std::endl << std::endl;

        }
        //input is beyond the number range in the main menu
        else {
            std::cout << "Error: menu item selected is not valid." << std::endl << std::endl; 
        }

    }

    return saved;
}

//saves and stores in file
void saveExit(LinkedList* sL, std::vector<Coin> wlt, std::vector<std::string> fileName){
    std::ofstream coinFile;
    coinFile.open(fileName[1]);
    for (int i = 0; i < int(wlt.size()); i++) {
        //std::cout << "saved" << std::endl;
        if (wlt[i].denom == FIVE_CENTS) {
            coinFile << "5," << wlt[i].count << std::endl; 
        } else if (wlt[i].denom == TEN_CENTS) {
            coinFile << "10," << wlt[i].count << std::endl; 
        } else if (wlt[i].denom == TWENTY_CENTS) {
            coinFile << "20," << wlt[i].count << std::endl; 
        } else if (wlt[i].denom == FIFTY_CENTS) {
            coinFile << "50," << wlt[i].count << std::endl; 
        } else if (wlt[i].denom == ONE_DOLLAR) {
            coinFile << "100," << wlt[i].count << std::endl; 
        } else if (wlt[i].denom == TWO_DOLLARS) {
            coinFile << "200," << wlt[i].count << std::endl; 
        } else if (wlt[i].denom == FIVE_DOLLARS) {
            coinFile << "500," << wlt[i].count << std::endl; 
        } else if (wlt[i].denom == TEN_DOLLARS) {
            coinFile << "1000," << wlt[i].count << std::endl; 
        }
    }
    
    std::ofstream stockFile;
    stockFile.open(fileName[0]);
        Node* ptr = sL->head;    
        while (ptr) {  
            stockFile << ptr->data->id << "|";
            stockFile << ptr->data->name << "|";
            stockFile << ptr->data->description << "|";
            stockFile << ptr->data->price.dollars << "." << ptr->data->price.cents << "|";
            stockFile << ptr->data->on_hand << std::endl;
            ptr = ptr->next;  
        }  

    coinFile.close();
    stockFile.close();
}
//saves and stores in file
void modifiedSaveExit(DoublyLinkedList* sL, std::vector<Coin> wlt, std::vector<std::string> fileName){
    std::ofstream coinFile;
    coinFile.open(fileName[1]);
    for (int i = 0; i < int(wlt.size()); i++) {
        //std::cout << "saved" << std::endl;
        if (wlt[i].denom == FIVE_CENTS) {
            coinFile << "5," << wlt[i].count << std::endl; 
        } else if (wlt[i].denom == TEN_CENTS) {
            coinFile << "10," << wlt[i].count << std::endl; 
        } else if (wlt[i].denom == TWENTY_CENTS) {
            coinFile << "20," << wlt[i].count << std::endl; 
        } else if (wlt[i].denom == FIFTY_CENTS) {
            coinFile << "50," << wlt[i].count << std::endl; 
        } else if (wlt[i].denom == ONE_DOLLAR) {
            coinFile << "100," << wlt[i].count << std::endl; 
        } else if (wlt[i].denom == TWO_DOLLARS) {
            coinFile << "200," << wlt[i].count << std::endl; 
        } else if (wlt[i].denom == FIVE_DOLLARS) {
            coinFile << "500," << wlt[i].count << std::endl; 
        } else if (wlt[i].denom == TEN_DOLLARS) {
            coinFile << "1000," << wlt[i].count << std::endl; 
        }
    }
    
    std::ofstream stockFile;
    stockFile.open(fileName[0]);
        ModifiedNode* ptr = sL->head;    
        while (ptr) {  
            stockFile << ptr->data->id << "|";
            stockFile << ptr->data->name << "|";
            stockFile << ptr->data->description << "|";
            stockFile << ptr->data->price.dollars << "." << ptr->data->price.cents << "|";
            stockFile << ptr->data->on_hand << std::endl;
            ptr = ptr->next;  
        }  

    coinFile.close();
    stockFile.close();
}

//prints the items 
void printItems(LinkedList* stockList) {
    std::cout << "Items Menu" << std::endl;
    std::cout << "----------" << std::endl;
    std::cout << "ID   |Name                                    | Available | Price" << std::endl;
    std::cout << "-------------------------------------------------------------------" << std::endl;
    stockList->displayItems();
    std::cout << std::endl;
}

//prints the items 
void modifiedPrintItems(DoublyLinkedList* stockList) {
    std::cout << "Items Menu" << std::endl;
    std::cout << "----------" << std::endl;
    std::cout << "ID   |Name                                    | Available | Price | Item Options " << std::endl;
    std::cout << "-------------------------------------------------------------------" << stockList->itemOptionsBorder() << std::endl;
    stockList->displayItems();
    std::cout << std::endl;
}
//allows user to add item in list 
bool addItem(LinkedList* stockList) {
    std::string name;
    std::string description;
    std::string priceString;
    std::vector<std::string> priceVec;

    //work out new id number
    std::string id = stockList->getLargestId();
    id = Helper::incrementId(id);

    std::cout << "The id of the new stock will be: " << id << std::endl;

    std::cout << "Enter the item name: ";
    name = Helper::readInput();
    while(name.length() == 0 || name.length() > NAMELEN){
        if(Helper::emptyString(name)){
            //if string is empty return to MM and write correct error message
            std::cout << "Cancelling \"add item\" at user's request." << std::endl;
            return false;
        }
        //otherwise if the name is too long ask again
        std::cout << "Error: line entered was too long. Please try again." << std::endl;
        std::cout << "Error inputting name of the product. Please try again." << std::endl; 
        std::cout << "Enter the item name: ";
        name = Helper::readInput();
    }
   

    std::cout << "Enter the item description: ";
    description = Helper::readInput();
    while(description.length() == 0 || description.length() > DESCLEN){
        if(Helper::emptyString(description)){
            //if string is empty return to MM and write correct error message
            std::cout << "Cancelling \"add item\" at the user's request." << std::endl;
            return false;
        }
        //otherwise if the description is too long ask again
        std::cout << "Error: line entered was too long. Please try again." << std::endl;
        std::cout << "Error inputting the description of the product. Please try again." << std::endl; 
        std::cout << "Enter the item description: ";
        description = Helper::readInput();
    }
    

    std::cout << "Enter the price for the item: ";
    priceString = Helper::readInput();

    while(!Helper::addItemPriceValidation(&priceString)){
        if(Helper::emptyString(priceString)){
            //if string is empty return to MM and write correct error message
            std::cout << "Cancelling \"add item\" at the user's request." << std::endl;
            return false;
        }
        //std::cout << "Error: the price is not valid." << std::endl;
        std::cout << "Enter the price for the item: ";
        priceString = Helper::readInput();
    }
   
    Helper::splitString(priceString, priceVec, PRICEDELIM);

    Price cost;
    cost.dollars = std::stoi(priceVec[0]);
    cost.cents = std::stoi(priceVec[1]);
  

    Node* newItem = new Node();
    newItem->createNode(id, name, description, cost, DEFAULT_STOCK_LEVEL);

    stockList->addNode(newItem);
    std::cout << "This item \"" << name << " - " << description;
    std::cout << "\" has now been added to the menu." << std::endl;
    return true;
}

//removes item in menu 
bool deleteItem(LinkedList* stockList) {
    std::string id;

    std::cout << "Enter the item id of the item to remove from the menu: ";
    id = Helper::readInput();
    while(id.length() > IDLEN){
        //if entered id is too long re prompt the user
        std::cout << "Error: line entered was too long. Please try again." << std::endl;
        std::cout << "Error: invalid item id entered. Please try again." << std::endl;
        std::cout << "Enter the item id of the item to remove from the menu: ";
        id = Helper::readInput();
    }
    
    if(Helper::emptyString(id)){
        //empty string 
        std::cout << "Operation cancelled at the user's request." << std::endl;
        return false;
    }
    if(stockList->deleteNode(id)){
        //success
        return true;
    }
    else{
        //node not found
        std::cout << "Error: desired id was not found." << std::endl;
        return false;
    }
}

//allows user to add item in list 
bool modifiedAddItem(DoublyLinkedList* stockList) {
    std::string name;
    std::string description;
    std::string priceString;
    std::vector<std::string> priceVec;

    //work out new id number
    std::string id = stockList->getLargestId();
    id = Helper::incrementId(id);

    std::cout << "The id of the new stock will be: " << id << std::endl;

    std::cout << "Enter the item name: ";
    name = Helper::readInput();
    while(name.length() == 0 || name.length() > NAMELEN || name == HELPOPTION){
        if(Helper::emptyString(name)){
            //if string is empty return to MM and write correct error message
            std::cout << "Cancelling \"add item\" at user's request." << std::endl;
            return false;
        }
        else if(name == HELPOPTION){
            std::cout << "HELP: ENTER A NAME FOR YOUR ITEM" << std::endl;
        }
        else{
            //otherwise if the name is too long ask again
            std::cout << "Error: line entered was too long. Please try again." << std::endl;
            std::cout << "Error inputting name of the product. Please try again." << std::endl; 
            
        }
        std::cout << "Enter the item name: ";
        name = Helper::readInput();
    }
   
    ItemOptionsll* newItemOptions = new ItemOptionsll;
    //handle adding item options here



    std::cout << "Enter the item description: ";
    description = Helper::readInput();
    while(description.length() == 0 || description.length() > DESCLEN || description == HELPOPTION){
        if(Helper::emptyString(description)){
            //if string is empty return to MM and write correct error message
            std::cout << "Cancelling \"add item\" at the user's request." << std::endl;
            return false;
        }
        else if(description == HELPOPTION){
            std::cout << "HELP: ENTER A DESCRIPTION FOR YOUR ITEM" << std::endl;
        }
        else{
            //otherwise if the description is too long ask again
            std::cout << "Error: line entered was too long. Please try again." << std::endl;
            std::cout << "Error inputting the description of the product. Please try again." << std::endl; 
            
        }
        std::cout << "Enter the item description: ";
        description = Helper::readInput();
    }
    

    std::cout << "Enter the price for the item: ";
    priceString = Helper::readInput();

    while(!Helper::addItemPriceValidation(&priceString)){
        if(Helper::emptyString(priceString)){
            //if string is empty return to MM and write correct error message
            std::cout << "Cancelling \"add item\" at the user's request." << std::endl;
            return false;
        }
        if(priceString == HELPOPTION){
            std::cout << "HELP: ENTER A PRICE FOR THE ITEM BETWEEN 0.00-99.99 DOLLARS" << std::endl;
        }
        std::cout << "Enter the price for the item: ";
        priceString = Helper::readInput();
    }
   
    Helper::splitString(priceString, priceVec, PRICEDELIM);

    Price cost;
    cost.dollars = std::stoi(priceVec[0]);
    cost.cents = std::stoi(priceVec[1]);
  

    ModifiedNode* newItem = new ModifiedNode();
    newItem->createNode(id, name, description, cost, DEFAULT_STOCK_LEVEL, newItemOptions);

    stockList->addNode(newItem);
    std::cout << "This item \"" << name << " - " << description;
    std::cout << "\" has now been added to the menu." << std::endl;
    return true;
}

//removes item in menu 
bool modifiedDeleteItem(DoublyLinkedList* stockList) {
    std::string id;

    std::cout << "Enter the item id of the item to remove from the menu: ";
    id = Helper::readInput();
    while(id.length() > IDLEN || id == HELPOPTION){
        if(id == HELPOPTION){
            //if the user requests help
            std::cout << "HELP: ENTER THE ID OF THE ITEM YOU WANT TO DELETE" << std::endl;
        }
        else{
            //if entered id is too long re prompt the user
            std::cout << "Error: line entered was too long. Please try again." << std::endl;
            std::cout << "Error: invalid item id entered. Please try again." << std::endl;
        }
      
        std::cout << "Enter the item id of the item to remove from the menu: ";

        id = Helper::readInput();
    }
    
    if(Helper::emptyString(id)){
        //empty string 
        std::cout << "Operation cancelled at the user's request." << std::endl;
        return false;
    }
    if(stockList->deleteNode(id)){
        //success
        return true;
    }
    else{
        //node not found
        std::cout << "Error: desired id was not found." << std::endl;
        return false;
    }
}


//displays coins 
void displayCoins(std::vector<Coin> wallet) {
    std::cout << "Coins Summary" << std::endl;
    std::cout << "-------------" << std::endl;
    std::cout << "Denomination" << "    |    " << "Count" << std::endl;
    std::cout << "---------------------------" << std::endl;
    for (int i = int(wallet.size()) - 1; i >= 0; i--) {
        if (wallet[i].denom == FIVE_CENTS) {
            std::cout << "5 Cents         |"; 
        } else if (wallet[i].denom == TEN_CENTS) {
            std::cout << "10 Cents        |"; 
        } else if (wallet[i].denom == TWENTY_CENTS) {
            std::cout << "20 Cents        |"; 
        } else if (wallet[i].denom == FIFTY_CENTS) {
            std::cout << "50 Cents        |"; 
        } else if (wallet[i].denom == ONE_DOLLAR) {
            std::cout << "1 Dollar        |"; 
        } else if (wallet[i].denom == TWO_DOLLARS) {
            std::cout << "2 Dollar        |"; 
        } else if (wallet[i].denom == FIVE_DOLLARS) {
            std::cout << "5 Dollar        |"; 
        } else if (wallet[i].denom == TEN_DOLLARS) {
            std::cout << "10 Dollar       |"; 
        }
        std::cout.width(COINSPACE);
        std::cout << wallet[i].count << std::endl;
    }

    std::cout << std::endl;
}

// sets the coins to a default value 
void setDefaultCoinCounts(std::vector<Coin>& wallet) {
    for (Coin &coin : wallet) {
        coin.count = DEFAULT_COIN_COUNT; 
    }
    std::cout << "All coins have been reset to the default level of " << DEFAULT_COIN_COUNT << std::endl;
}
