#define MAX_N 1500000
int sa[MAX_N];
int c[MAX_N];
int temp[2][MAX_N];

void suffix_array(char *t, int N)
{
    int A = 128;
    int* rank = temp[0];
    int* sa2 = temp[1];
 
    for (int i=0; i<A; ++i) c[i] = 0;
    for (int i=0; i<N; ++i) c[rank[i] = t[i]]++;
    for (int i=1; i<A; ++i) c[i] += c[i-1];
    for (int i=N-1; i>=0; --i)
        sa[--c[t[i]]] = i;
 
    for (int n=1; n<N; n*=2)
    {
        int r = 0;
        for (int i=N-n; i<N; ++i)
            sa2[r++] = i;
 
        for (int i=0; i<N; ++i)
            if (sa[i] >= n)
                sa2[r++] = sa[i] - n;
 
        for (int i=0; i<A; ++i) c[i] = 0;
        for (int i=0; i<N; ++i) c[rank[i]]++;
        for (int i=1; i<A; ++i) c[i] += c[i-1];
        for (int i=N-1; i>=0; --i)
            sa[--c[rank[sa2[i]]]] = sa2[i];
 
        int*& new_rank = sa2;
        new_rank[sa[0]] = r = 0;
        for (int i=1; i<N; ++i)
        {
            if (!(rank[sa[i-1]] == rank[sa[i]] &&
                sa[i-1]+n < N &&
                rank[sa[i-1]+n] == rank[sa[i]+n]))
                r++;
            new_rank[sa[i]] = r;
        }
        swap(rank, sa2);
 
        if (r == N-1) break;
        A = r + 1;
    }
}

int lcpa[MAX_N];
 
void lcp_array(char *s, int N)
{
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
