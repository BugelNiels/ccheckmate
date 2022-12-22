<br />
<p align="center">
  <h1 align="center">CCheckmate</h1>

  <p align="center">
    A simple unit testing framework for C.
  </p>
</p>


## About the project

ImprocC is a simple unit testing framework for C. The framework was developed with the aim of making it as easy as possible to integrate it into existing frameworks. The main benefit of this framework is its simplificity. It is easy to use, easy to read and does not require any libraries!

## Setting up

1. Start by adding the `ccheckmate.c` and `ccheckmate.h` files to your project.
2. Write the tests according to the specifications below
3. Add the following flag to your compilation if you want to run the tests:
```sh
-Wl,--wrap,main
```

Note that if the test suite is being run, the actual code is not!

## Example Usage

Let's starting by writing a few simple test functions. Any test functions you write must be of type `void` and must take no parameters.

### Writing test functions

We start by writing a simple test that checks whether two variables are equal:
```C
void testEqual() {
    int expected = 2;
    int actual = 2;
    assert_eq(expected, actual);
}
```
Alternatively, we can also provide a message to be printed if the test fails:
```C
void testPlus() {
    assert_eq_msg(5, 2 + 3, "2+3 should equal 5");
}
```

we can also do this for arrays:
```C
void testArrayEqual() {
    int array1[3] = {1, 2, 3};
    int array2[3] = {2, 3, 4};
    assert_arr_eq(array1, array1, 3, 3);
}
```

Note that at this point it is not possible to directly pass strings for comparison. For example, the following assert will not compile:
```C
    const char *test = "Hello world"
    assert_arr_eq(test, "Hello world", 11, 11);
```

### Setting up test suite

Unfortunately, these functions won't magically execute by themselves. To do this, we have to write the following block of code:

```C
BEGIN_CCHECK_MATE
    start_section("Testing single variables");
    ccm_test(testEqual);
    ccm_test(testPlus);

    start_section("Testing arrays");
    ccm_test(testArrayEqual);
END_CCHECK_MATE
```

The `BEGIN_CCHECK_MATE` and `END_CCHECK_MATE` are there to ensure that whatever is in between will be executed as part of the test suite. This block of code has to be added **outside** of any functions.

The `start_section` function is primarily used to nicely organize your output. We can execute individual test functions by passing along their name to the `ccm_test` macro.

### Running

The full file might look something as follows:
```C
#include "ccheckmate.h"

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
```

This file is provided in the `examples` directory. We can compile the program using:

```sh
gcc ccheckmate.c example/ctest.c -DTEST -Wl,--wrap,main
```

Running `./a.out` will then produce the following output:
```sh
Initializing test suite...

--------------------------------------------------
        Section: Testing single variables
--------------------------------------------------

 [Pass] testEqual (0.0s)
 [Pass] testPlus (0.0s)

--------------------------------------------------
        Section: Testing arrays
--------------------------------------------------

 [Fail] testArrayEqual (0.0s)
        ==> ctest.c:testArrayEqual():16
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
assert_eq(expected, actual)
```
> Asserts whether two primitives are equal.

```C
assert_eq_msg(expected, actual, message)
```
> Asserts whether two primitives are equal and prints the provided message if not.


```C
assert_arr_eq(expected, actual, len_expected, len_actual)
```
> Asserts whether the contents of the two arrays are equal.

```C
assert_arr_eq_msg(expected, actual, len_expected, len_actual, message)
```
> Asserts whether the contents of the two arrays are equal and prints the provided message if not.

### Test execution

```C
BEGIN_CCHECK_MATE
```
> Starts the test suit. Should always be accompanied with a corresponding `END_CCHECK_MATE`. This must be added outside of any functions and can only be added once to any project.

```C
END_CCHECK_MATE
```
> Ends the test suit. Should always be accompanied with a corresponding `BEGIN_CCHECK_MATE`. This must be added outside of any functions and can only be added once to any project.

```C
start_section(const char* name);
```
Starts a testing section. Useful to organize the console output.

```C
ccm_test(test_func)
```
Runs a particular testing function. The provided function should take no parameters and be of type void.
