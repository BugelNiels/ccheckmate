#include "ccheckmate.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CODE_BOLD "\e[1;37m"
#define CODE_RESET "\x1B[0m"
#define CODE_RED "\e[1;31m"
#define CODE_GREEN "\e[1;32m"
#define CODE_ORANGE "\e[1;33m"

#define PRIMITIVE_ERR_MSG(FORMAT) "%s and %s are not equal.\n\t\tExpected: " FORMAT "\n\t\tActual: " FORMAT "\n"
#define ARRAY_ERR_MSG(FORMAT) \
    "%s and %s, items at index %d do not match.\n\t\tExpected: " FORMAT "\n\t\tActual: " FORMAT "\n"

// TODO: see if we can remove the global variables :o

static int testStatus = -1;
static int passed = 0;
static int failed = 0;
static char errMsg[2048];

typedef char byte;

static void assertError(const char *usrMsg, const char *file, const char *function, int line, const char *format, ...) {
    // fprintf(stderr, "%s", CODE_BLUE);
    char *tmp = errMsg;
    tmp += sprintf(tmp, "\t==> %s:%s():%d\n\t==> %sfailure: %s", file, function, line, CODE_RED, CODE_RESET);
    va_list args;
    va_start(args, format);
    tmp += vsprintf(tmp, format, args);
    va_end(args);
    if (strlen(usrMsg) > 0) {
        tmp += sprintf(tmp, "\t==> Message: %s\n", usrMsg);
    }
    testStatus = 0;
}

static void warning(const char *format, ...) {
    fprintf(stderr, "Warning: ");
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}

static void printDivider() { fprintf(stderr, "--------------------------------------------------\n"); }

// Primitives

void __assertCharEquals(char a, char b, const char *aName, const char *bName, const char *msg, const char *file,
                        const char *function, int line) {
    if (a != b) {
        assertError(msg, file, function, line, PRIMITIVE_ERR_MSG("%c"), aName, bName, a, b);
    }
}
void __assertuCharEquals(unsigned char a, unsigned char b, const char *aName, const char *bName, const char *msg,
                         const char *file, const char *function, int line) {
    if (a != b) {
        assertError(msg, file, function, line, PRIMITIVE_ERR_MSG("%d"), aName, bName, a, b);
    }
}

void __assertShortEquals(short a, short b, const char *aName, const char *bName, const char *msg, const char *file,
                         const char *function, int line) {
    if (a != b) {
        assertError(msg, file, function, line, PRIMITIVE_ERR_MSG("%hd"), aName, bName, a, b);
    }
}
void __assertuShortEquals(unsigned short a, unsigned short b, const char *aName, const char *bName, const char *msg,
                          const char *file, const char *function, int line) {
    if (a != b) {
        assertError(msg, file, function, line, PRIMITIVE_ERR_MSG("%hu"), aName, bName, a, b);
    }
}

void __assertIntEquals(int a, int b, const char *aName, const char *bName, const char *msg, const char *file,
                       const char *function, int line) {
    if (a != b) {
        assertError(msg, file, function, line, PRIMITIVE_ERR_MSG("%d"), aName, bName, a, b);
    }
}
void __assertuIntEquals(unsigned int a, unsigned int b, const char *aName, const char *bName, const char *msg,
                        const char *file, const char *function, int line) {
    if (a != b) {
        assertError(msg, file, function, line, PRIMITIVE_ERR_MSG("%u"), aName, bName, a, b);
    }
}

void __assertLongEquals(long a, long b, const char *aName, const char *bName, const char *msg, const char *file,
                        const char *function, int line) {
    if (a != b) {
        assertError(msg, file, function, line, PRIMITIVE_ERR_MSG("%ld"), aName, bName, a, b);
    }
}
void __assertuLongEquals(unsigned long a, unsigned long b, const char *aName, const char *bName, const char *msg,
                         const char *file, const char *function, int line) {
    if (a != b) {
        assertError(msg, file, function, line, PRIMITIVE_ERR_MSG("%lu"), aName, bName, a, b);
    }
}

