#include "../ccheckmate.h"

ccm_begin_section;

ccm_test(testEqual) {
  int expected = 2;
  int actual = 2;
  assert_eq(expected, actual);
}

ccm_test(testPlus) { assert_eq_msg(5, 2 + 3, "2+3 should equal 5"); }

ccm_test(testArrayEqual) {
  int array1[3] = {1, 2, 3};
  int array2[3] = {2, 3, 4};
  assert_arr_eq(array1, array2, 3, 3);
}

ccm_end_section(example);

ccm_begin_test_suite;
example();
ccm_end_test_suite;
