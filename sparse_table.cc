int sparse_table[17][100001];

template<class T>
void make_sparse_table(int N, const T &A) {
    REP(i, N) {
        sparse_table[0][i] = A[i];
    }
    int k = 1;
    while ((1 << k) <= N) {
        REP1(i, 0, N - (1 << k)) {
            sparse_table[k][i] = max(sparse_table[k-1][i], sparse_table[k-1][i+(1<<(k-1))]);
        }
        k++;
    }
}

int query_sparse_table(int l, int r) {
    if (l > r) swap(l, r);
    int k = sizeof(int) * 8 - 1 - __builtin_clz(r+1-l);
    return max(sparse_table[k][l], sparse_table[k][r+1-(1<<k)]);
}
