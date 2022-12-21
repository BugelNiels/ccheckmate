#ifndef C_CHECKMATE_H
#define C_CHECKMATE_H

// TODO: function overloading to prevent separate message thing
// TODO: use this also for solving literal thing?

// #define assertEquals(A, B) __assertItemEqualsMsg(&A, &B, sizeof(A), sizeof(B), #A, #B, "", __FILE__, __FUNCTION__,
// __LINE__) #define assertEqualsMsg(A, B, MSG) __assertItemEqualsMsg(&A, &B, sizeof(A), sizeof(B), #A, #B, MSG,
// __FILE__, __FUNCTION__, __LINE__)
#define assertArrayEquals(A, B, LEN_A, LEN_B)                                                                    \
    __assertItemArrayEqualsMsg(&A, &B, LEN_A, LEN_B, sizeof(*A), sizeof(*B), #A, #B, "", __FILE__, __FUNCTION__, \
                               __LINE__)
#define assertArrayEqualsMsg(A, B, LEN_A, LEN_B, MSG)                                                             \
    __assertItemArrayEqualsMsg(&A, &B, LEN_A, LEN_B, sizeof(*A), sizeof(*B), #A, #B, MSG, __FILE__, __FUNCTION__, \
                               __LINE__)

// TODO: do for all those lib functions
#define assertEquals(A, B)                                   \
    _Generic((A), char                                       \
             : __assertCharEqualsMsg, unsigned char          \
             : __assertuCharEqualsMsg, short                 \
             : __assertShortEqualsMsg, unsigned short        \
             : __assertuShortEqualsMsg, int                  \
             : __assertIntEqualsMsg, unsigned int            \
             : __assertuIntEqualsMsg, long                   \
             : __assertLongEqualsMsg, unsigned long          \
             : __assertuLongEqualsMsg, long long             \
             : __assertLongLongEqualsMsg, unsigned long long \
             : __assertuLongLongEqualsMsg, float             \
             : __assertFloatEqualsMsg, double                \
             : __assertDoubleEqualsMsg, long double          \
             : __assertLongDoubleEqualsMsg)(A, B, #A, #B, "", __FILE__, __FUNCTION__, __LINE__)

#define assertEqualsMsg(A, B, MSG)                           \
    _Generic((A), char                                       \
             : __assertCharEqualsMsg, unsigned char          \
             : __assertuCharEqualsMsg, short                 \
             : __assertShortEqualsMsg, unsigned short        \
             : __assertuShortEqualsMsg, int                  \
             : __assertIntEqualsMsg, unsigned int            \
             : __assertuIntEqualsMsg, long                   \
             : __assertLongEqualsMsg, unsigned long          \
             : __assertuLongEqualsMsg, long long             \
             : __assertLongLongEqualsMsg, unsigned long long \
             : __assertuLongLongEqualsMsg, float             \
             : __assertFloatEqualsMsg, double                \
             : __assertDoubleEqualsMsg, long double          \
             : __assertLongDoubleEqualsMsg)(A, B, #A, #B, MSG, __FILE__, __FUNCTION__, __LINE__)

#define startTest() __startTest(__FUNCTION__)
#define endTest() __endTest(__FUNCTION__)
#define cTest(func) __executeTest(func, #func)

void __assertCharEqualsMsg(char a, char b, const char *aName, const char *bName, const char *msg, const char *file,
                           const char *function, int line);
void __assertuCharEqualsMsg(unsigned char a, unsigned char b, const char *aName, const char *bName, const char *msg,
                            const char *file, const char *function, int line);

void __assertShortEqualsMsg(short a, short b, const char *aName, const char *bName, const char *msg, const char *file,
                            const char *function, int line);
void __assertuShortEqualsMsg(unsigned short a, unsigned short b, const char *aName, const char *bName, const char *msg,
                             const char *file, const char *function, int line);

void __assertIntEqualsMsg(int a, int b, const char *aName, const char *bName, const char *msg, const char *file,
                          const char *function, int line);
void __assertuIntEqualsMsg(unsigned int a, unsigned int b, const char *aName, const char *bName, const char *msg,
                           const char *file, const char *function, int line);

void __assertLongEqualsMsg(long a, long b, const char *aName, const char *bName, const char *msg, const char *file,
                           const char *function, int line);
void __assertuLongEqualsMsg(unsigned long a, unsigned long b, const char *aName, const char *bName, const char *msg,
                            const char *file, const char *function, int line);

void __assertLongLongEqualsMsg(long long a, long long b, const char *aName, const char *bName, const char *msg,
                               const char *file, const char *function, int line);
void __assertuLongLongEqualsMsg(unsigned long long a, unsigned long long b, const char *aName, const char *bName,
                                const char *msg, const char *file, const char *function, int line);

void __assertFloatEqualsMsg(float a, float b, const char *aName, const char *bName, const char *msg, const char *file,
                            const char *function, int line);
void __assertDoubleEqualsMsg(double a, double b, const char *aName, const char *bName, const char *msg,
                             const char *file, const char *function, int line);
void __assertLongDoubleEqualsMsg(long double a, long double b, const char *aName, const char *bName, const char *msg,
                                 const char *file, const char *function, int line);

void __assertItemEqualsMsg(void *a, void *b, int sizeA, int sizeB, const char *aName, const char *bName,
                           const char *msg, const char *file, const char *function, int line);
void __assertItemArrayEqualsMsg(void *a, void *b, int sizeA, int sizeB, int elementSizeA, int elementSizeB,
                                const char *aName, const char *bName, const char *msg, const char *file,
                                const char *function, int line);

void startSection(const char *sectionName);

void __executeTest(void (*fp)(), const char *testName);

void __startTest(const char *testName);
void __endTest(const char *testName);

void startTestSuite();
void endTestSuite();

#endif
