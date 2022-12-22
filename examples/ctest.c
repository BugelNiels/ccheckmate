#include "../ccheckmate.h"

void testEqual() {
    int expected = 2;
    int actual = 2;
    assert_eq(expected, actual);
}

void testPlus() {
    assert_eq_msg(5, 2 + 3, "2+3 should equal 5");
}

void testArrayEqual() {
    int array1[3] = {1, 2, 3};
    int array2[3] = {2, 3, 4};
    assert_arr_eq(array1, array2, 3, 3);
}

BEGIN_CCHECK_MATE
    start_section("Testing single variables");
    ccm_test(testEqual);
    ccm_test(testPlus);

    start_section("Testing arrays");
    ccm_test(testArrayEqual);
END_CCHECK_MATE
