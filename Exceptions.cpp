// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdexcept>

struct CustomException : public std::exception {
    const char* what() const throw () {
        return "My custom exception";
    }
};

bool do_even_more_custom_application_logic() {
    throw std::runtime_error("Error: Function should only be called on a Wednesday");

    std::cout << "Running Even More Custom Application Logic." << std::endl;

    return true;
}

void do_custom_application_logic() {
    std::cout << "Running Custom Application Logic." << std::endl;

    try {
        if (do_even_more_custom_application_logic()) {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }
    catch (std::exception err) {
        std::cout << "Exception occurred" << std::endl << err.what();
    }
 
    throw CustomException();

    std::cout << "Leaving Custom Application Logic." << std::endl;
}

float divide(float num, float den) {
    if (den == 0) {
        throw std::runtime_error("Error: Cannot divide by zero\n");
    }
    return (num / den);
}

void do_division() noexcept {
    float numerator = 10.0f;
    float denominator = 0;

    try {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    catch (std::runtime_error err) {
        std::cout << "Exception occurred" << std::endl << err.what();
    }
}

int main() {
    std::cout << "Exceptions Tests!" << std::endl;

    try {
        do_division();
        do_custom_application_logic();
    }

    catch (CustomException err) {
        std::cout << "Exception occurred" << std::endl << err.what();
    }
    
    catch (std::exception err) {
        std::cout << "Exception occurred" << std::endl << err.what();
    }

    catch (...) {
        std::cout << "Exception of unknown type occurred" << std::endl;
    }
}
