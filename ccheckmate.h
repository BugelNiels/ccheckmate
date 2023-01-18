#ifndef C_CHECKMATE_H
#define C_CHECKMATE_H

#include <stdio.h>
#include <stdlib.h>

#define ccm_begin_test_suite                \
  int __wrap_main(int argc, char *argv[]) { \
    __start_test_suite();

#define ccm_end_test_suite \
  __end_test_suite();      \
  return 0;                \
  }

#define ccm_begin_section                                            \
  struct __func_list {                                               \
    struct __func_list *next;                                        \
    void (*f)(void);                                                 \
    char *name;                                                      \
  } *head = NULL;                                                    \
  static void __testfunc_list_add(void (*f)(void), char *name) {     \
    if (head == NULL) {                                              \
      head = malloc(sizeof(struct __func_list));                     \
      head->next = NULL;                                             \
      head->f = f;                                                   \
      head->name = name;                                             \
    } else {                                                         \
      struct __func_list *item = malloc(sizeof(struct __func_list)); \
      item->next = NULL;                                             \
      item->f = f;                                                   \
      item->name = name;                                             \
      struct __func_list *cur = head;                                \
      while (cur->next != NULL) {                                    \
        cur = cur->next;                                             \
      }                                                              \
      cur->next = item;                                              \
    }                                                                \
  }

#define ccm_test(f)                                                                              \
  static void f(void);                                                                           \
  static void __attribute__((constructor)) __construct_##f(void) { __testfunc_list_add(f, #f); } \
  static void f(void)

#define MAKE_FN_NAME(x) void x(void)
#define FUNCTION_NAME(signal) MAKE_FN_NAME(signal)

