#ifndef ZTALK_PAIR_H
#define ZTALK_PAIR_H

namespace lk
{
  inline bool is_pair(Z x) { return impl::has_long_tag(x, impl::pair_tag); }

  namespace impl
  {
    struct pair
    {
      Z car;
      Z cdr;
    };

    inline pair *as_pair(Z x) { return ptr<pair>(x); }
  } // namespace impl

  Z cons(Z a, Z d);

  inline Z car(Z x)
  {
    if (!is_pair(x))
      impl::type_error("pair");
    return impl::as_pair(x)->car;
  }

  inline Z cdr(Z x)
  {
    if (!is_pair(x))
      impl::type_error("pair");
    return impl::as_pair(x)->cdr;
  }

} // namespace lk

#endif

