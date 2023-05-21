#include "helper.h"

using std::string;
using std::vector;

Helper::Helper(){}

void Helper::printInvalidInput()
{
    std::cout << "Invalid input.\n" << std::endl;
}

bool Helper::isNumber(const std::string& s) {
    //check if string is empty
    if(Helper::emptyString(s)){
        return false;
    }
    std::string::const_iterator qtyString = s.begin();
    while (qtyString != s.end() && std::isdigit(*qtyString)) {
        qtyString++;
    }
    return !s.empty() && qtyString == s.end();
}

bool Helper::isMenuNumber(const std::string& s) {
    //check if string is empty
    if(Helper::emptyString(s)){
        return false;
    }
    std::string::const_iterator qtyString = s.begin();
    //check for negative sign at the beginning of the string
    if (*qtyString == '-') {
        qtyString++;
    }
    while (qtyString != s.end() && std::isdigit(*qtyString)) {
        qtyString++;
    }
    return !s.empty() && qtyString == s.end();
}

void Helper::splitString(string s, vector<string>& tokens, string delimeter)
{
    tokens.clear();
    char* _s = new char[s.length()+1];
    strcpy(_s, s.c_str());

    char * pch;
    pch = strtok (_s, delimeter.c_str());
    while (pch != NULL)
    {
        tokens.push_back(pch);
        pch = strtok (NULL, delimeter.c_str());
    }
    delete[] _s;
}

string Helper::readInput()
{
    string input;
    std::getline(std::cin, input);

    return input;
}

string Helper::incrementId(std::string id){
    //gets int from id
    int num = std::stoi(id.substr(1)); 
    num++; 
    std::string numStr = std::to_string(num); 
    //calculate number of zeros and string together the code 
    int numZeros = id.size() - numStr.size() - 1; 
    id = id[0] + std::string(numZeros, '0') + numStr; 
    
    return id;
}

bool Helper::emptyString(const std::string string){
    return string == "";
}



bool Helper::priceValidator(std::string* price){
    bool fullstop = false;
    // Check if there is more than one fullstop
    int ttl = 0;
    for (int i = 0; i < int((*price).size()); i++) {
        if ((*price)[i] == '.') {
            fullstop = true;
            ttl += 1;
        }
    }
    if (ttl > 1) {
        fullstop = false;
    }
    return fullstop;
}

bool Helper::isValidDollar(const std::string &s, bool output){
    if(output == true){
        //checks if the string is a number 
        if (Helper::isNumber(s)){
            if(s.length() <= PRICESIZE){
                return true;
            }
            else{
                //string is too long return False 
                std::cout << "Error: line entered was too long. Please try again." << std::endl;
                std::cout << "Error inputting the price for the item. Please try again." << std::endl;
                return false;
            }
        }
        else{
            //string is not a number
            std::cout << "The price is not valid." << std::endl;
            return false;
        }
    }
    else{
        //dont show output
        if (Helper::isNumber(s)){
            if(s.length() <= PRICESIZE){
                return true;
            }
            else{
                //string is too long return False 
                return false;
            }
        }
        else{
            //string is not a number
            return false;
        }
    }
}

bool Helper::isValidCent(const std::string &s, bool output){
    if(output == true){
        //if output required
        if (Helper::isNumber(s)){
            if(s.length() <= PRICESIZE){
                if (std::stoi(s) % 5 == 0){
                    //cents passes all checks and is a cent
                    return true;
                }
                else{
                    //not divisible by 5
                    std::cout << "Error: the cents need to be a multiple of 5." << std::endl; 
                    return false;
                }
            }
            else{
                //string is too long return False 
                std::cout << "Error: line entered was too long. Please try again." << std::endl;
                std::cout << "Error inputting the price for the item. Please try again." << std::endl;
                return false;
            }
        }
        else{
            //string is not a number
            std::cout << "Error: the cents are not numeric." << std::endl;
            return false;
        }
    }
    else{
        //dont show output
        if (Helper::isNumber(s)){
            if(s.length() <= PRICESIZE){
                if (std::stoi(s) % 5 == 0){
                    //cents passes all checks and is a cent
                    return true;
                }
                else{
                    //not divisible by 5
                    return false;
                }
            }
            else{
                //string is too long return False 
                
                return false;
            }
        }
        else{
            //string is not a number
            std::cout << "Error: the cents are not numeric." << std::endl;
            return false;
        }
    }
}

bool Helper::addItemPriceValidation(std::string* price){
    //runs multiple functions to validate price
    if(!Helper::emptyString(*price)){
        std::vector<std::string> priceVec;
        if(Helper::priceValidator(price)){
            
            Helper::splitString(*price, priceVec, PRICEDELIM);
            
            if(priceVec.size() == PRICE_COLS){
                if(Helper::isValidDollar(priceVec[0], true)){
                    if(Helper::isValidCent(priceVec[1], true)){
                        //is valid price all test passed
                        return true;
                    }
                    else{
                        //not valid cents
                        return false; 
                    }
                }
                else{
                    //is not valid dollar 
                    return false;
                }
              
            }
            else{
                //vector wrong size
                std::cout << "Error: the price is not valid." << std::endl;
                return false;
            }
            
        }
        else {
            //failed price val check
            std::cout << "Error: the price is not valid." << std::endl;
            return false;
        }
    }
    else{
        //empty string, return to main menu
        return false;
    }
    

}

bool Helper::isbool(std::string s){
    if(s == "true" || s == "false"){
        return true;
    }
    return false;
}