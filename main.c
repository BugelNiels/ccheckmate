
#define TEST

#ifdef TEST
#include <stdio.h>
#include <stdlib.h>
#include "ccheckmate.h"

void testVariableEqualLiteral() {
    int a = 0;
    assertEquals(a, 1);
}

void testVariableEqual() {
    int a = 0;
    int b = 0;
    assertEquals(a, b);
}

void testVariableNotEqual() {
    int a = 0;
    int b = 1;
    assertEquals(a, b);
}

void testVariableNotEqualTypes() {
    int a = 0;
    double b = 0;
    assertEquals(a, b);
}

void testVariableEqualMsg() {
    int a = 0;
    int b = 1;
    assertEqualsMsg(a, b, "Variables are not equal");
}

void testArrayEqual() {
    int array1[3] = {1, 2, 3};

    assertArrayEquals(array1, array1, 3, 3);
}

void testArrayNotEqual() {
    int array1[3] = {1, 2, 3};
    int array2[3] = {2, 3, 4};

    assertArrayEquals(array1, array2, 3, 3);
}

void testArrayNotEqualLength() {
    int array1[3] = {1, 2, 3};
    int array2[2] = {2, 3};

    assertArrayEquals(array1, array2, 3, 2);
}

void testArrayNotEqualTypes() {
    int array1[3] = {1, 2, 3};
    double array2[3] = {1.0, 2.0, 3.0};

    assertArrayEquals(array1, array2, 3, 3);
}

void testArrayEqualMsg() {
    int array1[3] = {1, 2, 3};
    int array2[3] = {1, 2, 3};

    assertArrayEqualsMsg(array1, array2, 3, 3, "Arrays are not equal");
}

void testAssertEquals() {
    startSection("Testing assertEquals");
    cTest(testVariableEqualLiteral);
    cTest(testVariableEqual);
    cTest(testVariableNotEqual);
    cTest(testVariableNotEqualTypes);
    cTest(testVariableEqualMsg);
}

void testAssertArrayEquals() {
    startSection("Testing assertArrayEquals");
    cTest(testArrayEqual);
    cTest(testArrayNotEqual);
    cTest(testArrayNotEqualLength);
    cTest(testArrayNotEqualTypes);
    cTest(testArrayEqualMsg);
}

int main(int argc, char *argv[]) {
    startTestSuite();
    testAssertEquals();
    testAssertArrayEquals();
    endTestSuite();
    return 0;
}

#endif
