#include "ccheckmate.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define ERROR_BUF_SIZE 20248

#define CODE_BOLD "\x1B[1;37m"
#define CODE_RESET "\x1B[0m"
#define CODE_RED "\x1B[1;31m"
#define CODE_GREEN "\x1B[1;32m"
#define CODE_ORANGE "\x1B[1;33m"

#define BOOL_ERR_MSG(FORMAT) "%s is not true.\n\t\tExpected: " FORMAT "\n\t\tActual: " FORMAT "\n"
#define PRIMITIVE_ERR_MSG(FORMAT) "%s and %s are not equal.\n\t\tExpected: " FORMAT "\n\t\tActual: " FORMAT "\n"
#define ARRAY_ERR_MSG(FORMAT) \
  "%s and %s, items at index %d do not match.\n\t\tExpected: " FORMAT "\n\t\tActual: " FORMAT "\n"

typedef char byte;

// TODO: see if we can remove the global variables :o

// TODO: default to error message for unrecongized types
// TODO: do for all those lib functions?
static int test_status = -1;
static int passed = 0;
static int failed = 0;
static char err_msg[ERROR_BUF_SIZE];

static void assert_err(const char *usrMsg, const char *file, const char *function, int line, const char *format, ...) {
  char *tmp = err_msg;
  tmp += sprintf(tmp, "\t==> %s:%s():%d\n\t==> %sfailure: %s", file, function, line, CODE_RED, CODE_RESET);
  va_list args;
  va_start(args, format);
  tmp += vsprintf(tmp, format, args);
  va_end(args);
  if (strlen(usrMsg) > 0) {
    tmp += sprintf(tmp, "\t==> Message: %s\n", usrMsg);
  }
  test_status = 0;
}

static void warning(const char *format, ...) {
  fprintf(stderr, "%s Warning:%s ", CODE_ORANGE, CODE_RESET);
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
}

// TODO: length dependent on terminal size?
static void print_divider() { fprintf(stderr, "--------------------------------------------------\n"); }

// Primitives

void __assert_true(int bool_i, const char *bool_name, const char *msg, const char *file, const char *function,
                   int line) {
  if (!bool_i) {
    assert_err(msg, file, function, line, "Boolean condition %s is not True.\n\t\tExpected: True\n\t\tActual: False\n",
               bool_name);
  }
}

void __assert_false(int bool_i, const char *bool_name, const char *msg, const char *file, const char *function,
                    int line) {
  if (bool_i) {
    assert_err(msg, file, function, line, "Boolean condition %s is not False.\n\t\tExpected: False\n\t\tActual: True\n",
               bool_name);
  }
}

void __assert_eq_char(char exp, char act, const char *exp_name, const char *act_name, const char *msg, const char *file,
                      const char *function, int line) {
  if (exp != act) {
    assert_err(msg, file, function, line, PRIMITIVE_ERR_MSG("%c"), exp_name, act_name, exp, act);
  }
}
void __assert_eq_uchar(unsigned char exp, unsigned char act, const char *exp_name, const char *act_name,
                       const char *msg, const char *file, const char *function, int line) {
  if (exp != act) {
    assert_err(msg, file, function, line, PRIMITIVE_ERR_MSG("%d"), exp_name, act_name, exp, act);
  }
}

void __assert_eq_short(short exp, short act, const char *exp_name, const char *act_name, const char *msg,
                       const char *file, const char *function, int line) {
  if (exp != act) {
    assert_err(msg, file, function, line, PRIMITIVE_ERR_MSG("%hd"), exp_name, act_name, exp, act);
  }
}
void __assert_eq_ushort(unsigned short exp, unsigned short act, const char *exp_name, const char *act_name,
                        const char *msg, const char *file, const char *function, int line) {
  if (exp != act) {
    assert_err(msg, file, function, line, PRIMITIVE_ERR_MSG("%hu"), exp_name, act_name, exp, act);
  }
}

