vector<vector<pair<LL, int> > > adj;
pair<LL, int> dfs(int u, int p) {
    pair<LL, int> ans = MP(0ll, u);
    FOR(e, adj[u]) {
        int v = e.F, w = e.S;
        if (v != p) {
            PII tmp = dfs(v, u);
            tmp.F += w;
            ans = max(ans, tmp);
        }
    }
    return ans;
}

LL diameter() {
    return dfs(dfs(1, -1).S, -1).F;
}