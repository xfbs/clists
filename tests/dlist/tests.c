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

/* inserting.c */
TEST(insertEmpty);
TEST(insertBeginning);
TEST(insertBack);
TEST(insertMiddle);
TEST(insertAll);

TEST_SUITE(inserting) {
    TEST_ADD(insertEmpty),
    TEST_ADD(insertBeginning),
    TEST_ADD(insertBack),
    TEST_ADD(insertMiddle),
    TEST_ADD(insertAll),
    TEST_SUITE_CLOSURE
};

/* removing.c */
TEST(removeEmpty);
TEST(removeInvalid);
TEST(removeSingle);
TEST(removeAll);

TEST_SUITE(removing) {
    TEST_ADD(removeEmpty),
    TEST_ADD(removeInvalid),
    TEST_ADD(removeSingle),
    TEST_ADD(removeAll),
    TEST_SUITE_CLOSURE
};

/* getting.c */
TEST(gettingEmpty);
TEST(gettingSingle);
TEST(gettingFull);

TEST_SUITE(getting) {
    TEST_ADD(gettingEmpty),
    TEST_ADD(gettingSingle),
    TEST_ADD(gettingFull),
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

/* comparing.c */
TEST(comparingEmpty);
TEST(comparingSingle);
TEST(comparingFull);

TEST_SUITE(comparing) {
    TEST_ADD(comparingEmpty),
    TEST_ADD(comparingSingle),
    TEST_ADD(comparingFull),
    TEST_SUITE_CLOSURE
};

/* foreach.c */
TEST(foreachEmpty);
TEST(foreachSingle);
TEST(foreachFull);
TEST(foreachBackEmpty);
TEST(foreachBackSingle);
TEST(foreachBackFull);

TEST_SUITE(foreach) {
    TEST_ADD(foreachEmpty),
    TEST_ADD(foreachSingle),
    TEST_ADD(foreachFull),
    TEST_ADD(foreachBackEmpty),
    TEST_ADD(foreachBackSingle),
    TEST_ADD(foreachBackFull),
    TEST_SUITE_CLOSURE
};

TEST_SUITES {
    TEST_SUITE_ADD(alloc),
    TEST_SUITE_ADD(freeing),
    TEST_SUITE_ADD(purging),
    TEST_SUITE_ADD(appending),
    TEST_SUITE_ADD(prepending),
    TEST_SUITE_ADD(inserting),
    TEST_SUITE_ADD(removing),
    TEST_SUITE_ADD(getting),
    TEST_SUITE_ADD(setting),
    TEST_SUITE_ADD(popping),
    TEST_SUITE_ADD(comparing),
    TEST_SUITE_ADD(foreach),
    TEST_SUITES_CLOSURE
};

int main(int argc, char *argv[])
{
    CU_SET_NAME("dlist");
    CU_SET_OUT_PREFIX("output/");
    CU_RUN(argc, argv);

    return 0;
}
