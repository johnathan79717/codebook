struct CMP
{
    int *rank, n, N;
    CMP(int *r, int n, int N): rank(r), n(n), N(N) {}
    bool operator()(const int& i, const int& j)
    {
        // 先比前半段，再比後半段。
        if (rank[i] != rank[j])
            return rank[i] < rank[j];
        int a = (i+n<N) ? rank[i+n] : -1;
        int b = (j+n<N) ? rank[j+n] : -1;
        return a < b;
    }
};
     
vector<int> suffix_array(char *t, int N)
{
    // int* rank = temp[0];
    // int* new_rank = temp[1];
    int *rank = new int[N], *new_rank = new int[N];
    vector<int> sa(N);
 
    for (int i=0; i<N; i++)
    {
        // 各個名次對應的後綴
        // 隨便初始化一個順序，稍後會重新排序。
        sa[i] = i;
        // 各個後綴對應的名次
        // 偷懶取巧：直接把ASCII數值當作是名次。
        rank[i] = t[i];
    }
 
    // 鍵值長度逐步倍增
    for (int n=1; n<N; n*=2)
    {
        // 運用上一回合求得的名次，排序所有後綴。
        // 鍵值是每個後綴的前2*n個字元，
        // 先比前半段、再比後半段。
        CMP cmp(rank, n, N);
        sort(sa.begin(), sa.end(), cmp);
        // for(int i = 0; i < sa.size(); i++) printf("%d\n", sa[i]);
        // 重新整理名次。
        // 相異者、排在相異名次，相同者、排在相同名次。
        int r = 0;
        new_rank[sa[0]] = r;
        for (int i=1, r=0; i<N; i++)
        {
            if (cmp(sa[i-1], sa[i])) r++;
            new_rank[sa[i]] = r;
        }
        swap(rank, new_rank);
 
        // 如果名次皆相異，表示排序完畢，可以提早結束。
        if (r == N-1) break;
    }
    delete rank;
    delete new_rank;
    return move(sa);
}

    char s[100005+1];
    int sa[100005];
    int temp[2][100005];
    int N;
     
    struct CMP
    {
        int* rnk, n, N;
        bool operator()(const int& i, const int& j)
        {
            // 先比前半段，再比後半段。
            if (rnk[i] != rnk[j])
                return rnk[i] < rnk[j];
            int a = (i+n<N) ? rnk[i+n] : -1;
            int b = (j+n<N) ? rnk[j+n] : -1;
            return a < b;
        }
    };
     
    void suffix_array()
    {
        int* rnk = temp[0];
        int* new_rank = temp[1];
     
        for (int i=0; i<N; i++)
        {
            // 各個名次對應的後綴
            // 隨便初始化一個順序，稍後會重新排序。
            sa[i] = i;
            // 各個後綴對應的名次
            // 偷懶取巧：直接把ASCII數值當作是名次。
            rnk[i] = s[i];
        }
     
        // 鍵值長度逐步倍增
        for (int n=1; n<N; n*=2)
        {
            // 運用上一回合求得的名次，排序所有後綴。
            // 鍵值是每個後綴的前2*n個字元，
            // 先比前半段、再比後半段。
            CMP cmp = {rnk, n, N};
            sort(sa, sa+N, cmp);
     
            // 重新整理名次。
            // 相異者、排在相異名次，相同者、排在相同名次。
            int r = 0;
            new_rank[sa[0]] = r;
            for (int i=1, r=0; i<N; i++)
            {
                if (cmp(sa[i-1], sa[i])) r++;
                new_rank[sa[i]] = r;
            }
            swap(rnk, new_rank);
     
            // 如果名次皆相異，表示排序完畢，可以提早結束。
            if (r == N-1) break;
        }
    }
     
    int rnk[100005];   // 各個後綴對應的名次
    int lcpa[100005];   // longest common prefix array
     
    void lcp_array()
    {
        // 也就是各個後綴在sa當中的索引值
        // 也就是sa的反函數
        for (int i=0; i<N; ++i)
            rnk[sa[i]] = i;
     
        for (int i=0, lcp=0; i<N; i++)
            if (rnk[i] == 0)
                lcpa[0] = 0;
            else
            {
                int j = sa[rnk[i]-1];
                if (lcp > 0) lcp--;
                while (s[i+lcp] == s[j+lcp]) lcp++;
                lcpa[rnk[i]] = lcp;
            }
    }