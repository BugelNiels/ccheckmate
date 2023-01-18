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

## Setting up a test section

The unit tests are separated into sections. Before you can declare any test functions, be sure to first declare a section within which the functions are declared. This is done as follows:

```C
ccm_start_section;

// Add test functions here

// replace section_name with the name of your section WITHOUT quotes and WITHOUT spaces
ccm_end_section(my_section_name);
```

Important: this can only be added once to every file, so if you want to have multiple sections, each of these sections should reside in separate files:

### Writing test functions

We start by writing a simple test that checks whether two variables are equal:

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

### Setting up test suite

These functions won't magically execute by themselves (actually for the most part they do, but there is still a little bit of manual labour involved). After declaring our sections, we have to declare the test suite and call the sections we want to execute.

 To do this, we first set up the test suite and simply call the test section using its name, similar to how you call a function.

```C
ccm_begin_test_suite
    my_section_name();
ccm_end_test_suite
```

The `ccm_begin_test_suite` and `ccm_end_test_suite` are there to ensure that whatever is in between will be executed as part of the test suite. This block of code has to be added **outside** of any functions.

### Running

The full file might look something as follows:
```C
#include "ccheckmate.h"

ccm_begin_section; // Must be added before any ccm_test declarations

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

// Name cannot contain spaces
ccm_end_section(example);   // Note the lack of quotes

ccm_begin_test_suite;
example();                  // This should be the same name as the section
ccm_end_test_suite;
```

This file is provided in the `examples` directory. We can compile the program using:

```sh
gcc ccheckmate.c example/ctest.c -Wl,--wrap,main
```

Running `./a.out` will then produce the following output:
```sh
Initializing test suite...

--------------------------------------------------
        Section: example
--------------------------------------------------

 [Pass] testEqual (0.0s)
 [Pass] testPlus (0.0s)
 [Fail] testArrayEqual (0.0s)
        ==> example.c:testArrayEqual():16
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
assert_true(int)
```
Asserts whether the integer evaluates to true (not 0).

```C
assert_false(int)
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
ccm_begin_test_suite;
```
Starts the test suit. Should always be accompanied with a corresponding `ccm_end_test_suite` within the same file. This must be added outside of any functions and can only be added once to any project. From here, you can call the test suites.

```C
ccm_end_test_suite;
```
Ends the test suit. Should always be accompanied with a corresponding `ccm_end_test_suite` within the same file. This must be added outside of any functions and can only be added once to any project.

```C
ccm_start_section;
```
Starts a testing section. Can only be added once to any file. Starts a new section of the test suite. Must always be accompanied with a corresponding `ccm_end_section`.

```C
ccm_end_section(section_name);
```
Ends a testing section and gives the section the name `section_name`. The tests within this section can now be called from within the test suite using `<section_name>();`. For example if you named a section `myTest`: `ccm_end_section(myTest)` (note the lack of quotes), then you can call said test suite using `myTest()`. Can only be added once to any file. Starts a new section of the test suite. Must always be accompanied with a corresponding `ccm_end_section`. The section name cannot contain spaces.

```C
ccm_test(test_func)
```
Declares a function as a test function. Should be used from within a test suite, otherwise it will not compile.
