#include "zta/lk.h"

int main() {
  using namespace lk;
  Z a = make_fixnum(1);
  Z b = make_fixnum(2);
  Z p = cons(a, b);
  return as_fixnum(car(p)) + as_fixnum(cdr(p));
}

