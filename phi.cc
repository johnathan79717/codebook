int phi(int n) {
  int ans = n;
  for(int p = 2; p * p <= n; p++) {
    if(n % p == 0) {
      ans -= ans / p;
      do n /= p; while(n % p == 0);
    }
  }
  if(n > 1)
    ans -= ans / n;
  return ans;
}