void __assert_eq_int(int exp, int act, const char *exp_name, const char *act_name, const char *msg, const char *file,
                     const char *function, int line) {
  if (exp != act) {
    assert_err(msg, file, function, line, PRIMITIVE_ERR_MSG("%d"), exp_name, act_name, exp, act);
  }
}
void __assert_eq_uint(unsigned int exp, unsigned int act, const char *exp_name, const char *act_name, const char *msg,
                      const char *file, const char *function, int line) {
  if (exp != act) {
    assert_err(msg, file, function, line, PRIMITIVE_ERR_MSG("%u"), exp_name, act_name, exp, act);
  }
}

void __assert_eq_long(long exp, long act, const char *exp_name, const char *act_name, const char *msg, const char *file,
                      const char *function, int line) {
  if (exp != act) {
    assert_err(msg, file, function, line, PRIMITIVE_ERR_MSG("%ld"), exp_name, act_name, exp, act);
  }
}
void __assert_eq_ulong(unsigned long exp, unsigned long act, const char *exp_name, const char *act_name,
                       const char *msg, const char *file, const char *function, int line) {
  if (exp != act) {
    assert_err(msg, file, function, line, PRIMITIVE_ERR_MSG("%lu"), exp_name, act_name, exp, act);
  }
}

void __assert_eq_longlong(long long exp, long long act, const char *exp_name, const char *act_name, const char *msg,
                          const char *file, const char *function, int line) {
  if (exp != act) {
    assert_err(msg, file, function, line, PRIMITIVE_ERR_MSG("%lld"), exp_name, act_name, exp, act);
  }
}
void __assert_eq_ulonglong(unsigned long long exp, unsigned long long act, const char *exp_name, const char *act_name,
                           const char *msg, const char *file, const char *function, int line) {
  if (exp != act) {
    assert_err(msg, file, function, line, PRIMITIVE_ERR_MSG("%llu"), exp_name, act_name, exp, act);
  }
}

void __assert_eq_float(float exp, float act, const char *exp_name, const char *act_name, const char *msg,
                       const char *file, const char *function, int line) {
  if (exp != act) {
    assert_err(msg, file, function, line, PRIMITIVE_ERR_MSG("%lf"), exp_name, act_name, exp, act);
  }
}
void __assert_eq_double(double exp, double act, const char *exp_name, const char *act_name, const char *msg,
                        const char *file, const char *function, int line) {
  if (exp != act) {
    assert_err(msg, file, function, line, PRIMITIVE_ERR_MSG("%lf"), exp_name, act_name, exp, act);
  }
}
void __assert_eq_longdouble(long double exp, long double act, const char *exp_name, const char *act_name,
                            const char *msg, const char *file, const char *function, int line) {
  if (exp != act) {
    assert_err(msg, file, function, line, PRIMITIVE_ERR_MSG("%llf"), exp_name, act_name, exp, act);
  }
}

void __assertItemEqualsMsg(void *exp, void *act, int elem_size_exp, int elem_size_b, const char *exp_name,
                           const char *act_name, const char *msg, const char *file, const char *function, int line) {
  if (elem_size_exp != elem_size_b) {
    assert_err(msg, file, function, line, "%s and %s are not of the same type.", exp_name, act_name);
    return;
  }
  byte *charA = (byte *)exp;
  byte *charB = (byte *)act;
  for (int i = 0; i < elem_size_exp; i++) {
    if (*charA != *charB) {
      assert_err(msg, file, function, line, "Items %s and %s are not equal.", exp_name, act_name);
      return;
    }
    charA++;
    charB++;
  }
}

int check_arr_size(int len_exp, int len_act, const char *exp_name, const char *act_name, const char *msg,
                   const char *file, const char *function, int line) {
  if (len_exp != len_act) {
    assert_err(msg, file, function, line, "%s and %s do not have the same length.\n\t\tExpected: %d\n\t\tActual: %d\n",
               exp_name, act_name, len_exp, len_act);
    return 0;
  }
  return 1;
}

// Arrays

