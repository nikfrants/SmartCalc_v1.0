//
// Created by nikolay on 1/2/24.
//

#ifndef TESTS_H
#define TESTS_H

#include <check.h>
#include <stdio.h>

#include "../stack.h"
#
Suite *Stack();
Suite *Parser();
Suite *Check_parsed();
Suite *Calc_polish_n();

#endif
