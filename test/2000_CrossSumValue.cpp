// file: test/2000_CrossSumValue.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "CRSCE/constants/constants.h"
#include "CRSCE/CrossSum/CrossSumValue/CrossSumValue.h"
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <stdexcept>

/**
 * confirm that the default constructor initializes a zero-state.
 */
int test_default_constructor() {
    std::cout << "test_default_constructor()" << std::endl;
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
    std::cout << "test_initial_value()" << std::endl;
    for(uint16_t initial_value=0; initial_value < s; initial_value++){
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
     std::cout << "test_increment() [step 1]" << std::endl;
    // setup the test
    CrossSumValue value(0);
    for(uint16_t expected_value=0;expected_value<s;expected_value++){
        if (uint16_t actual_value=value.to_uint16();actual_value != expected_value){
            std::cerr << "[FAIL] expected_value(" << std::to_string(expected_value) << ") missed. got "
                      << std::to_string(actual_value) << std::endl;
            return EXIT_FAILURE;
        }
        value++;
    }
    // increment beyond the limit and expect an overflow error
    try{
        value++;
        std::cerr << "[FAIL] overflow_error expected(1).  not encountered.\n\t"
                     "got:  " << std::to_string(value.to_uint16()) << "\n"
                     "want: " << std::to_string(s) << std::endl;
        return EXIT_FAILURE;
    }catch(std::overflow_error const &e){
      return EXIT_SUCCESS;
    }
}

int test_add_operator(){
    std::cout << "test_add_operator() [step 1]" << std::endl;
    {
        CrossSumValue value1(1);
        CrossSumValue value2(s);
        try {
            CrossSumValue value3(value1 + value2);
            std::cerr << "[FAIL] overflow_error expected(2).  not encountered.\n\t"
                         "got:  " << std::to_string(value3.to_uint16()) << "\n"
                         "want: " << std::to_string(s) << std::endl;
            return EXIT_FAILURE;
        } catch (const std::overflow_error& e) {
            // expected overflow
        }
    }
    {
        CrossSumValue value1(0);
        uint16_t value2 = 16;
        CrossSumValue actual = value1 + value2;
        if (actual.to_uint16() != value2) {
            std::cerr << "[FAIL] add produced a bad outcome (" << actual.to_uint16() << ")" << std::endl;
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int test_to_uint16() {
    try {
        // Valid values only
        CrossSumValue val1(511);  // max
        if (val1.to_uint16() != 511) {
            std::cerr << "[FAIL] CrossSumValue(511).to_uint16() != 511, got "
                      << val1.to_uint16() << std::endl;
            return EXIT_FAILURE;
        }

        CrossSumValue val2(341);
        if (val2.to_uint16() != 341) {
            std::cerr << "[FAIL] CrossSumValue(341).to_uint16() != 341, got "
                      << val2.to_uint16() << std::endl;
            return EXIT_FAILURE;
        }

        CrossSumValue val3(0);
        if (val3.to_uint16() != 0) {
            std::cerr << "[FAIL] CrossSumValue(0).to_uint16() != 0, got "
                      << val3.to_uint16() << std::endl;
            return EXIT_FAILURE;
        }

        std::cout << "[PASS] CrossSumValue::to_uint16() passed all tests.\n";
        return EXIT_SUCCESS;

    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Exception in test_to_uint16: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

int main() {
    try {
        if(int exit=test_default_constructor();exit!=EXIT_SUCCESS) return exit;
        if(int exit=test_initial_value();exit!=EXIT_SUCCESS) return exit;
        if(int exit=test_increment();exit!=EXIT_SUCCESS) return exit;
        if(int exit=test_add_operator();exit!=EXIT_SUCCESS) return exit;
        if(int exit=test_to_uint16();exit!=EXIT_SUCCESS) return exit;
        std::cout << "[PASS] All CrossSumValue tests passed." << std::endl;
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
