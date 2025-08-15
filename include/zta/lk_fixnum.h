#ifndef ZTALK_FIXNUM_H
#define ZTALK_FIXNUM_H

#include <climits>

namespace lk {
  namespace impl {
    constexpr long fixnum_min = LONG_MIN >> long_tag_bits;
    constexpr long fixnum_max = LONG_MAX >> long_tag_bits;
    inline bool fits_fixnum(long v) { return v >= fixnum_min && v <= fixnum_max; }
    inline long as_fixnum(Z x) { return static_cast<long>(raw(x)) >> long_tag_bits; }
    inline long expect_fixnum(Z x)
    {
      if (!has_long_tag(x, fixnum_tag)) type_error("fixnum");
      return as_fixnum(x);
    }
  } // namespace impl

  inline Z make_fixnum(long v)
  {
    if (!impl::fits_fixnum(v)) impl::type_error("fixnum overflow");
    return impl::wrap((static_cast<uintptr_t>(v) << impl::long_tag_bits) | impl::fixnum_tag);
  }

  inline long fixnum_value(Z x) { return impl::expect_fixnum(x); }
  inline bool is_fixnum(Z x) { return impl::has_long_tag(x, impl::fixnum_tag); }

} // namespace lk

#endif

