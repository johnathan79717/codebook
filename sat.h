int neg(int var) {
    return var ^ 1;
}

struct SAT {
    int N;
    SAT() : N(0) {}
    V(VI) adj;
    VI idx, lowlink, onStack, ans;
    stack<int> stack;
    int i;
    int addVariable() {
        N += 2;
        return N - 2;
    }
    void imply(int a, int b) {
        adj.resize(N);
        adj[a].PB(b);
        adj[neg(b)].PB(neg(a));
    }
    bool fail;
    void dfs(int v) {
        idx[v] = i;
        lowlink[v] = i;
        i++;
        stack.push(v);
        onStack[v] = true;
        FOR(it, adj[v]) {
            int w = *it;
            if (idx[w] < 0) {
                dfs(w);
                if (fail) return;
            }
            if (onStack[w]) {
                lowlink[v] = min(lowlink[v], lowlink[w]);
            }
        }

        if (lowlink[v] == idx[v]) {
            // found a new strongly component
            int w;
            set<int> comp;
            do {
                // w is in this strongly component
                w = stack.top(); stack.pop();
                onStack[w] = false;
                if (comp.count(neg(w))) {
                    fail = true;
                    return;
                }
                comp.insert(w);
                if (!ans[neg(w)]) ans[w] = true;
            } while(w != v);
        }
    }

    bool solve() {
        i = 0;
        onStack = VI(N);
        idx = VI(N, -1);
        lowlink = VI(N);
        ans = VI(N);
        fail = false;
        REP(v, N) {
            if (idx[v] < 0) {
                dfs(v);
                if (fail) return false;
            }
        }
        return true;
    }
};

