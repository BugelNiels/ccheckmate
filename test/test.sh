gcc ../ccheckmate.c ccheckmate_unit_test.c -DTEST -Wl,--wrap,main
./a.out