void __assert_arr_eq_char(char *exp, char *act, int len_exp, int len_act, int elem_size_exp, int elem_size_b,
                          const char *exp_name, const char *act_name, const char *msg, const char *file,
                          const char *function, int line) {
  if (!check_arr_size(len_exp, len_act, exp_name, act_name, msg, file, function, line)) {
    return;
  }
  for (int i = 0; i < len_exp; i++) {
    if (exp[i] != act[i]) {
      assert_err(msg, file, function, line, ARRAY_ERR_MSG("%c"), exp_name, act_name, i, exp[i], act[i]);
      return;
    }
  }
}

void __assert_arr_eq_uchar(unsigned char *exp, unsigned char *act, int len_exp, int len_act, int elem_size_exp,
                           int elem_size_b, const char *exp_name, const char *act_name, const char *msg,
                           const char *file, const char *function, int line) {
  if (!check_arr_size(len_exp, len_act, exp_name, act_name, msg, file, function, line)) {
    return;
  }
  for (int i = 0; i < len_exp; i++) {
    if (exp[i] != act[i]) {
      assert_err(msg, file, function, line, ARRAY_ERR_MSG("%d"), exp_name, act_name, i, exp[i], act[i]);
      return;
    }
  }
}

void __assert_arr_eq_short(short *exp, short *act, int len_exp, int len_act, int elem_size_exp, int elem_size_b,
                           const char *exp_name, const char *act_name, const char *msg, const char *file,
                           const char *function, int line) {
  if (!check_arr_size(len_exp, len_act, exp_name, act_name, msg, file, function, line)) {
    return;
  }
  for (int i = 0; i < len_exp; i++) {
    if (exp[i] != act[i]) {
      assert_err(msg, file, function, line, ARRAY_ERR_MSG("%hd"), exp_name, act_name, i, exp[i], act[i]);
      return;
    }
  }
}
void __assert_arr_eq_ushort(unsigned short *exp, unsigned short *act, int len_exp, int len_act, int elem_size_exp,
                            int elem_size_b, const char *exp_name, const char *act_name, const char *msg,
                            const char *file, const char *function, int line) {
  if (!check_arr_size(len_exp, len_act, exp_name, act_name, msg, file, function, line)) {
    return;
  }
  for (int i = 0; i < len_exp; i++) {
    if (exp[i] != act[i]) {
      assert_err(msg, file, function, line, ARRAY_ERR_MSG("%hu"), exp_name, act_name, i, exp[i], act[i]);
      return;
    }
  }
}

void __assert_arr_eq_int(int *exp, int *act, int len_exp, int len_act, int elem_size_exp, int elem_size_b,
                         const char *exp_name, const char *act_name, const char *msg, const char *file,
                         const char *function, int line) {
  if (!check_arr_size(len_exp, len_act, exp_name, act_name, msg, file, function, line)) {
    return;
  }
  for (int i = 0; i < len_exp; i++) {
    if (exp[i] != act[i]) {
      assert_err(msg, file, function, line, ARRAY_ERR_MSG("%d"), exp_name, act_name, i, exp[i], act[i]);
      return;
    }
  }
}
void __assert_arr_eq_uint(unsigned int *exp, unsigned int *act, int len_exp, int len_act, int elem_size_exp,
                          int elem_size_b, const char *exp_name, const char *act_name, const char *msg,
                          const char *file, const char *function, int line) {
  if (!check_arr_size(len_exp, len_act, exp_name, act_name, msg, file, function, line)) {
    return;
  }
  for (int i = 0; i < len_exp; i++) {
    if (exp[i] != act[i]) {
      assert_err(msg, file, function, line, ARRAY_ERR_MSG("%u"), exp_name, act_name, i, exp[i], act[i]);
      return;
    }
  }
}

