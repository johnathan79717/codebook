// z[i] is the length of the longest substring starting from s[i] which is also a prefix of s.
void z_algorithm(char *s, int n, int *z) {
    z[0] = n;
    // R is the max index where s[L..R] (inclusive) is a prefix of s.
    int L = 0, R = 0;
    for (int i = 1; i < n; i++) {
        if (i > R) {
            L = R = i;
        } else {
            // s[L..R] = s[0..R-L], so s[i..R] == s[i-L]
            int k = i-L;
            if (z[k] < R-i+1) {
                z[i] = z[k];
                continue;
            } else {
                L = i;
            }
        }
        while (R < n && s[R-L] == s[R]) R++;
        z[i] = R-L; R--;
    }
}
