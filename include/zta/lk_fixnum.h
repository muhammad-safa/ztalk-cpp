#ifndef ZTA_LK_FIXNUM_H
#define ZTA_LK_FIXNUM_H

namespace lk {

  inline Z make_fixnum(long v) {
    return impl::wrap(impl::pack_long(v) | impl::fixnum_tag);
  }

  inline long as_fixnum(Z x) {
    return impl::unpack_long(x);
  }

  inline bool is_fixnum(Z x) {
    return impl::has_long_tag(x, impl::fixnum_tag);
  }

} // namespace lk

#endif

