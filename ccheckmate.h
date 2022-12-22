#ifndef C_CHECKMATE_H
#define C_CHECKMATE_H

// TODO: default to error message for unrecongized types
// TODO: do for all those lib functions
#define assertEquals(A, B)                                \
    _Generic((A), char                                    \
             : __assertCharEquals, unsigned char          \
             : __assertuCharEquals, short                 \
             : __assertShortEquals, unsigned short        \
             : __assertuShortEquals, int                  \
             : __assertIntEquals, unsigned int            \
             : __assertuIntEquals, long                   \
             : __assertLongEquals, unsigned long          \
             : __assertuLongEquals, long long             \
             : __assertLongLongEquals, unsigned long long \
             : __assertuLongLongEquals, float             \
             : __assertFloatEquals, double                \
             : __assertDoubleEquals, long double          \
             : __assertLongDoubleEquals, default          \
             : __assertItemEquals)(A, B, #A, #B, "", __FILE__, __FUNCTION__, __LINE__)

#define assertEqualsMsg(A, B, MSG)                        \
    _Generic((A), char                                    \
             : __assertCharEquals, unsigned char          \
             : __assertuCharEquals, short                 \
             : __assertShortEquals, unsigned short        \
             : __assertuShortEquals, int                  \
             : __assertIntEquals, unsigned int            \
             : __assertuIntEquals, long                   \
             : __assertLongEquals, unsigned long          \
             : __assertuLongEquals, long long             \
             : __assertLongLongEquals, unsigned long long \
             : __assertuLongLongEquals, float             \
             : __assertFloatEquals, double                \
             : __assertDoubleEquals, long double          \
             : __assertLongDoubleEquals, default          \
             : __assertItemEquals)(A, B, #A, #B, MSG, __FILE__, __FUNCTION__, __LINE__)

#define assertArrayEquals(A, B, LEN_A, LEN_B) \
    _Generic((A), char                                       \
             : __assertCharArrayEquals, unsigned char*          \
             : __assertuCharArrayEquals, short*                 \
             : __assertShortArrayEquals, unsigned short*        \
             : __assertuShortArrayEquals, int*                  \
             : __assertIntArrayEquals, unsigned int*            \
             : __assertuIntArrayEquals, long*                   \
             : __assertLongArrayEquals, unsigned long*          \
             : __assertuLongArrayEquals, long long*             \
             : __assertLongLongArrayEquals, unsigned long long* \
             : __assertuLongLongArrayEquals, float*             \
             : __assertFloatArrayEquals, double*                \
             : __assertDoubleArrayEquals, long double*          \
             : __assertLongDoubleArrayEquals, default          \
             : __assertItemArrayEquals)(A, B, LEN_A, LEN_B, sizeof(*A), sizeof(*B), #A, #B, "", __FILE__, __FUNCTION__, __LINE__)

#define assertArrayEqualsMsg(A, B, LEN_A, LEN_B, MSG) \
    _Generic((A), char                                       \
             : __assertCharArrayEquals, unsigned char*          \
             : __assertuCharArrayEquals, short*                 \
             : __assertShortArrayEquals, unsigned short*        \
             : __assertuShortArrayEquals, int*                  \
             : __assertIntArrayEquals, unsigned int*            \
             : __assertuIntArrayEquals, long*                   \
             : __assertLongArrayEquals, unsigned long*          \
             : __assertuLongArrayEquals, long long*             \
             : __assertLongLongArrayEquals, unsigned long long* \
             : __assertuLongLongArrayEquals, float*             \
             : __assertFloatArrayEquals, double*                \
             : __assertDoubleArrayEquals, long double*          \
             : __assertLongDoubleArrayEquals, default          \
             : __assertItemArrayEquals)(A, B, LEN_A, LEN_B, sizeof(*A), sizeof(*B), #A, #B, MSG, __FILE__, __FUNCTION__, __LINE__)

#define cTest(func) __executeTest(func, #func)

void startSection(const char *sectionName);
void startTestSuite();
void endTestSuite();
void __executeTest(void (*fp)(), const char *testName);

// primitives

void __assertCharEquals(char a, char b, const char *aName, const char *bName, const char *msg, const char *file,
                        const char *function, int line);
void __assertuCharEquals(unsigned char a, unsigned char b, const char *aName, const char *bName, const char *msg,
                         const char *file, const char *function, int line);

void __assertShortEquals(short a, short b, const char *aName, const char *bName, const char *msg, const char *file,
                         const char *function, int line);
void __assertuShortEquals(unsigned short a, unsigned short b, const char *aName, const char *bName, const char *msg,
                          const char *file, const char *function, int line);

void __assertIntEquals(int a, int b, const char *aName, const char *bName, const char *msg, const char *file,
                       const char *function, int line);
void __assertuIntEquals(unsigned int a, unsigned int b, const char *aName, const char *bName, const char *msg,
                        const char *file, const char *function, int line);

void __assertLongEquals(long a, long b, const char *aName, const char *bName, const char *msg, const char *file,
                        const char *function, int line);
void __assertuLongEquals(unsigned long a, unsigned long b, const char *aName, const char *bName, const char *msg,
                         const char *file, const char *function, int line);

void __assertLongLongEquals(long long a, long long b, const char *aName, const char *bName, const char *msg,
                            const char *file, const char *function, int line);
void __assertuLongLongEquals(unsigned long long a, unsigned long long b, const char *aName, const char *bName,
                             const char *msg, const char *file, const char *function, int line);

void __assertFloatEquals(float a, float b, const char *aName, const char *bName, const char *msg, const char *file,
                         const char *function, int line);
void __assertDoubleEquals(double a, double b, const char *aName, const char *bName, const char *msg, const char *file,
                          const char *function, int line);
void __assertLongDoubleEquals(long double a, long double b, const char *aName, const char *bName, const char *msg,
                              const char *file, const char *function, int line);

void __assertItemEquals(void *a, void *b, int sizeA, int sizeB, const char *aName, const char *bName, const char *msg,
                        const char *file, const char *function, int line);

// Arrays

void __assertCharArrayEquals(char *a, char *b, int sizeA, int sizeB, int elementSizeA, int elementSizeB,
                             const char *aName, const char *bName, const char *msg, const char *file,
                             const char *function, int line);
void __assertuCharArrayEquals(unsigned char *a, unsigned char *b, int sizeA, int sizeB, int elementSizeA,
                              int elementSizeB, const char *aName, const char *bName, const char *msg, const char *file,
                              const char *function, int line);

void __assertShortArrayEquals(short *a, short *b, int sizeA, int sizeB, int elementSizeA, int elementSizeB,
                              const char *aName, const char *bName, const char *msg, const char *file,
                              const char *function, int line);
void __assertuShortArrayEquals(unsigned short *a, unsigned short *b, int sizeA, int sizeB, int elementSizeA,
                               int elementSizeB, const char *aName, const char *bName, const char *msg,
                               const char *file, const char *function, int line);

void __assertIntArrayEquals(int *a, int *b, int sizeA, int sizeB, int elementSizeA, int elementSizeB, const char *aName,
                            const char *bName, const char *msg, const char *file, const char *function, int line);
void __assertuIntArrayEquals(unsigned int *a, unsigned int *b, int sizeA, int sizeB, int elementSizeA, int elementSizeB,
                             const char *aName, const char *bName, const char *msg, const char *file,
                             const char *function, int line);

void __assertLongArrayEquals(long *a, long *b, int sizeA, int sizeB, int elementSizeA, int elementSizeB,
                             const char *aName, const char *bName, const char *msg, const char *file,
                             const char *function, int line);
void __assertuLongArrayEquals(unsigned long *a, unsigned long *b, int sizeA, int sizeB, int elementSizeA,
                              int elementSizeB, const char *aName, const char *bName, const char *msg, const char *file,
                              const char *function, int line);

void __assertLongLongArrayEquals(long long *a, long long *b, int sizeA, int sizeB, int elementSizeA, int elementSizeB,
                                 const char *aName, const char *bName, const char *msg, const char *file,
                                 const char *function, int line);
void __assertuLongLongArrayEquals(unsigned long long *a, unsigned long long *b, int sizeA, int sizeB, int elementSizeA,
                                  int elementSizeB, const char *aName, const char *bName, const char *msg,
                                  const char *file, const char *function, int line);

void __assertFloatArrayEquals(float *a, float *b, int sizeA, int sizeB, int elementSizeA, int elementSizeB,
                              const char *aName, const char *bName, const char *msg, const char *file,
                              const char *function, int line);
void __assertDoubleArrayEquals(double *a, double *b, int sizeA, int sizeB, int elementSizeA, int elementSizeB,
                               const char *aName, const char *bName, const char *msg, const char *file,
                               const char *function, int line);
void __assertLongDoubleArrayEquals(long double *a, long double *b, int sizeA, int sizeB, int elementSizeA,
                                   int elementSizeB, const char *aName, const char *bName, const char *msg,
                                   const char *file, const char *function, int line);

void __assertItemArrayEquals(void *a, void *b, int sizeA, int sizeB, int elementSizeA, int elementSizeB,
                             const char *aName, const char *bName, const char *msg, const char *file,
                             const char *function, int line);

#endif
