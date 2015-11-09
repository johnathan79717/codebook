#define MAX_V
#define MAX_E MAX_V*(MAX_V-1)/2

struct edge {int u, v, cost; };

bool comp(const edge& e1, const edge& e2) {
  return e1.cost < e2.cost;
}

edge es[MAX_E];
int V, E;

void init(), unite(int, int);
int find(int);
bool same(int, int);

int kruskal() {
  sort(es, es + E, comp);
  init();
  int res = 0;
  for(int i = 0; i < E; i++) {
    edge e = es[i];
    if(!same(e.u, e.v)) {
      unite(e.u, e.v);
      res += e.cost;
    }
  }
  return res;
}

#define MAX_N MAX_V

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