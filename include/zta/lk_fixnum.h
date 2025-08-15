#ifndef ZTALK_FIXNUM_H
#define ZTALK_FIXNUM_H

#include <climits>

namespace lk
{
  inline Z make_fixnum(long v)
  {
    constexpr long min = LONG_MIN >> impl::long_tag_bits;
    constexpr long max = LONG_MAX >> impl::long_tag_bits;
    if (v < min || v > max)
      return make_bignum(v);
    return impl::wrap((static_cast<uintptr_t>(v) << impl::long_tag_bits) | impl::fixnum_tag);
  }

  inline long fixnum_value(Z x) { return static_cast<long>(impl::raw(x)) >> impl::long_tag_bits; }

  inline bool is_fixnum(Z x) { return impl::has_long_tag(x, impl::fixnum_tag); }

} // namespace lk

#endif

