V(VI) adj;

int i, N, M, cnt;
stack<int> s;
int idx[100001], lowlink[100001];
bool onStack[100001];

void strongconnect(int v) {
    idx[v] = i;
    lowlink[v] = i;
    i++;
    s.push(v);
    onStack[v] = true;
    FOR(it, adj[v]) {
        int w = *it;
        if (idx[w] < 0) {
            strongconnect(w);
        }
        if (onStack[w]) {
            lowlink[v] = min(lowlink[v], lowlink[w]);
        }
    }

    if (lowlink[v] == idx[v]) {
        // found a new strongly component
        cnt++;
        int w;
        do {
            // w is in this strongly component
            w = s.top(); s.pop();
            onStack[w] = false;
        } while(w != v);
    }
}

void tarjan() {
    i = 0;
    s = stack<int>();
    MS0(onStack);
    MS1(idx);
    cnt = 0;
    REP(v, N) {
        if (idx[v] < 0) {
            strongconnect(v);
        }
    }
}
