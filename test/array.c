#include "test_helper.h"

void test_array_assign() {
  int a[2];
  a[0] = 2;
  a[1] = 3;
  expect_int(5, a[0] + a[1]);
}

int main() {
  test_array_assign();
  return 0;
}
