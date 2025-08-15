#include "zta/lk.h"
#include <stdio.h>

int main()
{
  using namespace lk;
  Z a = 1;
  Z b = 2;
  Z p = cons(a, b);
  printf("%ld\n", fixnum_value(car(p)) + fixnum_value(cdr(p)));
  return 0;
}

