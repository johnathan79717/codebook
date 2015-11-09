class Graph {
  typedef pair<int, int> P;
  int V;
  struct edge { int to, cost; };
  vector<vector<edge> > G;
public:
  Graph() { V = 0; }
  Graph(int N) { V = N; }
  int addVertex() {
    G.resize(V+1);
    return V++;
  }
  void addEdge(int from, int to, int cost) {
    G[from].push_back((edge){to, cost});
    G[to].push_back((edge){from, cost});
  }
  vector<int> d;
  void dijkstra(int s) {
    d = VI(V, INF);
    priority_queue<P, vector<P>, greater<P> > que;
    d[s] = 0;
    que.push(P(0, s));

    while(!que.empty()) {
      P p = que.top(); que.pop();
      int v = p.second;
      if(d[v] < p.first) continue;
      for(int i = 0; i < G[v].size(); i++) {
        edge e = G[v][i];
        if(d[e.to] > d[v] + e.cost) {
          d[e.to] = d[v] + e.cost;
          que.push(P(d[e.to], e.to));
        }
      }
    }
  }
};