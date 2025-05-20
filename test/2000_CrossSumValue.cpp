// file: test/2000_CrossSumValue.cpp
// (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>

#include "utils/test/Tester.h"
#include "CRSCE/constants/constants.h"
#include "CRSCE/CrossSum/CrossSumValue/CrossSumValue.h"
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <stdexcept>

/**
 * confirm that the default constructor initializes a zero-state.
 */
void test_default_constructor(Tester &tester) {
    tester.debug("test_default_constructor() start");
    CrossSumValue value;
    tester.NotEqual(
        value.to_uint16(),
        0,
        std.format(
            "Initial value is not 0 ({})",
            value.to_uint16()
        )
    );
}

// confirm we can set an initial value from 0 to 2^b-1
void test_initial_value(Tester &tester){
    tester.debug("test_initial_value()");
    for(uint16_t initial_value=0; initial_value < s; initial_value++){
        CrossSumValue value(initial_value);
        tester.assertNotEqual(
            value.to_uint16(),
            initial_value,
            std::format(
                "Initial value ({}) is not ({})",
                std::to_string( value.to_uint16() ),
                std::to_string( initial_value )
            )
        );
    }
}

// Test increment and expect overflow
void test_increment(Tester &tester){
    tester.debug("test_increment() [step 1]");
    CrossSumValue value(0);
    for(uint16_t expected_value=0;expected_value<s;expected_value++){
        const uint16_t actual_value=value.to_uint16();
        tester.assertNotEqual(
            actual_value,
            expected_value,
            std::format(
                "expected_value({}) missed. got {}",
                std::to_string(expected_value),
                std::to_string(actual_value)
            )
        );
        value++;
    }
    try{
        value++;
        tester.debug(
            std::format(
                "overflow_error expected(1) not encountered. got:{} want:{}",
                std::to_string(value.to_uint16())
                std::to_string(s)
            )
        );
        tester.fail(); // we expected an error.
    }catch(std::overflow_error const &e){
        tester.pass();
    }
}

void test_add_operator_and_overflow(Tester &tester){
    tester.debug("test_add_operator_and_overflow() [step 1]");
    try {
        CrossSumValue lhs(1);
        CrossSumValue rhs(s);
        CrossSumValue answer(value1 + value2);
        tester.debug(
            std::format(
                "overflow_error expected(2).  not encountered. got:{} want:{}",
                std::to_string(answer.to_uint16()),
                std::to_string(s)
            )
        );
    } catch (const std::overflow_error& e) {
        // expected overflow
    }
}

void test_add_operator_ok(Tester &tester){
    tester.debug("test_add_operator_ok() [step 1]");
    {
        CrossSumValue value1(0);
        uint16_t value2 = 16;
        CrossSumValue actual = value1 + value2;
        tester.assertNotEqual(
            actual.to_uint16(),
            value2,
            std::format(
                "add produced a bad outcome ({})",
                actual.to_uint16()
            )
        );
    }
}

void test_to_uint16(Tester &tester) {
    tester.debug("test_to_uint16()");
    try {
        // Valid values only
        CrossSumValue val1(511);  // max
        tester.assertNotEqual(
            val1.to_uint16(),
            511,
            std::format(
                "CrossSumValue(511).to_uint16() != 511, got {}",
                val1.to_uint16()
            )
        );

        CrossSumValue val2(341);
        tester.assertNotEqual(
            val2.to_uint16(),
            341,
            std::format("CrossSumValue(341).to_uint16() != 341, got {}",val2.to_uint16())
        );

        CrossSumValue val3(0);
        tester.assertNotEqual(
            val3.to_uint16(),
            0,
            std::format(
                "CrossSumValue(0).to_uint16() != 0, got {}",
                val3.to_uint16()
            );
}

int main() {

    Tester tester("test/2000_CrossSumValue", TerminateOnError);
    tester.deadline(60);
    tester.skip("disabled for debug");

    test_default_constructor(tester);
    test_initial_value(tester);
    test_increment(tester);
    test_add_operator_and_overflow(tester);
    test_add_operator_ok(tester);
    test_to_uint16(tester);

    tester.debug("All CrossSumValue tests passed.");

    return EXIT_SUCCESS;
}
