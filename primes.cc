#define MAX_P 15000000
vector<int> primes;
bool p[MAX_P];

void Eratosthenes() {
  memset(p, true, sizeof p);
  for(int i = 2; i < MAX_P; i++)
    if(p[i]) {
      primes.push_back(i);
      if((LL)i*i < MAX_P) 
        for(int j = i*i; j < MAX_P; j+=i)
          p[j] = false;
    }
}

bool isprime(LL n) {
  if(n < 2) return false;
  int nn = sqrt(n);
  FOR(p, primes) {
    if(p > nn)
      return true;
    if(n % p == 0)
      return false;
  }
  return true;
}
