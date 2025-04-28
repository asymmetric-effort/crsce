// file: test/CrossSumValue.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/CrossSumValue.h"
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <stdexcept>

/**
 * confirm that the default constructor initializes a zero-state.
 */
int test_default_constructor() {
    CrossSumValue value;
    // Confirm initial state is 0
    if (value.to_uint16() != 0) {
        std::cerr << "[FAIL] Initial value is not 0 (" << value.to_uint16() << ")" << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

// confirm we can set an initial value from 0 to 2^b-1
int test_initial_value(){
    constexpr uint16_t max_value=(1 << 9) - 1; // all bits set
    for(uint16_t initial_value=0; initial_value < max_value; initial_value++){
        CrossSumValue value(initial_value);
        if (value.to_uint16() != initial_value) {
            std::cerr << "[FAIL] Initial value (" << std::to_string(value.to_uint16()) << ") "
                      <<"is not (" << std::to_string(initial_value)<< ")"
                      << std::endl;
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

// Test increment and expect overflow
int test_increment(){
    // increment through the available numbers
    constexpr uint16_t max_value=(1 << 9) - 1; // all bits set
    // setup the test
    CrossSumValue value(0);
    for(uint16_t expected_value=0;i<max_value;expected_value++){
        if (uint16_t actual_value=value.to_uint16();actual_value != expected_value){
            std::cerr << "[FAIL] expected_value("
                      << std::to_string(expected_value)
                      << ") missed. got "
                      << std::to_string(actual_value)
                      << std::endl;
            return EXIT_FAILURE;
        }
        value++;
    }
    // increment beyond the limit and expect an overflow error
    try{
        value++;
        std::cerr << "[FAIL] overflow_error expected.  not encountered" << std::endl;
        return EXIT_FAILURE;
    }catch(std::overflow_error const &e){
      return EXIT_SUCCESS;
    }
}

//Test the addition (+) operator
int test_add_operator(){
    constexpr uint16_t max_value=(1 << 9) - 1;
    try{
        CrossSumValue value1(1);
        CrossSumValue value2(max_value);
        CrossSumValue value3(value1+value2);
        std::cerr << "[FAIL] overflow_error expected.  not encountered" << std::endl;
        return EXIT_FAILURE;
    }catch(std::overflow_error const &e){
        return EXIT_SUCCESS;
    }
    CrossSumValue v(0);
    if(uint16_t actual = v+16; actual != 16){
        std::cerr << "[FAIL] add produced a bad outcome" << std::endl;
        return EXIT_FAILURE;
    }
}

int main() {
    try {
      if(int exit=test_default_constructor();exit!=EXIT_SUCCESS) return exit;
      if(int exit=test_initial_value();exit!=EXIT_SUCCESS) return exit;
      if(int exit=test_increment();exit!=EXIT_SUCCESS) return exit;
      if(int exit=test_add_operator();exit!=EXIT_SUCCESS) return exit;

        {
            CrossSumValue value;
            // Confirm initial state is 0
            if (value.to_uint16() != 0) {
                std::cerr << "[FAIL] Initial value is not 0 (" << value.to_uint16() << ")" << std::endl;
                return EXIT_FAILURE;
            }

            // Increment the value
            ++value;

            // Confirm incremented state is 1
            if (value.to_uint16() != 1) {
                std::cerr << "[FAIL] Value after increment is not 1 (" << value.to_uint16() << ")" << std::endl;
                return EXIT_FAILURE;
            }

            // Add a value to the current state
            value = value + 5;

            // Confirm the result is 6
            if (value.to_uint16() != 6) {
                std::cerr << "[FAIL] Value after adding 5 is not 6 (" << value.to_uint16() << ")" << std::endl;
                return EXIT_FAILURE;
            }

            // Add another CrossSumValue instance
            CrossSumValue another(10);
            value = value + another;

            // Confirm the result is 16
            if (value.to_uint16() != 16) {
                std::cerr << "[FAIL] Value after adding another(10) is not 16 (" << value.to_uint16() << ")" << std::endl;
                return EXIT_FAILURE;
            }
        }
        std::cout << "[PASS] All CrossSumValue tests passed." << std::endl;
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
