#include "zta/lk.h"
#include <cstdlib>

namespace lk
{
Z cons(Z a, Z d)
{
  impl::pair *p = static_cast<impl::pair *>(std::malloc(sizeof(impl::pair)));
  if (!p)
    std::abort();
  p->car = a;
  p->cdr = d;
  return impl::wrap_ptr(p, impl::pair_tag);
}

} // namespace lk

