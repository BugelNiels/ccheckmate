#include <stdio.h>
#include <stdlib.h>

#include "../ccheckmate.h"

void testAssertTrue() {
    int x = 7;
    assert_true(x);
    assert_true(1);
    assert_true(3 > 5);
}

void testAssertFalse() {
    int x = 0;
    assert_false(x);
    assert_false(0);
    assert_false(3 < 5);
}


void testVariableEqualLiteral() {
    int a = 0;
    assert_eq(a, 1);
}

void testVariableEqual() {
    int a = 0;
    int b = 0;
    assert_eq(a, b);
}

void testDifferentVariablesEqual() {
    int a = 4;
    int b = 4;
    assert_eq(4, 3);
    assert_eq(a, 4);
    assert_eq(a, b);
    assert_eq((char)a, (char)b);
    assert_eq((unsigned char)a, (unsigned char)b);
    assert_eq((short)a, (short)b);
    assert_eq((unsigned short)a, (unsigned short)b);
    assert_eq((int)a, (int)b);
    assert_eq((unsigned int)a, (unsigned int)b);
    assert_eq((long)a, (long)b);
    assert_eq((unsigned long)a, (unsigned long)b);
    assert_eq((long long)a, (long long)b);
    assert_eq((unsigned long long)a, (unsigned long long)b);
    assert_eq((float)a, (float)b);
    assert_eq((double)a, (double)b);
    assert_eq((long double)a, (long double)b);
}

void testVariableNotEqual() {
    int a = 0;
    int b = 1;
    assert_eq(a, b);
}

void testVariableNotEqualTypes() {
    int a = 0;
    double b = 0;
    assert_eq(a, b);
}

void testVariableEqualMsg() {
    int a = 0;
    int b = 1;
    assert_eq_msg(a, b, "Variables are not equal");
}

void testArrayEqual() {
    int array1[3] = {1, 2, 3};
    assert_arr_eq(array1, array1, 3, 3);
}

void testArrayNotEqual() {
    int array1[3] = {1, 2, 3};
    int array2[3] = {2, 3, 4};
    assert_arr_eq(array1, array2, 3, 3);
}

void testArrayNotEqualLength() {
    int array1[3] = {1, 2, 3};
    int array2[2] = {2, 3};
    assert_arr_eq(array1, array2, 3, 2);
}

void testArrayNotEqualTypes() {
    int array1[3] = {1, 2, 3};
    double array2[3] = {1.0, 2.0, 3.0};
    assert_arr_eq(array1, array2, 3, 3);
}

void testArrayEqualMsg() {
    int array1[3] = {1, 2, 3};
    int array2[3] = {1, 2, 3};
    assert_arr_eq_msg(array1, array2, 3, 3, "Arrays are not equal");
}

BEGIN_CCHECK_MATE
start_section("Testing assertTrue");
ccm_test(testAssertTrue);
ccm_test(testAssertFalse);

start_section("Testing assertEquals");
ccm_test(testVariableEqualLiteral);
ccm_test(testVariableEqual);
ccm_test(testVariableNotEqual);
ccm_test(testVariableNotEqualTypes);
ccm_test(testVariableEqualMsg);
ccm_test(testDifferentVariablesEqual);

start_section("Testing assertArrayEquals");
ccm_test(testArrayEqual);
ccm_test(testArrayNotEqual);
ccm_test(testArrayNotEqualLength);
ccm_test(testArrayNotEqualTypes);
ccm_test(testArrayEqualMsg);
END_CCHECK_MATE
