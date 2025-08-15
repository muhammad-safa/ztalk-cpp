#ifndef ZTALK_PAIR_H
#define ZTALK_PAIR_H

namespace lk {
  inline bool is_pair(Z x) { return impl::has_long_tag(x, impl::pair_tag); }

  namespace impl {
    struct pair {
      Z car;
      Z cdr;
    };

    inline pair *as_pair(Z x) { return ptr<pair>(x); }
    inline pair *expect_pair(Z x)
    {
      if (!has_long_tag(x, pair_tag)) type_error("pair");
      return as_pair(x);
    }
  } // namespace impl

  Z cons(Z a, Z d);

  inline Z car(Z x) { return impl::expect_pair(x)->car; }
  inline Z cdr(Z x) { return impl::expect_pair(x)->cdr; }

} // namespace lk

#endif

