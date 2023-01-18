#include <stdio.h>
#include <stdlib.h>

#include "../ccheckmate.h"

ccm_start_section

ccm_test(testAssertTrue) {
  int x = 7;
  assert_true(x);
  assert_true(1);
  assert_true(3 > 5);
}

ccm_test(testAssertFalse) {
  int x = 0;
  assert_false(x);
  assert_false(0);
  assert_false(3 < 5);
}

ccm_test(testVariableEqualLiteral) {
  int a = 0;
  assert_eq(a, 1);
}

ccm_test(testVariableEqual) {
  int a = 0;
  int b = 0;
  assert_eq(a, b);
}

ccm_test(testDifferentVariablesEqual) {
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

ccm_test(testVariableNotEqual) {
  int a = 0;
  int b = 1;
  assert_eq(a, b);
}

ccm_test(testVariableNotEqualTypes) {
  int a = 0;
  double b = 0;
  assert_eq(a, b);
}

ccm_test(testVariableEqualMsg) {
  int a = 0;
  int b = 1;
  assert_eq_msg(a, b, "Variables are not equal");
}

ccm_test(testArrayEqual) {
  int array1[3] = {1, 2, 3};
  assert_arr_eq(array1, array1, 3, 3);
}

ccm_test(testArrayNotEqual) {
  int array1[3] = {1, 2, 3};
  int array2[3] = {2, 3, 4};
  assert_arr_eq(array1, array2, 3, 3);
}

ccm_test(testArrayNotEqualLength) {
  int array1[3] = {1, 2, 3};
  int array2[2] = {2, 3};
  assert_arr_eq(array1, array2, 3, 2);
}

ccm_test(testArrayNotEqualTypes) {
  int array1[3] = {1, 2, 3};
  double array2[3] = {1.0, 2.0, 3.0};
  assert_arr_eq(array1, array2, 3, 3);
}

ccm_test(testArrayEqualMsg) {
  int array1[3] = {1, 2, 3};
  int array2[3] = {1, 2, 3};
  assert_arr_eq_msg(array1, array2, 3, 3, "Arrays are not equal");
}

ccm_end_section(unit_test_section)