void __assertLongLongEquals(long long a, long long b, const char *aName, const char *bName, const char *msg,
                            const char *file, const char *function, int line) {
    if (a != b) {
        assertError(msg, file, function, line, PRIMITIVE_ERR_MSG("%lld"), aName, bName, a, b);
    }
}
void __assertuLongLongEquals(unsigned long long a, unsigned long long b, const char *aName, const char *bName,
                             const char *msg, const char *file, const char *function, int line) {
    if (a != b) {
        assertError(msg, file, function, line, PRIMITIVE_ERR_MSG("%llu"), aName, bName, a, b);
    }
}

void __assertFloatEquals(float a, float b, const char *aName, const char *bName, const char *msg, const char *file,
                         const char *function, int line) {
    if (a != b) {
        assertError(msg, file, function, line, PRIMITIVE_ERR_MSG("%lf"), aName, bName, a, b);
    }
}
void __assertDoubleEquals(double a, double b, const char *aName, const char *bName, const char *msg, const char *file,
                          const char *function, int line) {
    if (a != b) {
        assertError(msg, file, function, line, PRIMITIVE_ERR_MSG("%lf"), aName, bName, a, b);
    }
}
void __assertLongDoubleEquals(long double a, long double b, const char *aName, const char *bName, const char *msg,
                              const char *file, const char *function, int line) {
    if (a != b) {
        assertError(msg, file, function, line, PRIMITIVE_ERR_MSG("%llf"), aName, bName, a, b);
    }
}

void __assertItemEqualsMsg(void *a, void *b, int sizeA, int sizeB, const char *aName, const char *bName,
                           const char *msg, const char *file, const char *function, int line) {
    if (sizeA != sizeB) {
        assertError(msg, file, function, line, "%s and %s are not of the same type.", aName, bName);
        return;
    }
    byte *charA = (byte *)a;
    byte *charB = (byte *)b;
    for (int i = 0; i < sizeA; i++) {
        if (*charA != *charB) {
            assertError(msg, file, function, line, "Items %s and %s are not equal.", aName, bName);
            return;
        }
        charA++;
        charB++;
    }
}

int checkSize(int sizeA, int sizeB, const char *aName, const char *bName, const char *msg, const char *file,
              const char *function, int line) {
    if (sizeA != sizeB) {
        assertError(msg, file, function, line,
                    "%s and %s do not have the same length.\n\t\tExpected: %d\n\t\tActual: %d\n", aName, bName, sizeA,
                    sizeB);
        return 0;
    }
    return 1;
}

// Arrays

void __assertCharArrayEquals(char *a, char *b, int sizeA, int sizeB, int elementSizeA, int elementSizeB,
                             const char *aName, const char *bName, const char *msg, const char *file,
                             const char *function, int line) {
    if (!checkSize(sizeA, sizeB, aName, bName, msg, file, function, line)) {
        return;
    }
    for (int i = 0; i < sizeA; i++) {
        if (a[i] != b[i]) {
            assertError(msg, file, function, line, ARRAY_ERR_MSG("%c"), aName, bName, i, a[i], b[i]);
            return;
        }
    }
}

void __assertuCharArrayEquals(unsigned char *a, unsigned char *b, int sizeA, int sizeB, int elementSizeA,
                              int elementSizeB, const char *aName, const char *bName, const char *msg, const char *file,
                              const char *function, int line) {
    if (!checkSize(sizeA, sizeB, aName, bName, msg, file, function, line)) {
        return;
    }
    for (int i = 0; i < sizeA; i++) {
        if (a[i] != b[i]) {
            assertError(msg, file, function, line, ARRAY_ERR_MSG("%d"), aName, bName, i, a[i], b[i]);
            return;
        }
    }
}

void __assertShortArrayEquals(short *a, short *b, int sizeA, int sizeB, int elementSizeA, int elementSizeB,
                              const char *aName, const char *bName, const char *msg, const char *file,
                              const char *function, int line) {
    if (!checkSize(sizeA, sizeB, aName, bName, msg, file, function, line)) {
        return;
    }
    for (int i = 0; i < sizeA; i++) {
        if (a[i] != b[i]) {
            assertError(msg, file, function, line, ARRAY_ERR_MSG("%hd"), aName, bName, i, a[i], b[i]);
            return;
        }
    }
}
void __assertuShortArrayEquals(unsigned short *a, unsigned short *b, int sizeA, int sizeB, int elementSizeA,
                               int elementSizeB, const char *aName, const char *bName, const char *msg,
                               const char *file, const char *function, int line) {
    if (!checkSize(sizeA, sizeB, aName, bName, msg, file, function, line)) {
        return;
    }
    for (int i = 0; i < sizeA; i++) {
        if (a[i] != b[i]) {
            assertError(msg, file, function, line, ARRAY_ERR_MSG("%hu"), aName, bName, i, a[i], b[i]);
            return;
        }
    }
}

