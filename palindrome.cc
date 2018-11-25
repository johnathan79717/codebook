char t[400004];
char s[800008];
int z[800008];
 
void longest_palindromic_substring()
{
    // t穿插特殊字元，存放到s。
    int n = strlen(t);
    int N = n * 2 + 1;
    memset(s, '.', N);
    for (int i=0; i<n; ++i) s[i*2+1] = t[i];
    s[N] = 0;
 
    z[0] = 1;   // 無須使用，無須計算。
 
    int L = 0, R = 0;
    for (int i=1; i<N; ++i) // 從z[1]開始
    {
        z[i] = (R > i) ? min(z[2*L-i], R-i) : 1;
        while (i-z[i] >= 0 && i+z[i] < N &&
               s[i-z[i]] == s[i+z[i]]) z[i]++;
        if (i+z[i] > R) L = i, R = i+z[i];
    }

    // l[i] = z[i] - (i % 2 != z[i] % 2);
} 

