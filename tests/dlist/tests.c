#include "cu/cu.h"

/* dlist_size() */
TEST(size_works_with_dlist_new);
TEST(size_works_with_dlist_init);
TEST(size_works_manually);

/* dlist_length() */
TEST(length_works_with_basic_ops);
TEST(length_works_manually);

/* dlist_first() */
TEST(first_returns_null_on_empty_list);
TEST(first_returns_first_element);
TEST(first_returns_correct_pointer);

/* dlist_last() */
TEST(last_returns_null_on_empty_list);
TEST(last_returns_last_element);
TEST(last_returns_correct_pointer);

/* dlist_new() */
TEST(new_works_with_all_sizes);
TEST(new_sets_all_pointers_to_null);

/* dlist_init() */
TEST(init_works_with_all_sizes);
TEST(init_sets_all_pointers_to_null);

/* dlist_purge() */
TEST(purge_does_nothing_on_empty_list);
TEST(purge_removes_all_elements_of_list);

/* dlist_free() */

/* dlist_append() */
TEST(append_sets_both_head_and_tail);
TEST(append_sets_data_correctly);
TEST(append_sets_length_correctly);

/* dlist_prepend() */
TEST(prepend_sets_both_head_and_tail);
TEST(prepend_sets_data_correctly);
TEST(prepend_sets_length_correctly);

/* dlist_insert() */
TEST(insert_works_without_data);
TEST(insert_returns_null_on_illegal);
TEST(insert_works_with_data);

/* dlist_remove() */
TEST(remove_on_empty_list_does_not_work);
TEST(remove_in_beginning_works);
TEST(remove_at_end_works);
TEST(remove_in_middle_works);

/* dlist_pop() */
TEST(pop_works_on_empty_list);
TEST(pop_works_on_single_list);
TEST(pop_works_on_full_list);

/* dlist_set() */
TEST(set_does_not_work_for_empty_list);
TEST(set_does_not_work_for_illegal_index);
TEST(set_with_null_data_returns_null);
TEST(set_works_with_data);

/* dlist_get() */
TEST(get_does_not_work_for_empty_list);
TEST(get_does_not_work_for_illegal_index);
TEST(get_works_without_data);
TEST(get_works_with_data);

/* dlist_swap() */
TEST(swap_does_not_work_on_empty_list);
TEST(swap_does_not_work_on_nonexisting_indices);
TEST(swap_does_nothing_when_indices_are_equal);
TEST(swap_works_correctly_with_different_indices);

/* dlist_split() */
TEST(split_does_not_work_on_empty_list);
TEST(split_does_not_work_on_illegal_pos);
TEST(split_on_head_works_on_full_list);
TEST(split_on_rest_works_on_full_list);

/* dlist_join() */
TEST(join_does_not_work_on_different_element_sizes);
TEST(join_works_on_empty_lists);
TEST(join_works_on_full_lists);

/* dlist_copy() */
TEST(copy_works_on_empty_list);
TEST(copy_works_on_full_list);

TEST_SUITE(basic_data_access) {
    TEST_ADD(size_works_with_dlist_new),
    TEST_ADD(size_works_with_dlist_init),
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
    TEST_ADD(insert_works_without_data),
    TEST_ADD(insert_returns_null_on_illegal),
    TEST_ADD(insert_works_with_data),
    TEST_SUITE_CLOSURE
};

TEST_SUITE(removal) {
    TEST_ADD(pop_works_on_empty_list),
    TEST_ADD(pop_works_on_single_list),
    TEST_ADD(pop_works_on_full_list),
    TEST_ADD(remove_on_empty_list_does_not_work),
    TEST_ADD(remove_in_beginning_works),
    TEST_ADD(remove_at_end_works),
    TEST_ADD(remove_in_middle_works),
    TEST_SUITE_CLOSURE
};

TEST_SUITE(accessing) {
    TEST_ADD(get_does_not_work_for_empty_list),
    TEST_ADD(get_does_not_work_for_illegal_index),
    TEST_ADD(get_works_without_data),
    TEST_ADD(get_works_with_data),
    TEST_ADD(set_does_not_work_for_empty_list),
    TEST_ADD(set_does_not_work_for_illegal_index),
    TEST_ADD(set_with_null_data_returns_null),
    TEST_ADD(set_works_with_data),
    TEST_SUITE_CLOSURE
};

TEST_SUITE(manipulation) {
/*
    TEST_ADD(swap_does_not_work_on_empty_list),
    TEST_ADD(swap_does_not_work_on_nonexisting_indices),
    TEST_ADD(swap_does_nothing_when_indices_are_equal),
    TEST_ADD(swap_works_correctly_with_different_indices),
*/
    TEST_ADD(split_does_not_work_on_empty_list),
    TEST_ADD(split_does_not_work_on_illegal_pos),
    TEST_ADD(split_on_head_works_on_full_list),
    TEST_ADD(split_on_rest_works_on_full_list),
    TEST_ADD(join_does_not_work_on_different_element_sizes),
    TEST_ADD(join_works_on_empty_lists),
    TEST_ADD(join_works_on_full_lists),
    TEST_ADD(copy_works_on_empty_list),
    TEST_ADD(copy_works_on_full_list),
    TEST_SUITE_CLOSURE
};

/* test suites */
TEST_SUITES {
    TEST_SUITE_ADD(basic_data_access),
    TEST_SUITE_ADD(creation_destruction),
    TEST_SUITE_ADD(insertion),
    TEST_SUITE_ADD(removal),
    TEST_SUITE_ADD(accessing),
    TEST_SUITE_ADD(manipulation),
    TEST_SUITES_CLOSURE
};
int main(int argc, char *argv[])
{
    CU_SET_NAME("dlist");
    CU_SET_OUT_PREFIX("output/");
    CU_RUN(argc, argv);

    // set return value according to whether
    // there were any failures
    return (cu_fail_test_suites > 0) ? -1 : 0;
}
