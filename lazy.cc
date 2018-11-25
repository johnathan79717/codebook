#include <vector>
using namespace std;

#define chl(k) (k*2+1)
#define chr(k) (k*2+2)

template<class Data, class Lazy>
struct SegmentTree {
  // static Data identity;
  int n;
  int size;
  vector<Data> dat;
  vector<Lazy> lazy;

  int real_size;
  SegmentTree(int n_) {
    real_size = n_;
    n = 1;
    size = n_;
    while(n < n_) n *= 2;
    dat = vector<Data>(2*n-1);
    lazy = vector<Lazy>(2*n-1);
    init(0, 0, n);
  }

  void init(int k, int l, int r) {
    if(r - l == 1) {
      if (l < real_size) { 
        // TODO set dat[k] of leaf at position l
      }
    } else {
      // non-leaf
      int m = (l+r)/2;
      init(chl(k), l, m);
      init(chr(k), m, r);
      dat[k] = combine(dat[chl(k)], dat[chr(k)]);
    }
  }

  void update(int a, int z) {
    update(a, a+1, 0, 0, n, z);
  }
  void update(int a, int b, const Lazy &d) {
    update(a, b+1, 0, 0, n, d);
  }

  void propagate(int k, int l, int r) {
    // TODO update dat[k] according to lazy value d
    if (chr(k) < lazy.size()) {
      lazy[chl(k)] += lazy[k];
      lazy[chr(k)] += lazy[k];
    }
    lazy[k] = Lazy();
  }

  void update(int a, int b, int k, int l, int r, const Lazy &d) {
    // we have to make sure dat[k] is the right value after update
    propagate(k, l, r);
    if (r <= a || b <= l) return;
    if (a <= l && r <= b) {
      lazy[k] = d;
      propagate(k, l, r);
    } else {
      int m = (l+r)/2;
      update(a, b, chl(k), l, m, d);
      update(a, b, chr(k), m, r, d);
      dat[k] = combine(dat[chl(k)], dat[chr(k)]);
    }
  }

  Data query(int a, int b) {
    return query(a, b+1, 0, 0, n);
  }

  Data query(int a, int b, int k, int l, int r) {
    // if [a, b) and [l, r) are disjoint
    if(r <= a || b <= l) return identity;
    propagate(k, l, r);
    // if [l, r) contains [a, b)
    if(a <= l && r <= b) {
      return dat[k];
    } else {
      Data vl = query(a, b, chl(k), l, (l + r) / 2);
      Data vr = query(a, b, chr(k), (l + r) / 2, r);
      return combine(vl, vr);
    }
  }

  Data combine(Data vl, Data vr) {
    // TODO
  }
};
