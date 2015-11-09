#include <cstring>
#include <cmath>
#include <cstdio>

const int BASE = 100000;
const int N_DIGIT = 5;
const int N = 32768;
const double PI = acos(-1.0);
struct Complex {
  double real, imag;
};
Complex omega[N >> 1];
Complex a[N];
Complex b[N];

char s[1000003];
int d[N], len;

void bitReverse(Complex a[]) {
  int i, j = 1, k;
  Complex t;
  for (i = 1; i < len; ++ i) {
    if (i < j) {
      t.real = a[j - 1].real;
      t.imag = a[j - 1].imag;
      a[j - 1].real = a[i - 1].real;
      a[j - 1].imag = a[i - 1].imag;
      a[i - 1].real = t.real;
      a[i - 1].imag = t.imag;
    }
    k = len >> 1;
    while (k < j) {
      j -= k;
      k >>= 1;
    }
    j += k;
  }
}

void calOmega() {
  double unit = 2 * PI / len;
  int n = len >> 1;
  for (int i = 0; i < n; ++ i) {
    double t = unit * i;
    omega[i].real = cos( t );
    omega[i].imag = sin( t );
  }
}

void fft(Complex a[], bool inverse = false) {
  bitReverse( a );
  
  int s = len >> 1;
  int m, k, j;
  int up, t, step;
  int i1, i2;
  Complex tmp;

  if ( inverse ) {
    for (j = 0; j < s; ++ j)
      omega[j].imag = - omega[j].imag;
  }
  s = 1;
  for (m = 2; m <= len; m <<= 1) {
    up = m >> 1, t = len >> s;
    for (k = 0; k < len; k += m) {
      step = 0;
      for (j = 0; j < up; ++ j) { // 2^(log2(n) - s) != n - 2^s !!!!!!!
        i1 = k + j;
        i2 = i1 + up;
        tmp.real = omega[step].real * a[i2].real - omega[step].imag * a[i2].imag;
        tmp.imag = omega[step].real * a[i2].imag + omega[step].imag * a[i2].real;
        a[i2].real = a[i1].real - tmp.real;
        a[i2].imag = a[i1].imag - tmp.imag;
        a[i1].real += tmp.real;
        a[i1].imag += tmp.imag;
        step += t;
      }
    }
    ++ s;
  }
  if ( inverse ) {
    double t = 1.0 / len;
    for (j = 0; j < len; ++ j)
      a[j].real *= t;
  }
}

int convert(int d[], char s[]) {
  int sLen = strlen( s );
  int dLen = ((sLen - 1) / N_DIGIT) + 1, i = 0, n;
  char *pRight = s + sLen - 1, *pLeft = pRight - (N_DIGIT - 1);
  memset(d, 0, sizeof(int) * dLen);
  while (i < dLen && pRight >= s) {
    if (pLeft < s) pLeft = s;
    n = 0;
    while (pLeft <= pRight) {
      n = n * 10 + (*pLeft & 15);
      ++ pLeft;
    }
    d[i ++] = n;
    pRight -= N_DIGIT;
    pLeft = pRight - (N_DIGIT - 1);
  }
  return dLen;
}

bool init() {
  int i, j;
  //read a
  if (scanf("%s", s) != 1)
    return false;
  int aLen = convert(d, s); //length of a
  for (i = 0; i < aLen; ++ i) {
    a[i].real = d[i];
    a[i].imag = 0;
  }
  
  //read b
  scanf("%s", s);
  int bLen = convert(d, s);
  for (j = 0; j < bLen; ++ j) {
    b[j].real = d[j];
    b[j].imag = 0;
  }
  len = 1;
  while (len < aLen + bLen) len <<= 1;
  memset(a + i, 0, sizeof(Complex) * (len - i));
  memset(b + j, 0, sizeof(Complex) * (len - j));
  calOmega();
  return true;
}

void mul() {
  for (int i = 0; i < len; ++ i) {
    double real = a[i].real * b[i].real - a[i].imag * b[i].imag;
    double imag = a[i].real * b[i].imag + a[i].imag * b[i].real;
    a[i].real = real;
    a[i].imag = imag;
  }
}

void print() {
  double carry = 0, t;
  //length of b
  //length of product who uses int
  static char format[10];
  int i;
  for (i = 0; i < len; ++ i) {
    t = carry + a[i].real;
    carry = floor((t + 0.5) / BASE);
    d[i] = int(t - carry * BASE + 0.5);
  }
  for (i = len - 1; i > 0 && d[i] == 0; -- i);
  sprintf(format, "%%.%dd", N_DIGIT);
  printf("%d", d[i]);
  for (-- i; i >= 0; -- i)
    printf(format, d[i]);
  printf("\n");
}

int main() {
  while ( init() ) {
    fft( a );
    fft( b );
    mul();
    fft(a, true);
    print();
  }
  return 0;
}