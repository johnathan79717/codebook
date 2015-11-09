Z pool[9999999];
int p = 0;

Z *alloc(int n) {
  Z *ans = pool + p;
  p += n;
  return ans;
}

Z* poly_mul(Z *x, Z *y, int n) {
  if(n == 1) {
    // Z* ans = new Z[1];
    Z *ans = alloc(1);
    ans[0] = x[0] * y[0];
    return ans;
  } else {
    // Z *ans = new Z[n*2-1];
    Z *ans = alloc(n*2-1);
    for(int i = 0; i < n*2-1; i++)
      ans[i] = 0;
    int l = (n+1)/2;
    Z *z0 = poly_mul(x, y, l);
    Z *z2 = poly_mul(x+l, y+l, n-l);
    // Z *temp1 = new Z[l];
    // Z *temp2 = new Z[l];
    Z *temp1 = alloc(l), *temp2 = alloc(l);
    for(int i = 0; i < l; i++) {
      temp1[i] = x[i];
      temp2[i] = y[i];
    }
    for(int i = 0; i < n-l; i++) {
      temp1[i] += x[i+l];
      temp2[i] += y[i+l];
    }
    Z *z1 = poly_mul(temp1, temp2, l);
    for(int i = 0; i < l*2-1; i++) {
      z1[i] -= z0[i];
    }
    for(int i = 0; i < (n-l)*2-1; i++) {
      z1[i] -= z2[i];
    }
    for(int i = 0; i < l*2-1; i++) {
      ans[i] += z0[i];
      ans[i+l] += z1[i];
    }
    for(int i = 0; i < (n-l)*2-1; i++) {
      ans[i+l*2] += z2[i];
    }
    // delete[] temp1;
    // delete[] temp2;
    // delete[] z0;
    // delete[] z1;
    // delete[] z2;
    p -= l + l + (2*l-1) + (2*l-1) + (2*(n-l)-1);
    return ans;
  }
}