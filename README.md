<br />
<p align="center">
  <h1 align="center">CCheckmate</h1>

  <p align="center">
    A simple unit testing framework for C.
  </p>
</p>


## About the project

ImprocC is a simple unit testing framework for C. The framework was developed with the aim of making it as easy as possible to integrate it into existing frameworks. The main benefit of this framework is its simplificity. It is easy to use, easy to read and does not require any libraries!

All tests are run in separate process to ensure that a segmentation fault does not cause everything to stop.

## Setting up

1. Start by adding the `ccheckmate.c` and `ccheckmate.h` files to your project.
2. Write the tests according to the specifications below
3. Add the following flag to your compilation if you want to run the tests:
```sh
-Wl,--wrap,main
```

> Note that if the test suite is being run, the actual code is not!

## Usage

While using this framework, it is good practice to split unit tests concerned with different things into separate files. Tests that should be grouped together should reside in the same file.

A test file consists only of a `.c` file. At the top of this file, include `ccheckmate.h`. If you want to run the tests within a particular `.c` file, simply include said file in the compilation process.

The manner in which a test is declared is by writing: `ccm_test(<function_name>)`. Note that the function name cannot contain spaces in this case.

### Example Usage

For example, if we want to write a test that checks whether two variables are equal, we can write the following:

```C
ccm_test(testEqual) {
  int expected = 2;
  int actual = 2;
  assert_eq(expected, actual);
}
```

Alternatively, we can also provide a message to be printed if the test fails:

```C
ccm_test(testPlus) {
  assert_eq_msg(5, 2 + 3, "2+3 should equal 5");
}
```

we can also do this for arrays:

```C
ccm_test(testArrayEqual) {
  int array1[3] = {1, 2, 3};
  int array2[3] = {2, 3, 4};
  assert_arr_eq(array1, array2, 3, 3);
}
```

Note that at this point it is not possible to directly pass strings for comparison. For example, the following assert will not compile:

```C
    const char *test = "Hello world"
    assert_arr_eq(test, "Hello world", 11, 11);
```

### Running

The full file might look something as follows:

```C
#include "../ccheckmate.h"

ccm_test(testEqual) {
  int expected = 2;
  int actual = 2;
  assert_eq(expected, actual);
}

ccm_test(testPlus) {
  assert_eq_msg(5, 2 + 3, "2+3 should equal 5");
}

ccm_test(testArrayEqual) {
  int array1[3] = {1, 2, 3};
  int array2[3] = {2, 3, 4};
  assert_arr_eq(array1, array2, 3, 3);
}
```

This file is provided in the `examples` directory. We can compile the program using:

```sh
gcc ccheckmate.c examples/example.c -Wl,--wrap,main
```

Running `./a.out` will then produce the following output:
```sh

--------------------------------------------------
        Section: examples/example.c
--------------------------------------------------

 [Pass] testEqual (0.0s)
 [Pass] testPlus (0.0s)
 [Fail] testArrayEqual (0.0s)
        ==> examples/example.c:testArrayEqual():16
        ==> failure: array1 and array2, items at index 0 do not match.
                Expected: 1
                Actual: 2

--------------------------------------------------

Tests: 2 Passed, 1 Failed, 3 Total
There are test failures.
```

## Functions and macros

> Disclaimer: The framework works primarily with macros to facilitate flexible and easy-to-read usage. However, this can potentially result in large error messages if you get the syntax wrong. It is definitely possible to see what is going wrong, but this can be more difficult due to the macro expansions As such, always be sure to double check that you are using it in the correct way.

### Assertions

```C
assert_true(bool)
```
Asserts whether the integer evaluates to true (not 0).

```C
assert_false(bool)
```
Asserts whether the integer evaluates to false (0).

```C
assert_eq(expected, actual)
```
Asserts whether two primitives are equal.

```C
assert_eq_msg(expected, actual, message)
```
Asserts whether two primitives are equal and prints the provided message if not.


```C
assert_arr_eq(expected, actual, len_expected, len_actual)
```
Asserts whether the contents of the two arrays are equal.

```C
assert_arr_eq_msg(expected, actual, len_expected, len_actual, message)
```
Asserts whether the contents of the two arrays are equal and prints the provided message if not.

### Test execution

```C
ccm_test(test_func) {
    // Test code here
}
```
Declares a function as a test function. To group unit tests together, group them in the same source file.
