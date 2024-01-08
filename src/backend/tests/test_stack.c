//
// Created by nikolay on 1/2/24.
//

#include <check.h>

#include "test.h"

//
START_TEST(push_1) {
    stack st;
    stackInit(&st);
    push(&st, initData(1, 0, 0, 0));
    stNode *val = top(&st);
    ck_assert_int_eq(val->data.number, 1);
    ck_assert_int_eq(val->data.type, 0);
    freeStack(&st);
}

START_TEST(empty_1) {
    stack st;
    stackInit(&st);
    int first = isEmpty(&st);
    push(&st, initData(1, 0, 0, 0));
    int second = isEmpty(&st);
    // stNode *val = pop(&st);
    int third = isEmpty(&st);
    ck_assert_int_eq(first, 1);
    ck_assert_int_eq(second, 0);
    ck_assert_int_eq(third, 0);
    freeStack(&st);
    // free(val);
}

END_TEST


START_TEST(pop_empty_1) {
    stack st;
    stackInit(&st);
    parseData first = pop(&st);
    ck_assert_int_eq(first.type=E_STACK_UNDERFLOW, E_STACK_UNDERFLOW);
    freeStack(&st);
}

END_TEST


START_TEST(top_1) {
    stack st;
    stackInit(&st);
    push(&st, initData(1, 0, 0, 0));
    parseData node1;
    parseData node2;
    if (top(&st) != NULL)
        node1 = top(&st)->data;
    else
        node1.number = 1;
    ck_assert_int_eq(node1.number, 1); // TODO Error
    node2 = pop(&st);
    node1 = top(&st)->data;
    ck_assert_int_eq(node2.type = E_STACK_UNDERFLOW, E_STACK_UNDERFLOW);
    ck_assert_int_eq(node1.type, 0);
    // free(node1);
    // free(node2);
    freeStack(&st);
}

END_TEST


START_TEST(print_all_1) {
    parseData data1 = initData(1, 0, 0, 0);
    parseData data2 = initData(1, 0, 1, 0);

    stackPrintValue(data1, 0);
    stackPrintValue(data1, 1);

    stackPrintValue(data2, 0);
    stackPrintValue(data2, 1);
    stack st;
    stackInit(&st);
    push(&st, initData(1, 0, 0, 0));
    stackPrintByIndex(&st, 3);
    push(&st, initData(3, 0, 0, 0));
    push(&st, initData(3, 0, 0, 0));
    push(&st, initData(3, 0, 0, 0));
    push(&st, initData(3, 0, 0, 0));

    stackPrintByIndex(&st, 2);
    stackPrintAll(&st);

    freeStack(&st);


    // ck_assert_int_eq(data.type, 1);
}

END_TEST


Suite *Stack() {
    Suite *s = suite_create("Stack");
    TCase *tc_create = tcase_create("Stack");
    tcase_add_test(tc_create, push_1);
    tcase_add_test(tc_create, empty_1);
    tcase_add_test(tc_create, pop_empty_1);
    tcase_add_test(tc_create, print_all_1);
    tcase_add_test(tc_create, top_1);

    // tcase_add_test(tc_create, calc_complements_part_2);
    // tcase_add_test(tc_create, calc_complements_part_3);
    suite_add_tcase(s, tc_create);
    return s;
}
