#include <stdio.h>
#include <stdlib.h>

#include "../ccheckmate.h"

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
