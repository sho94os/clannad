#include "test_helper.h"

void test_arithmetic() {
  expect_int(3, 1 + 2);
  expect_int(5, 7 - 2);
  expect_int(6, 2 * 3);
  expect_int(3, 9 / 3);
  expect_int(2, 8 % 3);
}

void test_not() {
  int n;
  if (!1)
    n = 1;
  else
    n = 2;
  expect_int(2, n);

  if (!n)
    n = 3;
  else
    n = 4;
  expect_int(4, n);
}

int factorial(int n) {
  int ret;
  if (n == 1)
    ret = 1;
  else
    ret = n * factorial(n - 1);
  return ret;
}

void test_factorial() {
  expect_int(120, factorial(5));
}

void test_increment() {
  int n = 0;
  expect_int(0, n++);
  expect_int(1, n);

  n = 0;
  expect_int(1, ++n);
  expect_int(1, n);
}

void test_decrement() {
  int n = 0;
  expect_int(0, n--);
  expect_int(-1, n);

  n = 0;
  expect_int(-1, --n);
  expect_int(-1, n);
}

void test_unary_plus() {
  expect_int(3, +1 + +2);
}

void test_unary_minus() {
  expect_int(-3, -1 + -2);
}

void test_arithmetic_compound_assign() {
  int a = 1;
  a += 3;
  expect_int(4, a);
  a -= 2;
  expect_int(2, a);
  a *= 3;
  expect_int(6, a);
  a /= 2;
  expect_int(3, a);
  a %= 2;
  expect_int(1, a);
}

void test_anti_associativity() {
  int n = (2 + 3) * (3 - 1) / 5;
  expect_int(2, n);
}

void test_comma_operator() {
  int n = (2, 3);
  expect_int(3, n);
}

void test_integer_types() {
  unsigned n;
  n = 3;
  expect_int(3, n);

  short unsigned m = 2;
  expect_int(2, m);

  long l = 1;
  expect_int(1, l);
}

int main() {
  test_arithmetic();
  test_not();
  test_factorial();
  test_increment();
  test_decrement();
  test_unary_plus();
  test_unary_minus();
  test_arithmetic_compound_assign();
  test_anti_associativity();
  test_comma_operator();
  test_integer_types();
  return 0;
}
