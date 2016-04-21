#include "cu/cu.h"

/* creation.c */
TEST(allocation);
TEST(initialization);
TEST(purgingEmpty);
TEST(purgingSingle);
TEST(purgingMultiple);
TEST(freeingEmpty);
TEST(freeingSingle);
TEST(freeingMultiple);

/* insertion.c */
TEST(appendingSingle);
TEST(appendingMultiple);
TEST(prependingSingle);
TEST(prependingMultiple);
TEST(insertFirst);
TEST(insertLast);
TEST(insertMiddle);
TEST(removeFirst);
TEST(removeLast);
TEST(removeMiddle);

TEST_SUITE(creation) {
    TEST_ADD(allocation),
    TEST_ADD(initialization),
    TEST_SUITE_CLOSURE
};

TEST_SUITE(destruction) {
    TEST_ADD(purgingEmpty),
    TEST_ADD(purgingSingle),
    TEST_ADD(purgingMultiple),
    TEST_ADD(freeingEmpty),
    TEST_ADD(freeingSingle),
    TEST_ADD(freeingMultiple),
    TEST_SUITE_CLOSURE
};

TEST_SUITE(pending) {
    TEST_ADD(appendingSingle),
    TEST_ADD(appendingMultiple),
    TEST_ADD(prependingSingle),
    TEST_ADD(prependingMultiple),
    TEST_SUITE_CLOSURE
};

TEST_SUITE(insertion) {
    TEST_ADD(insertFirst),
    TEST_ADD(insertLast),
    TEST_ADD(insertMiddle),
    TEST_ADD(removeFirst),
    TEST_ADD(removeLast),
    TEST_ADD(removeMiddle),
    TEST_SUITE_CLOSURE
};

/* test suites */
TEST_SUITES {
    TEST_SUITE_ADD(creation),
    TEST_SUITE_ADD(destruction),
    TEST_SUITE_ADD(pending),
    TEST_SUITE_ADD(insertion),
    TEST_SUITES_CLOSURE
};
int main(int argc, char *argv[])
{
    CU_SET_NAME("slist");
    CU_SET_OUT_PREFIX("output/");
    CU_RUN(argc, argv);

    return 0;
}