void __assert_arr_eq_long(long *exp, long *act, int len_exp, int len_act, int elem_size_exp, int elem_size_b,
                          const char *exp_name, const char *act_name, const char *msg, const char *file,
                          const char *function, int line) {
  if (!check_arr_size(len_exp, len_act, exp_name, act_name, msg, file, function, line)) {
    return;
  }
  for (int i = 0; i < len_exp; i++) {
    if (exp[i] != act[i]) {
      assert_err(msg, file, function, line, ARRAY_ERR_MSG("%ld"), exp_name, act_name, i, exp[i], act[i]);
      return;
    }
  }
}
void __assert_arr_eq_ulong(unsigned long *exp, unsigned long *act, int len_exp, int len_act, int elem_size_exp,
                           int elem_size_b, const char *exp_name, const char *act_name, const char *msg,
                           const char *file, const char *function, int line) {
  if (!check_arr_size(len_exp, len_act, exp_name, act_name, msg, file, function, line)) {
    return;
  }
  for (int i = 0; i < len_exp; i++) {
    if (exp[i] != act[i]) {
      assert_err(msg, file, function, line, ARRAY_ERR_MSG("%lu"), exp_name, act_name, i, exp[i], act[i]);
      return;
    }
  }
}

void __assert_arr_eq_longlong(long long *exp, long long *act, int len_exp, int len_act, int elem_size_exp,
                              int elem_size_b, const char *exp_name, const char *act_name, const char *msg,
                              const char *file, const char *function, int line) {
  if (!check_arr_size(len_exp, len_act, exp_name, act_name, msg, file, function, line)) {
    return;
  }
  for (int i = 0; i < len_exp; i++) {
    if (exp[i] != act[i]) {
      assert_err(msg, file, function, line, ARRAY_ERR_MSG("%lld"), exp_name, act_name, i, exp[i], act[i]);
      return;
    }
  }
}
void __assert_arr_eq_ulonglong(unsigned long long *exp, unsigned long long *act, int len_exp, int len_act,
                               int elem_size_exp, int elem_size_b, const char *exp_name, const char *act_name,
                               const char *msg, const char *file, const char *function, int line) {
  if (!check_arr_size(len_exp, len_act, exp_name, act_name, msg, file, function, line)) {
    return;
  }
  for (int i = 0; i < len_exp; i++) {
    if (exp[i] != act[i]) {
      assert_err(msg, file, function, line, ARRAY_ERR_MSG("%llu"), exp_name, act_name, i, exp[i], act[i]);
      return;
    }
  }
}

void __assert_arr_eq_float(float *exp, float *act, int len_exp, int len_act, int elem_size_exp, int elem_size_b,
                           const char *exp_name, const char *act_name, const char *msg, const char *file,
                           const char *function, int line) {
  if (!check_arr_size(len_exp, len_act, exp_name, act_name, msg, file, function, line)) {
    return;
  }
  for (int i = 0; i < len_exp; i++) {
    if (exp[i] != act[i]) {
      assert_err(msg, file, function, line, ARRAY_ERR_MSG("%lf"), exp_name, act_name, i, exp[i], act[i]);
      return;
    }
  }
}
void __assert_arr_eq_double(double *exp, double *act, int len_exp, int len_act, int elem_size_exp, int elem_size_b,
                            const char *exp_name, const char *act_name, const char *msg, const char *file,
                            const char *function, int line) {
  if (!check_arr_size(len_exp, len_act, exp_name, act_name, msg, file, function, line)) {
    return;
  }
  for (int i = 0; i < len_exp; i++) {
    if (exp[i] != act[i]) {
      assert_err(msg, file, function, line, ARRAY_ERR_MSG("%lf"), exp_name, act_name, i, exp[i], act[i]);
      return;
    }
  }
}
void __assert_arr_eq_longdouble(long double *exp, long double *act, int len_exp, int len_act, int elem_size_exp,
                                int elem_size_b, const char *exp_name, const char *act_name, const char *msg,
                                const char *file, const char *function, int line) {
  if (!check_arr_size(len_exp, len_act, exp_name, act_name, msg, file, function, line)) {
    return;
  }
  for (int i = 0; i < len_exp; i++) {
    if (exp[i] != act[i]) {
      assert_err(msg, file, function, line, ARRAY_ERR_MSG("%llf"), exp_name, act_name, i, exp[i], act[i]);
      return;
    }
  }
}

