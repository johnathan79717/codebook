#define MAX_LOG_V 20
V(VI) G;
int parent[MAX_LOG_V][300001];
int depth[300001];

void init() {
    MS1(depth);
    MS1(parent);
    queue<int> q;
    q.push(0);
    depth[0] = 0;
    while (!q.empty()) {
        FOR(it, G[q.front()]) {
            int v = *it;
            if (depth[v] < 0) {
                depth[v] = depth[q.front()] + 1;
                parent[0][v] = q.front();
                q.push(v);
            }
        }
        q.pop();
    }
    for(int k = 0; k + 1 < MAX_LOG_V; k++) {
        for(int v = 0; v < N; v++) {
          if(parent[k][v] < 0)
            parent[k+1][v] = -1;
          else
            parent[k + 1][v] = parent[k][parent[k][v]];
        }
    }
}

int lca(int u, int v) {
  if(depth[u] > depth[v]) swap(u, v);
  for(int k = 0; k < MAX_LOG_V; k++) {
    if((depth[v] - depth[u]) >> k & 1) {
      v = parent[k][v];
    }
  }
  if(u == v) return u;
  for(int k = MAX_LOG_V - 1; k >= 0; k--) {
    if(parent[k][u] != parent[k][v]) {
      u = parent[k][u];
      v = parent[k][v];
    }
  }
  return parent[0][u];
}