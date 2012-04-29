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

/* freeing.c */
TEST(freeingEmpty);
TEST(freeingSingle);
TEST(freeingFull);
TEST(purgingEmpty);
TEST(purgingSingle);
TEST(purgingFull);

TEST_SUITE(freeing) {
    TEST_ADD(freeingEmpty),
    TEST_ADD(freeingSingle),
    TEST_ADD(freeingFull),
    TEST_SUITE_CLOSURE
};

/* purging.c */
TEST(purgingEmpty);
TEST(purgingSingle);
TEST(purgingFull);

TEST_SUITE(purging) {
    TEST_ADD(purgingEmpty),
    TEST_ADD(purgingSingle),
    TEST_ADD(purgingFull),
    TEST_SUITE_CLOSURE
};

/* appending.c */
TEST(appendEmpty);
TEST(appendFull);

TEST_SUITE(appending) {
    TEST_ADD(appendEmpty),
    TEST_ADD(appendFull),
    TEST_SUITE_CLOSURE
};

/* prepending.c */
TEST(prependEmpty);
TEST(prependFull);

TEST_SUITE(prepending) {
    TEST_ADD(prependEmpty),
    TEST_ADD(prependFull),
    TEST_SUITE_CLOSURE
};

TEST_SUITES {
    TEST_SUITE_ADD(alloc),
    TEST_SUITE_ADD(freeing),
    TEST_SUITE_ADD(purging),
    TEST_SUITE_ADD(appending),
    TEST_SUITE_ADD(prepending),
    TEST_SUITES_CLOSURE
};

int main(int argc, char *argv[])
{
    CU_SET_OUT_PREFIX("output/");
    CU_RUN(argc, argv);

    return 0;
}
