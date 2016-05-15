#include "cu/cu.h"

/* slist_size() */
TEST(size_works_with_slist_new);
TEST(size_works_with_slist_init);
TEST(size_works_manually);

/* slist_length() */
TEST(length_works_with_basic_ops);
TEST(length_works_manually);

/* slist_first() */
TEST(first_returns_null_on_empty_list);
TEST(first_returns_first_element);
TEST(first_returns_correct_pointer);

/* slist_last() */
TEST(last_returns_null_on_empty_list);
TEST(last_returns_last_element);
TEST(last_returns_correct_pointer);

/* slist_new() */
TEST(new_works_with_all_sizes);
TEST(new_sets_all_pointers_to_null);

/* slist_init() */
TEST(init_works_with_all_sizes);
TEST(init_sets_all_pointers_to_null);

/* slist_purge() */
TEST(purge_does_nothing_on_empty_list);
TEST(purge_removes_all_elements_of_list);

/* slist_free() */

/* slist_append() */
TEST(append_sets_both_head_and_tail);
TEST(append_sets_data_correctly);
TEST(append_sets_length_correctly);

/* slist_prepend() */
TEST(prepend_sets_both_head_and_tail);
TEST(prepend_sets_data_correctly);
TEST(prepend_sets_length_correctly);

/* slist_insert() */

/* slist_remove() */

/* slist_pop() */

/* slist_swap() */

/* slist_set() */

/* slist_get() */

TEST_SUITE(basic_data_access) {
    TEST_ADD(size_works_with_slist_new),
    TEST_ADD(size_works_with_slist_init),
    TEST_ADD(size_works_manually),
    TEST_ADD(length_works_with_basic_ops),
    TEST_ADD(length_works_manually),
    TEST_ADD(first_returns_null_on_empty_list),
    TEST_ADD(first_returns_correct_pointer),
    TEST_ADD(first_returns_first_element),
    TEST_ADD(last_returns_null_on_empty_list),
    TEST_ADD(last_returns_last_element),
    TEST_ADD(last_returns_correct_pointer),
    TEST_SUITE_CLOSURE
};

TEST_SUITE(creation_destruction) {
    TEST_ADD(new_works_with_all_sizes),
    TEST_ADD(new_sets_all_pointers_to_null),
    TEST_ADD(init_works_with_all_sizes),
    TEST_ADD(init_sets_all_pointers_to_null),
    TEST_ADD(purge_does_nothing_on_empty_list),
    TEST_ADD(purge_removes_all_elements_of_list),
    TEST_SUITE_CLOSURE
};

TEST_SUITE(insertion) {
    TEST_ADD(append_sets_both_head_and_tail),
    TEST_ADD(append_sets_data_correctly),
    TEST_ADD(append_sets_length_correctly),
    TEST_ADD(prepend_sets_both_head_and_tail),
    TEST_ADD(prepend_sets_data_correctly),
    TEST_ADD(prepend_sets_length_correctly),
    TEST_SUITE_CLOSURE
};

/* test suites */
TEST_SUITES {
    TEST_SUITE_ADD(basic_data_access),
    TEST_SUITE_ADD(creation_destruction),
    TEST_SUITE_ADD(insertion),
    TEST_SUITES_CLOSURE
};
int main(int argc, char *argv[])
{
    CU_SET_NAME("slist");
    CU_SET_OUT_PREFIX("output/");
    CU_RUN(argc, argv);

    // set return value according to whether
    // there were any failures
    return (cu_fail_test_suites > 0) ? -1 : 0;
}
