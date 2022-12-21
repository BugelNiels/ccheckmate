#include "ccheckmate.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CODE_RESET "\x1B[0m"
#define CODE_RED "\x1B[31m"
#define CODE_GREEN "\x1B[32m"
#define CODE_BLUE "\x1B[34m"

// TODO: use global variables :o
// TODO: print the variables being compared
// TODO: use checkmarks/colors

static int testStatus = -1;

static int passed = 0;
static int failed = 0;

typedef char byte;

void __executeTest(void (*fp)(), const char *name) {
    __startTest(name);
    fp();
    __endTest(name);
}

static void assertError(const char *usrMsg, const char *file, const char *function, int line, const char *format, ...) {
    // fprintf(stderr, "%s", CODE_BLUE);
    fprintf(stderr, "      %s:%s():%d %s failure: %s", file, function, line, CODE_RED, CODE_RESET);
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    if (strlen(usrMsg) == 0) {
        fprintf(stderr, "\n");
    } else {
        fprintf(stderr, "\n      %s\n", usrMsg);
    }
    // fprintf(stderr, "%s", CODE_RESET);
    testStatus = 0;
}

static void warning(const char *format, ...) {
    fprintf(stderr, "Warning: ");
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}

void successPrint(const char *format, ...) {
    fprintf(stderr, "%s", CODE_GREEN);
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, "%s", CODE_RESET);
}

void failPrint(const char *format, ...) {
    fprintf(stderr, "%s", CODE_RED);
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, "%s", CODE_RESET);
}

// TODO: check these print formattings
void __assertCharEqualsMsg(char a, char b, const char *aName, const char *bName, const char *msg, const char *file,
                           const char *function, int line) {
    if (a != b) {
        assertError(msg, file, function, line, "%s and %s are not equal. %c vs %c.\n", aName, bName, a, b);
    }
}
void __assertuCharEqualsMsg(unsigned char a, unsigned char b, const char *aName, const char *bName, const char *msg,
                            const char *file, const char *function, int line) {
    if (a != b) {
        assertError(msg, file, function, line, "%s and %s are not equal. %c vs %c.\n", aName, bName, a, b);
    }
}

void __assertShortEqualsMsg(short a, short b, const char *aName, const char *bName, const char *msg, const char *file,
                            const char *function, int line) {
    if (a != b) {
        assertError(msg, file, function, line, "%s and %s are not equal. %c vs %c.\n", aName, bName, a, b);
    }
}
void __assertuShortEqualsMsg(unsigned short a, unsigned short b, const char *aName, const char *bName, const char *msg,
                             const char *file, const char *function, int line) {
    if (a != b) {
        assertError(msg, file, function, line, "%s and %s are not equal. %c vs %c.\n", aName, bName, a, b);
    }
}

void __assertIntEqualsMsg(int a, int b, const char *aName, const char *bName, const char *msg, const char *file,
                          const char *function, int line) {
    if (a != b) {
        assertError(msg, file, function, line, "%s and %s are not equal. %d vs %d.\n", aName, bName, a, b);
    }
}
void __assertuIntEqualsMsg(unsigned int a, unsigned int b, const char *aName, const char *bName, const char *msg,
                           const char *file, const char *function, int line) {
    if (a != b) {
        assertError(msg, file, function, line, "%s and %s are not equal. %u vs %u.\n", aName, bName, a, b);
    }
}

void __assertLongEqualsMsg(long a, long b, const char *aName, const char *bName, const char *msg, const char *file,
                           const char *function, int line) {
    if (a != b) {
        assertError(msg, file, function, line, "%s and %s are not equal. %ld vs %ld.\n", aName, bName, a, b);
    }
}
void __assertuLongEqualsMsg(unsigned long a, unsigned long b, const char *aName, const char *bName, const char *msg,
                            const char *file, const char *function, int line) {
    if (a != b) {
        assertError(msg, file, function, line, "%s and %s are not equal. %lu vs %lu.\n", aName, bName, a, b);
    }
}

