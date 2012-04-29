#include "cu/cu.h"

/* alloc.c */
TEST(allocation);
TEST(initialization);
TEST(manualAllocation);

TEST_SUITE(alloc) {
    TEST_ADD(allocation),
    TEST_ADD(initialization),
    TEST_ADD(manualAllocation),
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

/* insertion.c */
TEST(insertEmpty);
TEST(insertBeginning);
TEST(insertBack);
TEST(insertMiddle);
TEST(insertInvalid);
TEST(insertAll);

TEST_SUITE(insertion) {
    TEST_ADD(insertEmpty),
    TEST_ADD(insertBeginning),
    TEST_ADD(insertBack),
    TEST_ADD(insertMiddle),
    TEST_ADD(insertInvalid),
    TEST_ADD(insertAll),
    TEST_SUITE_CLOSURE
};

/* removing.c */
TEST(removeEmpty);
TEST(removeBeginning);
TEST(removeBack);
TEST(removeMiddle);
TEST(removeInvalid);
TEST(removeAll);

TEST_SUITE(removing) {
    TEST_ADD(removeEmpty),
    TEST_ADD(removeBeginning),
    TEST_ADD(removeBack),
    TEST_ADD(removeBeginning),
    TEST_ADD(removeInvalid),
    TEST_ADD(removeAll),
    TEST_SUITE_CLOSURE
};

/* setting.c */
TEST(settingEmpty);
TEST(settingInvalid);
TEST(settingAll);

TEST_SUITE(setting) {
    TEST_ADD(settingEmpty),
    TEST_ADD(settingInvalid),
    TEST_ADD(settingAll),
    TEST_SUITE_CLOSURE
};

TEST(gettingEmpty);
TEST(gettingSingle);
TEST(gettingFull);

TEST_SUITE(getting) {
    TEST_ADD(gettingEmpty),
    TEST_ADD(gettingSingle),
    TEST_ADD(gettingFull),
    TEST_SUITE_CLOSURE
};

/* popping.c */
TEST(poppingEmpty);
TEST(poppingSingle);
TEST(poppingFull);

TEST_SUITE(popping) {
    TEST_ADD(poppingEmpty),
    TEST_ADD(poppingSingle),
    TEST_ADD(poppingFull),
    TEST_SUITE_CLOSURE
};

TEST_SUITES {
    TEST_SUITE_ADD(alloc),
    TEST_SUITE_ADD(freeing),
    TEST_SUITE_ADD(purging),
    TEST_SUITE_ADD(appending),
    TEST_SUITE_ADD(prepending),
    TEST_SUITE_ADD(insertion),
    TEST_SUITE_ADD(removing),
    TEST_SUITE_ADD(setting),
    TEST_SUITE_ADD(getting),
    TEST_SUITE_ADD(popping),
    TEST_SUITES_CLOSURE
};

int main(int argc, char *argv[])
{
    CU_SET_OUT_PREFIX("output/");
    CU_RUN(argc, argv);

    return 0;
}
