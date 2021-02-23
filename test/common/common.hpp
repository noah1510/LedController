#pragma once

#ifndef ARDUINO
#if __has_include("ArduinoFake.h")
#include "ArduinoFake.h"
#include <iostream>
#define PRINTLN(x) std::cout << x << std::endl
using namespace fakeit;
#define CATCH_FAKEIT catch(const FakeitException& e){std::cout << e.what() << std::endl; const char* msg = e.what().c_str(); TEST_FAIL_MESSAGE(msg);}
#endif
#endif

#include "LedController.hpp"
#include <unity.h>

#define CATCH_STD catch(const std::exception& e){const char* msg = e.what(); TEST_FAIL_MESSAGE(msg); }

#define TEST_ASSERT_EQAUL_BYTE_BLOCKS(a,b) for(unsigned int i = 0;i < 8;i++){TEST_ASSERT_EQUAL(a[i],b[i]);};

controller_configuration<4,1>& get_conf();
controller_configuration<4,1>& get_conf_SPI();
controller_configuration<4,4>& get_multi_conf();
controller_configuration<4,4>& get_multi_conf_SPI();

template<size_t columns>
const ByteRow<columns>& in_array() {
    static ByteRow<columns> in_array = ByteRow<columns>();
    for(unsigned int i = 0; i<columns; i++) {
        in_array[i]=static_cast<byte>(i);
    }
    return in_array;
}

const ByteBlock& testBlock();
