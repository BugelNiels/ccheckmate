#include <stdio.h>
#include <stdlib.h>

#include "../ccheckmate.h"

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
