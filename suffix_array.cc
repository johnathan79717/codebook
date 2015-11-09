#define MAX_N 1500000
int sa[MAX_N];
int c[MAX_N];
int temp[2][MAX_N];

void suffix_array(char *t, int N)
{
    int A = 128;            // 計數排序法數值範圍
    int* rank = temp[0];    // 各個後綴對應的名次
    int* sa2 = temp[1];     // 各個名次對應的後綴後半段
 
    // 各個後綴第一個字元，實施計數排序法。
    // 然後累計次數，直接得到名次。
    // 從索引值最高的後綴開始處理，得到各個後綴對應的名次。
    // （偷懶取巧：直接把ASCII數值當作是名次。）
    for (int i=0; i<A; ++i) c[i] = 0;
    for (int i=0; i<N; ++i) c[rank[i] = t[i]]++;
    for (int i=1; i<A; ++i) c[i] += c[i-1];
    for (int i=N-1; i>=0; --i)
        sa[--c[t[i]]] = i;
 
    // 鍵值長度逐步倍增
    for (int n=1; n<N; n*=2)
    {
        // sa 是各個名次對應的後綴前半段
        // sa2是各個名次對應的後綴後半段
        // rank是各個後綴前半段對應的名次
 
        // sa與rank在上一回合就計算好了，現在要計算sa2。
        // 最後n個後綴的後半段，肯定都是空字串，名次最高。
        // 各個空字串依照索引值由小到大進行排名。
        int r = 0;  // 名次
        for (int i=N-n; i<N; ++i)
            sa2[r++] = i;
 
        // 其它的後綴的後半段，運用sa求得。
        for (int i=0; i<N; ++i)
            // 位置大於等於k，實際上才有前半段。
            if (sa[i] >= n)
                sa2[r++] = sa[i] - n;
 
        // 使用各個後綴的名次，實施計數排序法。
        // 從名次最高的後綴後半段開始處理，得到正確名次。
        for (int i=0; i<A; ++i) c[i] = 0;
        for (int i=0; i<N; ++i) c[rank[i]]++;
        for (int i=1; i<A; ++i) c[i] += c[i-1];
        for (int i=N-1; i>=0; --i)
            sa[--c[rank[sa2[i]]]] = sa2[i];
 
        // 暫且以sa2來儲存本回合的rank，
        // 然後計算下一回合的rank。
        int*& new_rank = sa2;
        new_rank[sa[0]] = r = 0;
        for (int i=1; i<N; ++i)
        {
            // 相異者、排在相異名次，相同者、排在相同名次。
            // （偷懶取巧：因為最後n個後綴，
            // 上個回合就已經排序完畢，
            // 這些後綴長度不等、名次一定都相異，
            // 所以不會遇到sa[i-1]+n和sa[i]+n溢位。）
            if (!(rank[sa[i-1]] == rank[sa[i]] &&
                sa[i-1]+n < N &&
                rank[sa[i-1]+n] == rank[sa[i]+n]))
                r++;
            new_rank[sa[i]] = r;
        }
        swap(rank, sa2);
 
        // 如果名次皆相異，表示排序完畢，可以提早結束。
        if (r == N-1) break;
        // 修正一下計數排序法數值範圍
        A = r + 1;
    }
}

int lcpa[MAX_N];
 
void lcp_array(char *s, int N)
{
    // 也就是各個後綴在sa當中的索引值
    // 也就是sa的反函數
    int *rank = temp[0];
    for (int i=0; i<N; ++i)
        rank[sa[i]] = i;
 
    for (int i=0, lcp=0; i<N; i++)
        if (rank[i] == 0)
            lcpa[0] = 0;
        else
        {
            int j = sa[rank[i]-1];
            if (lcp > 0) lcp--;
            while (s[i+lcp] == s[j+lcp]) {
                // assert(max(i, j) + lcp < N);
                lcp++;
            }
            lcpa[rank[i]] = lcp;
        }
}