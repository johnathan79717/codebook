int MOD = 1000000007;
struct Z {
  int i;
  Z():i(0) {}
  Z(int i): i(i >= 0 ? i : i + MOD) {}
  Z(long long i): i(i % MOD) {}
  void operator +=(const Z& z) { i += z.i; if(i >= MOD) i -= MOD; }
  void operator -=(const Z& z) { i -= z.i; if(i < 0) i += MOD; }
  void operator *=(const Z& z) { i = (long long) i * z.i % MOD; }
  void operator /=(const Z& z) { (*this) *= z.inverse(); }
  Z operator +(const Z& z) const { Z ret(i); ret += z; return ret; }
  Z operator -(const Z& z) const { Z ret(i); ret -= z; return ret; }
  Z operator *(const Z& z) const { Z ret(i); ret *= z; return ret; }
  Z operator /(const Z& z) const { return (*this) * z.inverse(); }
  // Z operator -() const { return Z(-i); }
  Z inverse() const {
    int a = i, d = MOD, x = 0, s = 1;
    while(a) {
      int q = d / a, r = d % a, t = x - q * s;
      d = a, a = r, x = s, s = t;
    }
    if (d != 1) return -1;
    return x < 0 ? x + MOD : x;
  }
  Z pow(long long b) {
    Z x=1,y=*this;
    while(b > 0){
      if(b%2 == 1)
        x *= y;
      y *= y; // squaring the base
      b /= 2;
    }
    return x;
  }
};

vector<Z> factorial(1, 1), inv_factorial(1, 1);

Z fact(int n) {
  while(int(factorial.size()) <= n)
    factorial.push_back(factorial.back() * SZ(factorial));
  return factorial.at(n);
}

Z inv_fact(int n) {
  int old_size = inv_factorial.size();
  inv_factorial.resize(n+1);
  inv_factorial.at(n) = fact(n).inverse();
  for (int i = n-1; i >= old_size; i--) {
    inv_factorial[i] = inv_factorial.at(i+1) * (i+1);
  }
  return inv_factorial.at(n);
}

Z choose(int n, int k) {
  if(n < k) return 0;
  return fact(n) * (inv_fact(k) * inv_fact(n-k));
}

pair<Z,int> factModExp(int n) {
    if (n == 0) return MP(Z(1), 0);
    int e = n / MOD;
    pair<Z,int> pr = factModExp(e);
    if (e % 2) {
        return MP(Z(0) - pr.F * fact(n % MOD), pr.S + e);
    } else {
        return MP(pr.F * fact(n % MOD), pr.S + e);
    }
}

struct Matrix {
  static int M;

  //Z a[30][30];
  vector<vector<Z> > a;
  Matrix() {
    //MS0(a);
    a = vector<vector<Z> >(M, vector<Z>(M));
  }

  Z* operator[](int i) {
    return a[i];
  }

  Matrix operator* (const Matrix &other) const {
    Matrix ret;
    REP(i, M) REP(j, M) REP(k, M) {
      ret.a[i][j] += a[i][k] * other.a[k][j];
    }
    return ret;
  }

  Matrix pow(LL n) {
    if(n % 2) {
      return *this * pow(n-1);
    } else {
      if(n)
        return (*this * *this).pow(n / 2);
      else {
        Matrix ret;
        REP(i, M) {
          ret.a[i][i] = 1;
        }
        return ret;
      }
    }
  }
};
int Matrix::M;
