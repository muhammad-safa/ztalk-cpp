#ifndef ZTALK_H
#define ZTALK_H

#include <stdint.h>
#include <cstdlib>
#include <cstdio>

namespace lk {
  struct Z {
    uintptr_t rep;

    Z() = default;
    Z(long);
    Z(int v) : Z(static_cast<long>(v)) {}
    Z(const char *);
  };

  namespace impl {
    constexpr int long_tag_bits = 4;
    constexpr uintptr_t long_tag_mask = (uintptr_t{1} << long_tag_bits) - 1;
    constexpr int short_tag_bits = 3;
    constexpr uintptr_t short_tag_mask = (uintptr_t{1} << short_tag_bits) - 1;

    constexpr uintptr_t pair_tag = 0;
    constexpr uintptr_t fixnum_tag = 1;
    constexpr uintptr_t symbol_tag = 2;
    constexpr uintptr_t string_tag = 3;
    constexpr uintptr_t bytevector_tag = 4;
    constexpr uintptr_t vector_tag = 5;
    constexpr uintptr_t hashtable_tag = 6;

    inline Z wrap(uintptr_t r) { Z v; v.rep = r; return v; }
    inline uintptr_t raw(Z v) { return v.rep; }
    inline bool has_long_tag(Z v, uintptr_t tag) { return (raw(v) & long_tag_mask) == tag; }
    inline uintptr_t strip_long_tag(Z v) { return raw(v) & ~long_tag_mask; }
    inline Z wrap_ptr(void *p, uintptr_t tag) { return wrap(reinterpret_cast<uintptr_t>(p) | tag); }
    template <typename T> inline T *ptr(Z v) { return reinterpret_cast<T *>(strip_long_tag(v)); }

    [[noreturn]] inline void type_error(const char *) { std::abort(); }
    [[noreturn]] inline void not_implemented(const char *msg) { std::fputs(msg, stderr); std::abort(); }

  } // namespace impl

  Z make_bignum(long);
  Z make_string(const char *);

} // namespace lk

#include "lk_fixnum.h"
#include "lk_pair.h"

namespace lk {
  inline Z make_bignum(long) { impl::not_implemented("make_bignum"); }
  inline Z make_string(const char *) { impl::not_implemented("make_string"); }
  inline Z::Z(long v)
  {
    *this = impl::fits_fixnum(v) ? make_fixnum(v) : make_bignum(v);
  }
  inline Z::Z(const char *s) { *this = make_string(s); }
}

#endif

