#define MAX_N

int par[MAX_N];
int depth[MAX_N];

void init(int n) {
  for(int i = 0; i < n; i++) {
    par[i] = i;
    depth[i] = 0;
  }
}

int find(int x) {
  if(par[x] == x) {
    return x;
  } else {
    return par[x] = find(par[x]);
  }
}

void unite(int x, int y) {
  x = find(x);
  y = find(y);
  if(x == y) return;
  if(depth[x] < depth[y]) {
    par[x] = y;
  } else {
    par[y] = x;
    if(depth[x] == depth[y]) depth[x]++;
  }
}

bool same(int x, int y) {
  return find(x) == find(y);
}