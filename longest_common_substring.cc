int N;

char s[4001][256];       // 4001個字串，長度皆可達到256-1。
char* sa[4001 * 256];    // suffix array
int c[4001];              // 紀錄目前出現的後綴是位於哪幾個字串。
 
int cmp(const void* a, const void* b)
{
    return strcmp(*(char**)a, *(char**)b);
}
 
// 找出一個後綴所附屬的字串
inline int pos(int n)
{
    return (sa[n] - s[0]) / 256;
}
 
// 求出兩個字串的Longest Common Prefix長度
int lcp(char* s, char* t)
{
    int n = 0;
    while (s[n] && t[n] && s[n] == t[n]) n++;
    return n;
}
 
PII longest_common_substring()
{
    // 建立後綴陣列
    int M = 0;
    for (int i=0; i<N; ++i)
        for (int j=0; s[i][j]; ++j)
            sa[M++] = s[i] + j;
 
    qsort(sa, M, sizeof(char*), cmp);
 
    // 尋找連續後綴
    PII ans = MP(0, 0);
    memset(c, 0, sizeof(c));
    for (int i=0, j=0, n=0; j<M; )
    {
        // 往右移動j，直到涵蓋每一種字串的後綴。
        // 並且隨時紀錄每一種字串的後綴的出現次數。
        while (n < N && j < M) if (!c[pos(j++)]++) n++;
        // 往右移動i，直到無法涵蓋每一種字串的後綴。
        while (n == N) if (!--c[pos(i++)]) n--;
 
        // 計算共同子字串，並且紀錄最長者。
        // ans = max(ans, MP(lcp(sa[i], sa[j-1]), i));
        int l = lcp(sa[i-1], sa[j-1]);
        if (l > ans.X) {
            ans = MP(l, i-1);
        } else if (l == ans.X && strncmp(sa[i-1], sa[ans.Y], l) < 0) {
            ans = MP(l, i-1);
        }
 
    }
 
    return ans;
}