void __assertIntArrayEquals(int *a, int *b, int sizeA, int sizeB, int elementSizeA, int elementSizeB, const char *aName,
                            const char *bName, const char *msg, const char *file, const char *function, int line) {
    if (!checkSize(sizeA, sizeB, aName, bName, msg, file, function, line)) {
        return;
    }
    for (int i = 0; i < sizeA; i++) {
        if (a[i] != b[i]) {
            assertError(msg, file, function, line, ARRAY_ERR_MSG("%d"), aName, bName, i, a[i], b[i]);
            return;
        }
    }
}
void __assertuIntArrayEquals(unsigned int *a, unsigned int *b, int sizeA, int sizeB, int elementSizeA, int elementSizeB,
                             const char *aName, const char *bName, const char *msg, const char *file,
                             const char *function, int line) {
    if (!checkSize(sizeA, sizeB, aName, bName, msg, file, function, line)) {
        return;
    }
    for (int i = 0; i < sizeA; i++) {
        if (a[i] != b[i]) {
            assertError(msg, file, function, line, ARRAY_ERR_MSG("%u"), aName, bName, i, a[i], b[i]);
            return;
        }
    }
}

void __assertLongArrayEquals(long *a, long *b, int sizeA, int sizeB, int elementSizeA, int elementSizeB,
                             const char *aName, const char *bName, const char *msg, const char *file,
                             const char *function, int line) {
    if (!checkSize(sizeA, sizeB, aName, bName, msg, file, function, line)) {
        return;
    }
    for (int i = 0; i < sizeA; i++) {
        if (a[i] != b[i]) {
            assertError(msg, file, function, line, ARRAY_ERR_MSG("%ld"), aName, bName, i, a[i], b[i]);
            return;
        }
    }
}
void __assertuLongArrayEquals(unsigned long *a, unsigned long *b, int sizeA, int sizeB, int elementSizeA,
                              int elementSizeB, const char *aName, const char *bName, const char *msg, const char *file,
                              const char *function, int line) {
    if (!checkSize(sizeA, sizeB, aName, bName, msg, file, function, line)) {
        return;
    }
    for (int i = 0; i < sizeA; i++) {
        if (a[i] != b[i]) {
            assertError(msg, file, function, line, ARRAY_ERR_MSG("%lu"), aName, bName, i, a[i], b[i]);
            return;
        }
    }
}

void __assertLongLongArrayEquals(long long *a, long long *b, int sizeA, int sizeB, int elementSizeA, int elementSizeB,
                                 const char *aName, const char *bName, const char *msg, const char *file,
                                 const char *function, int line) {
    if (!checkSize(sizeA, sizeB, aName, bName, msg, file, function, line)) {
        return;
    }
    for (int i = 0; i < sizeA; i++) {
        if (a[i] != b[i]) {
            assertError(msg, file, function, line, ARRAY_ERR_MSG("%lld"), aName, bName, i, a[i], b[i]);
            return;
        }
    }
}
void __assertuLongLongArrayEquals(unsigned long long *a, unsigned long long *b, int sizeA, int sizeB, int elementSizeA,
                                  int elementSizeB, const char *aName, const char *bName, const char *msg,
                                  const char *file, const char *function, int line) {
    if (!checkSize(sizeA, sizeB, aName, bName, msg, file, function, line)) {
        return;
    }
    for (int i = 0; i < sizeA; i++) {
        if (a[i] != b[i]) {
            assertError(msg, file, function, line, ARRAY_ERR_MSG("%llu"), aName, bName, i, a[i], b[i]);
            return;
        }
    }
}

