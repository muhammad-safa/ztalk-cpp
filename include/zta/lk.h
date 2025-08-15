#ifndef ZTA_LK_H
#define ZTA_LK_H

#include <stdint.h>
#include <cstdlib>

namespace lk {

  struct Z {
    uintptr_t rep;
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

    inline Z wrap(uintptr_t r) { return Z{r}; }
    inline uintptr_t raw(Z v) { return v.rep; }

    inline uintptr_t pack_long(long v) {
      return static_cast<uintptr_t>(v) << long_tag_bits;
    }
    inline long unpack_long(Z v) {
      return static_cast<long>(raw(v)) >> long_tag_bits;
    }

    inline bool has_long_tag(Z v, uintptr_t tag) {
      return (raw(v) & long_tag_mask) == tag;
    }
    inline uintptr_t strip_long_tag(Z v) { return raw(v) & ~long_tag_mask; }

    inline Z wrap_ptr(void *p, uintptr_t tag) {
      return wrap(reinterpret_cast<uintptr_t>(p) | tag);
    }
    template <typename T>
    inline T *ptr(Z v) {
      return reinterpret_cast<T *>(strip_long_tag(v));
    }

    [[noreturn]] inline void type_error(const char *) { std::abort(); }

  } // namespace impl

} // namespace lk

#include "lk_fixnum.h"
#include "lk_pair.h"

#endif