void __assertLongLongEqualsMsg(long long a, long long b, const char *aName, const char *bName, const char *msg,
                               const char *file, const char *function, int line) {
    if (a != b) {
        assertError(msg, file, function, line, "%s and %s are not equal. %lld vs %lld.\n", aName, bName, a, b);
    }
}
void __assertuLongLongEqualsMsg(unsigned long long a, unsigned long long b, const char *aName, const char *bName,
                                const char *msg, const char *file, const char *function, int line) {
    if (a != b) {
        assertError(msg, file, function, line, "%s and %s are not equal. %llu vs %llu.\n", aName, bName, a, b);
    }
}

void __assertFloatEqualsMsg(float a, float b, const char *aName, const char *bName, const char *msg, const char *file,
                            const char *function, int line) {
    if (a != b) {
        assertError(msg, file, function, line, "%s and %s are not equal. %lf vs %lf.\n", aName, bName, a, b);
    }
}
void __assertDoubleEqualsMsg(double a, double b, const char *aName, const char *bName, const char *msg,
                             const char *file, const char *function, int line) {
    if (a != b) {
        assertError(msg, file, function, line, "%s and %s are not equal. %lf vs %lf.\n", aName, bName, a, b);
    }
}
void __assertLongDoubleEqualsMsg(long double a, long double b, const char *aName, const char *bName, const char *msg,
                                 const char *file, const char *function, int line) {
    if (a != b) {
        assertError(msg, file, function, line, "%s and %s are not equal. %llf vs %llf.\n", aName, bName, a, b);
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

void __assertItemArrayEqualsMsg(void *a, void *b, int sizeA, int sizeB, int elementSizeA, int elementSizeB,
                                const char *aName, const char *bName, const char *msg, const char *file,
                                const char *function, int line) {
    if (elementSizeA != elementSizeB) {
        assertError(msg, file, function, line, "Provided arrays %s and %s do not contain equal type.", aName, bName);
        return;
    }
    if (sizeA != sizeB) {
        assertError(msg, file, function, line, "Provided arrays %s and %s do not have the same length.", aName, bName);
        return;
    }

    // Check that char is size 1
    byte *charA = (byte *)a;
    byte *charB = (byte *)b;
    for (int i = 0; i < sizeA; i++) {
        for (int j = 0; j < elementSizeA; j++) {
            if (*charA != *charB) {
                assertError(msg, file, function, line, "Contents of provided arrays %s and %s do not match.", aName,
                            bName);
                return;
            }
            charA++;
            charB++;
        }
    }
}

void startTestSuite() {
    fprintf(stderr, "Initializing test suite...\n\n");
    static int testStatus = -1;
    static int passed = 0;
    static int failed = 0;
}

void endTestSuite() {
    fprintf(stderr, "\nOutcomes: \n");
    fprintf(stderr, "  ✅ %d Passed\n  ❌ %d Failed\n", passed, failed);
    if (failed == 0 && passed > 0) {
        fprintf(stderr, " All tests passed.\n");
    } else if (passed == 0 && failed == 0) {
        fprintf(stderr, "No tests were run.\n");
    } else {
        fprintf(stderr, "There are test failures.\n");
    }
    fflush(stderr);
}

void startSection(const char *sectionName) { printf("Starting section: %s\n", sectionName); }

void __startTest(const char *testName) {
    if (testStatus != -1) {
        warning("Cannot start a test while the previous test has not been terminated.\n");
        return;
    }

    fprintf(stderr, "  Starting test: %s\n", testName);
    testStatus = 1;
}

void __endTest(const char *testName) {
    if (testStatus == -1) {
        warning("Cannot end a test that has not been started yet.\n");
        return;
    }
    if (testStatus > 0) {
        passed++;
        successPrint("    ✅ %s\n", testName);

    } else {
        failed++;
        failPrint("    ❌ %s\n", testName);
    }
    testStatus = -1;
}
