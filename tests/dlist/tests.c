#include "cu/cu.h"

/* alloc.c */
TEST(allocNew);
TEST(heapInit);
TEST(stackInit);

TEST_SUITE(alloc) {
    TEST_ADD(allocNew),
    TEST_ADD(heapInit),
    TEST_ADD(stackInit),
    TEST_SUITE_CLOSURE
};

TEST_SUITES {
    TEST_SUITE_ADD(alloc),
    TEST_SUITES_CLOSURE
};

int main(int argc, char *argv[])
{
    CU_SET_OUT_PREFIX("output/");
    CU_RUN(argc, argv);

    return 0;
}