#define ccm_end_section(A)                   \
  MAKE_FN_NAME(A) {                          \
    __start_section(#A);                     \
    struct __func_list *cur;                 \
    for (cur = head; cur; cur = cur->next) { \
      __execute_test(cur->f, cur->name);     \
    }                                        \
  }

#define assert_true(A) __assert_true((A), #A, "", __FILE__, __func__, __LINE__)
#define assert_false(A) __assert_false((A), #A, "", __FILE__, __func__, __LINE__)

#define assert_eq(A, B)                               \
  _Generic((A), char                                  \
           : __assert_eq_char, unsigned char          \
           : __assert_eq_uchar, short                 \
           : __assert_eq_short, unsigned short        \
           : __assert_eq_ushort, int                  \
           : __assert_eq_int, unsigned int            \
           : __assert_eq_uint, long                   \
           : __assert_eq_long, unsigned long          \
           : __assert_eq_ulong, long long             \
           : __assert_eq_longlong, unsigned long long \
           : __assert_eq_ulonglong, float             \
           : __assert_eq_float, double                \
           : __assert_eq_double, long double          \
           : __assert_eq_longdouble, default          \
           : __assert_eq_item)(A, B, #A, #B, "", __FILE__, __func__, __LINE__)

#define assert_eq_msg(A, B, MSG)                      \
  _Generic((A), char                                  \
           : __assert_eq_char, unsigned char          \
           : __assert_eq_uchar, short                 \
           : __assert_eq_short, unsigned short        \
           : __assert_eq_ushort, int                  \
           : __assert_eq_int, unsigned int            \
           : __assert_eq_uint, long                   \
           : __assert_eq_long, unsigned long          \
           : __assert_eq_ulong, long long             \
           : __assert_eq_longlong, unsigned long long \
           : __assert_eq_ulonglong, float             \
           : __assert_eq_float, double                \
           : __assert_eq_double, long double          \
           : __assert_eq_longdouble, default          \
           : __assert_eq_item)(A, B, #A, #B, MSG, __FILE__, __func__, __LINE__)

#define assert_arr_eq(A, B, LEN_A, LEN_B) \
  _Generic((A), char                                       \
             : __assert_arr_eq_char, unsigned char*          \
             : __assert_arr_eq_uchar, short*                 \
             : __assert_arr_eq_short, unsigned short*        \
             : __assert_arr_eq_ushort, int*                  \
             : __assert_arr_eq_int, unsigned int*            \
             : __assert_arr_eq_uint, long*                   \
             : __assert_arr_eq_long, unsigned long*          \
             : __assert_arr_eq_ulong, long long*             \
             : __assert_arr_eq_longlong, unsigned long long* \
             : __assert_arr_eq_ulonglong, float*             \
             : __assert_arr_eq_float, double*                \
             : __assert_arr_eq_double, long double*          \
             : __assert_arr_eq_longdouble, default           \
             : __assert_arr_eq_item)(A, B, LEN_A, LEN_B, sizeof(*A), sizeof(*B), #A, #B, "", __FILE__, __func__, __LINE__)

#define assert_arr_eq_msg(A, B, LEN_A, LEN_B, MSG) \
  _Generic((A), char                                       \
             : __assert_arr_eq_char, unsigned char*          \
             : __assert_arr_eq_uchar, short*                 \
             : __assert_arr_eq_short, unsigned short*        \
             : __assert_arr_eq_ushort, int*                  \
             : __assert_arr_eq_int, unsigned int*            \
             : __assert_arr_eq_uint, long*                   \
             : __assert_arr_eq_long, unsigned long*          \
             : __assert_arr_eq_ulong, long long*             \
             : __assert_arr_eq_longlong, unsigned long long* \
             : __assert_arr_eq_ulonglong, float*             \
             : __assert_arr_eq_float, double*                \
             : __assert_arr_eq_double, long double*          \
             : __assert_arr_eq_longdouble, default           \
             : __assert_arr_eq_item)(A, B, LEN_A, LEN_B, sizeof(*A), sizeof(*B), #A, #B, MSG, __FILE__, __func__, __LINE__)


void __start_test_suite();
void __end_test_suite();
void __start_section(const char *section_name);
void __execute_test(void (*fp)(), const char *test_name);

// booleans

void __assert_true(int bool_i, const char *bool_name, const char *msg, const char *file, const char *function,
                   int line);
void __assert_false(int bool_i, const char *bool_name, const char *msg, const char *file, const char *function,
                    int line);

// primitives

void __assert_eq_char(char exp, char act, const char *exp_name, const char *act_name, const char *msg, const char *file,
                      const char *function, int line);
void __assert_eq_uchar(unsigned char exp, unsigned char act, const char *exp_name, const char *act_name,
                       const char *msg, const char *file, const char *function, int line);

void __assert_eq_short(short exp, short act, const char *exp_name, const char *act_name, const char *msg,
                       const char *file, const char *function, int line);
void __assert_eq_ushort(unsigned short exp, unsigned short act, const char *exp_name, const char *act_name,
                        const char *msg, const char *file, const char *function, int line);

void __assert_eq_int(int exp, int act, const char *exp_name, const char *act_name, const char *msg, const char *file,
                     const char *function, int line);
void __assert_eq_uint(unsigned int exp, unsigned int act, const char *exp_name, const char *act_name, const char *msg,
                      const char *file, const char *function, int line);

void __assert_eq_long(long exp, long act, const char *exp_name, const char *act_name, const char *msg, const char *file,
                      const char *function, int line);
void __assert_eq_ulong(unsigned long exp, unsigned long act, const char *exp_name, const char *act_name,
                       const char *msg, const char *file, const char *function, int line);

void __assert_eq_longlong(long long exp, long long act, const char *exp_name, const char *act_name, const char *msg,
                          const char *file, const char *function, int line);
void __assert_eq_ulonglong(unsigned long long exp, unsigned long long act, const char *exp_name, const char *act_name,
                           const char *msg, const char *file, const char *function, int line);

void __assert_eq_float(float exp, float act, const char *exp_name, const char *act_name, const char *msg,
                       const char *file, const char *function, int line);
void __assert_eq_double(double exp, double act, const char *exp_name, const char *act_name, const char *msg,
                        const char *file, const char *function, int line);
void __assert_eq_longdouble(long double exp, long double act, const char *exp_name, const char *act_name,
                            const char *msg, const char *file, const char *function, int line);

void __assert_eq_item(void *exp, void *act, int len_exp, int len_act, const char *exp_name, const char *act_name,
                      const char *msg, const char *file, const char *function, int line);

// Arrays

void __assert_arr_eq_char(char *exp, char *act, int len_exp, int len_act, int elem_size_exp, int elem_size_act,
                          const char *exp_name, const char *act_name, const char *msg, const char *file,
                          const char *function, int line);
void __assert_arr_eq_uchar(unsigned char *exp, unsigned char *act, int len_exp, int len_act, int elem_size_exp,
                           int elem_size_act, const char *exp_name, const char *act_name, const char *msg,
                           const char *file, const char *function, int line);

void __assert_arr_eq_short(short *exp, short *act, int len_exp, int len_act, int elem_size_exp, int elem_size_act,
                           const char *exp_name, const char *act_name, const char *msg, const char *file,
                           const char *function, int line);
void __assert_arr_eq_ushort(unsigned short *exp, unsigned short *act, int len_exp, int len_act, int elem_size_exp,
                            int elem_size_act, const char *exp_name, const char *act_name, const char *msg,
                            const char *file, const char *function, int line);

void __assert_arr_eq_int(int *exp, int *act, int len_exp, int len_act, int elem_size_exp, int elem_size_act,
                         const char *exp_name, const char *act_name, const char *msg, const char *file,
                         const char *function, int line);
void __assert_arr_eq_uint(unsigned int *exp, unsigned int *act, int len_exp, int len_act, int elem_size_exp,
                          int elem_size_act, const char *exp_name, const char *act_name, const char *msg,
                          const char *file, const char *function, int line);

void __assert_arr_eq_long(long *exp, long *act, int len_exp, int len_act, int elem_size_exp, int elem_size_act,
                          const char *exp_name, const char *act_name, const char *msg, const char *file,
                          const char *function, int line);
void __assert_arr_eq_ulong(unsigned long *exp, unsigned long *act, int len_exp, int len_act, int elem_size_exp,
                           int elem_size_act, const char *exp_name, const char *act_name, const char *msg,
                           const char *file, const char *function, int line);

void __assert_arr_eq_longlong(long long *exp, long long *act, int len_exp, int len_act, int elem_size_exp,
                              int elem_size_act, const char *exp_name, const char *act_name, const char *msg,
                              const char *file, const char *function, int line);
void __assert_arr_eq_ulonglong(unsigned long long *exp, unsigned long long *act, int len_exp, int len_act,
                               int elem_size_exp, int elem_size_act, const char *exp_name, const char *act_name,
                               const char *msg, const char *file, const char *function, int line);

void __assert_arr_eq_float(float *exp, float *act, int len_exp, int len_act, int elem_size_exp, int elem_size_act,
                           const char *exp_name, const char *act_name, const char *msg, const char *file,
                           const char *function, int line);
void __assert_arr_eq_double(double *exp, double *act, int len_exp, int len_act, int elem_size_exp, int elem_size_act,
                            const char *exp_name, const char *act_name, const char *msg, const char *file,
                            const char *function, int line);
void __assert_arr_eq_longdouble(long double *exp, long double *act, int len_exp, int len_act, int elem_size_exp,
                                int elem_size_act, const char *exp_name, const char *act_name, const char *msg,
                                const char *file, const char *function, int line);

void __assert_arr_eq_item(void *exp, void *act, int len_exp, int len_act, int elem_size_exp, int elem_size_act,
                          const char *exp_name, const char *act_name, const char *msg, const char *file,
                          const char *function, int line);

#endif
