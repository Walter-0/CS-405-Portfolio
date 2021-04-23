// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>

int main() {
    std::cout << "Buffer Overflow Example" << std::endl;

    // TODO: The user can type more than 20 characters and overflow the buffer, resulting in account_number being replaced -
    //  even though it is a constant and the compiler buffer overflow checks are on.
    //  You need to modify this method to prevent buffer overflow without changing the account_order
    //  varaible, and its position in the declaration. It must always be directly before the variable used for input.

    const std::string account_number = "CharlieBrown42";

    // I changed user_input from a char array with a hardcoded limit of 20 to a std::basic_string from the C++ standard library
    // which handles buffer overflows by automatically sizing the buffer to hold the data required.
    std::string user_input;
    std::cout << "Enter a value: ";
    std::cin >> user_input;

    // If the user does not enter an input less than or equal to 20 characters, this
    // while loop will continue to ask them until they do
    while (user_input.length() > 20) {
        std::cout << "Input too long. Please enter a value 20 characters or less: ";
        std::cin >> user_input;
    }

    std::cout << "You entered: " << user_input << std::endl;
    std::cout << "Account Number = " << account_number << std::endl;
}
