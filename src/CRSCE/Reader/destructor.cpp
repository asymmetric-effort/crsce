/**
 * @file include/CRSCE/Reader/destructor.cpp
 * @copyright (c) 2025 Asymmetric Effort, LLC. <scaldwell@asymmetric-effort.com>
 */

#include "CRSCE/Reader.h"

Reader::~Reader(){

    if (inputStream.is_open()) {
        inputStream.close();
    }

    if (outputStream.is_open()) {
        outputStream.close();
    }

}