void __assert_arr_eq_item(void *exp, void *act, int len_exp, int len_act, int elem_size_exp, int elem_size_b,
                          const char *exp_name, const char *act_name, const char *msg, const char *file,
                          const char *function, int line) {
  if (elem_size_exp != elem_size_b) {
    assert_err(msg, file, function, line, "%s and %s do not contain equal types.", exp_name, act_name);
    return;
  }
  if (len_exp != len_act) {
    assert_err(msg, file, function, line, "%s and %s do not have the same length.\n\t\tExpected: %d\n\t\tActual: %d\n",
               exp_name, act_name, len_exp, len_act);
    return;
  }
  byte *charA = (byte *)exp;
  byte *charB = (byte *)act;
  for (int i = 0; i < len_exp; i++) {
    for (int j = 0; j < elem_size_exp; j++) {
      if (*charA != *charB) {
        assert_err(msg, file, function, line, "%s and %s do not match at index %d\n", exp_name, act_name, i);
        return;
      }
      charA++;
      charB++;
    }
  }
}

void __start_section(const char *section_name) {
  // TODO: based on terminal width
  fprintf(stderr, "\n");
  print_divider();
  fprintf(stderr, "\t%sSection: %s%s\n", CODE_BOLD, section_name, CODE_RESET);
  print_divider();
  fprintf(stderr, "\n");
}

static void __startTest(const char *test_name) {
  if (test_status != -1) {
    warning("Cannot start exp test while the previous test has not been terminated.\n");
    return;
  }
  err_msg[0] = '\0';
  test_status = 1;
}

static void __endTest(const char *test_name, struct timeval time) {
  if (test_status == -1) {
    warning("Cannot end exp test that has not been started yet.\n");
    return;
  }

  if (test_status > 0) {
    passed++;
    fprintf(stderr, "%s [Pass]%s %s%s (%ld.%01lds)%s\n", CODE_GREEN, CODE_RESET, CODE_BOLD, test_name,
            (size_t)time.tv_sec, (size_t)(time.tv_usec / 100000.0), CODE_RESET);

  } else {
    failed++;
    fprintf(stderr, "%s [Fail]%s %s%s (%ld.%01lds)%s\n", CODE_RED, CODE_RESET, CODE_BOLD, test_name,
            (size_t)time.tv_sec, (size_t)(time.tv_usec / 100000.0), CODE_RESET);
    fprintf(stderr, "%s", err_msg);
  }
  test_status = -1;
}

void __execute_test(void (*fp)(), const char *name) {
  struct timeval before = {0};
  struct timeval after = {0};
  struct timeval result = {0};
  __startTest(name);
  gettimeofday(&before, NULL);
  fp();
  gettimeofday(&after, NULL);
  timersub(&after, &before, &result);
  __endTest(name, result);
}

void __start_test_suite() {
  fprintf(stderr, "Initializing test suite...\n");
  test_status = -1;
  passed = 0;
  failed = 0;
}

void __end_test_suite() {
  fprintf(stderr, "\n");
  print_divider();
  fprintf(stderr, "\n%sTests:%s ", CODE_BOLD, CODE_RESET);
  if (passed > 0) {
    fprintf(stderr, "%s%d Passed%s, ", CODE_GREEN, passed, CODE_RESET);
  }
  if (failed > 0) {
    fprintf(stderr, "%s%d Failed%s, ", CODE_RED, failed, CODE_RESET);
  }
  fprintf(stderr, "%d Total\n", passed + failed);

  if (failed == 0 && passed > 0) {
    fprintf(stderr, "%s", CODE_GREEN);
    fprintf(stderr, "All tests passed.\n");
  } else if (passed == 0 && failed == 0) {
    fprintf(stderr, "%s", CODE_ORANGE);
    fprintf(stderr, "No tests were run.\n");
  } else {
    fprintf(stderr, "%s", CODE_RED);
    fprintf(stderr, "There are test failures.\n");
  }
  fprintf(stderr, "%s", CODE_RESET);
  fflush(stderr);
  exit(failed > 0 ? EXIT_FAILURE : EXIT_SUCCESS);
}
