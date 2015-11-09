// Building the partial match table
// table[0] = -1, table[i+1] is the length of the longest
// proper suffix of W[0..i] which is a prefix of W
// time complexity O(|W|)
void kmp_table(char *W, int *table) {
  int pos = 2, cnd = 0;
  table[0] = -1, table[1] = 0;
  int N = strlen(W);
  while(pos <= N) {
    if(W[pos-1] == W[cnd]) {
      cnd++;
      table[pos] = cnd;
      pos++;
    } else if(cnd > 0) {
      cnd = table[cnd];
    } else {
      table[pos] = 0;
      pos++;
    }
  }
}

// search W in S, time complexity O(|S|)
int kmp_search(char *S, char *W, int *table) {
  int m = 0, i = 0;
  int ls = strlen(S), lw = strlen(W);
  while(m + i < ls) {
    if(i < lw && W[i] == S[m+i]) {
      if(i == lw-1) {
        // W == S[m..m+lw-1]
        // doesn't have to return can keep going if needed
        return m;
      }
      i++;
    } else {
      if(table[i] > -1) {
        i = table[i];
        m = m + i - table[i];
      } else {
        i = 0;
        m++;
      }
    }
  }
  return ls;
}