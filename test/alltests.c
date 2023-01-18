
#include "../ccheckmate.h"
#include "booltests.c"
#include "primitivetests.c"
#include "arraytests.c"

ccm_begin_test_suite
bool_tests();
primitive_tests();
array_tests();
ccm_end_test_suite
