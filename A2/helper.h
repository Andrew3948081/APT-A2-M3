#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <cassert>
#include <sstream>
#include <vector>
#include <iostream>
#include <string.h>
#include <random>
#include "LinkedList.h"

class Helper
{
private:
    Helper();

public:



    /**
     * @brief Split the given string given a delimeter. For instance, given the string "1,2,3" and the delimeter ",", 
     *        This string will be splited into "1","2","3", and they will be put into the vector.  
     * 
     * @param s The given string
     * @param tokens The vector containing the results
     * @param delimeter the string based on which splitting is performed
     */
    static void splitString(std::string s, std::vector<std::string>& tokens, std::string delimeter);

    /**
     * @brief Read the user input (a line) from keyboard
     * 
     * @return the user input.
     */
    static std::string readInput();

    //returns the next availiable id
    static std::string incrementId(std::string id);

    //return true if string is empty
    static bool emptyString(const std::string string);

    /**
     * @brief Print a statement if an incorrect command was entered
    */
    static void printInvalidInput();

    //returns true if string is number
    static bool isNumber(const std::string &s);

    //checks if string is valid cent
    //cent is valid if its is a number and a multiple of 5
    static bool isValidCent(const std::string &s, bool output = false);

    //validate price for adding items
    static bool addItemPriceValidation(std::string* price);

    //checks if string is a price,, output tells the function if it should print
    static bool priceValidator(std::string* price);

    //checks if dollar is valid, output tells the function if it should print
    static bool isValidDollar(const std::string &s, bool output = false);

    //returns true if string is number (modified to work with negative ints)
    static bool isMenuNumber(const std::string &s);
};
#endif