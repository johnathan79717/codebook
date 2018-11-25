#include <vector>
#include <complex>

using namespace std;
typedef complex<double> cd;
typedef vector<cd> vcd;

vcd fft(const vcd &as) {
  int n = as.size();
  int k = 0;
  while ((1 << k) < n) k++;
  n = (1 << k);
  vector<int> rev(n);
  rev[0] = 0;
  int high1 = -1;
  for (int i = 1; i < n; i++) {
    if ((i & (i - 1)) == 0)
      high1++;
    rev[i] = rev[i ^ (1 << high1)];
    rev[i] |= (1 << (k - high1 - 1));
  }

  vcd roots(n);
  for (int i = 0; i < n; i++) {
    double alpha = 2 * M_PI * i / n;
    roots[i] = cd(cos(alpha), sin(alpha));
  }

  vcd cur(n);
  for (int i = 0; i < n; i++) {
    if (rev[i] < (int)as.size())
      cur[i] = as[rev[i]];
  }

  for (int len = 1; len < n; len *= 2) {
    int rstep = roots.size() / (len * 2);
    for (int p = 0; p < n; p += len * 2) {
      for (int i = 0; i < len; i++) {
        cd val = roots[i * rstep] * cur[p + len + i];
        auto c = cur[p + i];
        cur[p + i] = c + val;
        cur[p + len + i] = c - val;
      }
    }
  }
  return cur;
}

vcd mul(const vcd& a1, const vcd& a2) {
    vcd f1 = fft(a1), f2 = fft(a2);
    assert(f1.size() == f2.size());
    int L = f1.size();
    vcd p(L);
    for (int i = 0; i < L; i++) {
        p[i] = conj(f1[i] * f2[i]) / cd(L);
    }
    return fft(p);
}
