#ifndef ZTALK_H
#define ZTALK_H

namespace lk {

  struct Z {
    uintptr_t rep;
  };

  namespace impl {
    constexpr int long_tag_bits = 4;
    constexpr long_tag_mask = (1UL << long_tag_bits) - 1;
    inline remove_long_tag(uintptr_t x) { return x & ~long_tag_mask; }
    template<typename T> as_ptr(uintptr_t x) { return reinterpret_cast<T *>(x); }
  }

  // pairs

  namespace impl {
    struct pair {
      Z car;
      Z cdr;
    };

    inline pair &as_pair(Z x) { return *as_ptr<pair>(remove_long_tag(x.rep)); }
    inline pair &expect_pair(Z x) { if (!is_pair(x)) type_error(x, "pair"); return as_pair(x); }
  }

  Z cons();
  inline Z car(Z x) { return expect_pair(x).car; }
  inline Z cdr(Z x) { return expect_pair(x).cdr; }

}

#endif
