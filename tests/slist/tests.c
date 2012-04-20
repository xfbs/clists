#include "cu/cu.h"

TEST(allocation);
TEST(initialization);
TEST(manualAllocation);

TEST_SUITE(alloc) {
    TEST_ADD(allocation),
    TEST_ADD(initialization),
    TEST_ADD(manualAllocation),
    TEST_SUITE_CLOSURE
};

TEST(freeingEmpty);
TEST(freeingFull);
TEST(purgingEmpty);
TEST(purgingFull);

TEST_SUITE(freeing) {
    TEST_ADD(freeingEmpty),
    TEST_ADD(freeingFull),
    TEST_ADD(purgingEmpty),
    TEST_ADD(purgingFull),
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
