#include "cu/cu.h"

/* alloc.c */
TEST(heapAlloc);
TEST(allocSize);
TEST(heapInit);
TEST(stackInit);

TEST_SUITE(alloc) {
    TEST_ADD(heapAlloc),
    TEST_ADD(allocSize),
    TEST_ADD(heapInit),
    TEST_ADD(stackInit),
    TEST_SUITE_CLOSURE
};

/* freeing.c */
TEST(freeingEmpty);
TEST(freeingSingle);
TEST(freeingFull);

TEST_SUITE(freeing) {
    TEST_ADD(freeingEmpty),
    TEST_ADD(freeingSingle),
    TEST_ADD(freeingFull),
    TEST_SUITE_CLOSURE
};

TEST_SUITES {
    TEST_SUITE_ADD(alloc),
    TEST_SUITE_ADD(freeing),
    TEST_SUITES_CLOSURE
};

int main(int argc, char *argv[])
{
    CU_SET_OUT_PREFIX("output/");
    CU_RUN(argc, argv);

    return 0;
}