void __assertFloatArrayEquals(float *a, float *b, int sizeA, int sizeB, int elementSizeA, int elementSizeB,
                              const char *aName, const char *bName, const char *msg, const char *file,
                              const char *function, int line) {
    if (!checkSize(sizeA, sizeB, aName, bName, msg, file, function, line)) {
        return;
    }
    for (int i = 0; i < sizeA; i++) {
        if (a[i] != b[i]) {
            assertError(msg, file, function, line, ARRAY_ERR_MSG("%lf"), aName, bName, i, a[i], b[i]);
            return;
        }
    }
}
void __assertDoubleArrayEquals(double *a, double *b, int sizeA, int sizeB, int elementSizeA, int elementSizeB,
                               const char *aName, const char *bName, const char *msg, const char *file,
                               const char *function, int line) {
    if (!checkSize(sizeA, sizeB, aName, bName, msg, file, function, line)) {
        return;
    }
    for (int i = 0; i < sizeA; i++) {
        if (a[i] != b[i]) {
            assertError(msg, file, function, line, ARRAY_ERR_MSG("%lf"), aName, bName, i, a[i], b[i]);
            return;
        }
    }
}
void __assertLongDoubleArrayEquals(long double *a, long double *b, int sizeA, int sizeB, int elementSizeA,
                                   int elementSizeB, const char *aName, const char *bName, const char *msg,
                                   const char *file, const char *function, int line) {
    if (!checkSize(sizeA, sizeB, aName, bName, msg, file, function, line)) {
        return;
    }
    for (int i = 0; i < sizeA; i++) {
        if (a[i] != b[i]) {
            assertError(msg, file, function, line, ARRAY_ERR_MSG("%llf"), aName, bName, i, a[i], b[i]);
            return;
        }
    }
}

void __assertItemArrayEqualsMsg(void *a, void *b, int sizeA, int sizeB, int elementSizeA, int elementSizeB,
                                const char *aName, const char *bName, const char *msg, const char *file,
                                const char *function, int line) {
    if (elementSizeA != elementSizeB) {
        assertError(msg, file, function, line, "%s and %s do not contain equal types.", aName, bName);
        return;
    }
    if (sizeA != sizeB) {
        assertError(msg, file, function, line,
                    "%s and %s do not have the same length.\n\t\tExpected: %d\n\t\tActual: %d\n", aName, bName, sizeA,
                    sizeB);
        return;
    }

    // Check that char is size 1
    byte *charA = (byte *)a;
    byte *charB = (byte *)b;
    for (int i = 0; i < sizeA; i++) {
        for (int j = 0; j < elementSizeA; j++) {
            if (*charA != *charB) {
                assertError(msg, file, function, line, "%s and %s do not match at index %d\n", aName, bName, i);
                return;
            }
            charA++;
            charB++;
        }
    }
}

void startSection(const char *sectionName) {
    // TODO: based on terminal width
    fprintf(stderr, "\n");
    printDivider();
    fprintf(stderr, "\t%sSection: %s%s\n", CODE_BOLD, sectionName, CODE_RESET);
    printDivider();
    fprintf(stderr, "\n");
}

static void __startTest(const char *testName) {
    if (testStatus != -1) {
        warning("Cannot start a test while the previous test has not been terminated.\n");
        return;
    }
    errMsg[0] = '\0';
    testStatus = 1;
}

static void __endTest(const char *testName) {
    if (testStatus == -1) {
        warning("Cannot end a test that has not been started yet.\n");
        return;
    }

    if (testStatus > 0) {
        passed++;
        fprintf(stderr, "%s [Pass]%s %s%s%s\n", CODE_GREEN, CODE_RESET, CODE_BOLD, testName, CODE_RESET);

    } else {
        failed++;
        fprintf(stderr, "%s [Fail]%s %s%s%s\n", CODE_RED, CODE_RESET, CODE_BOLD, testName, CODE_RESET);
        fprintf(stderr, "%s", errMsg);
    }
    testStatus = -1;
}

void __executeTest(void (*fp)(), const char *name) {
    __startTest(name);
    fp();
    __endTest(name);
}

void startTestSuite() {
    fprintf(stderr, "Initializing test suite...\n");
    static int testStatus = -1;
    static int passed = 0;
    static int failed = 0;
}

void endTestSuite() {
    fprintf(stderr, "\n");
    printDivider();
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
}
