V(VI) adj;     // adjacency list

void add_edge(int u, int v) {
  adj[u].push_back(v);
  adj[v].push_back(u);
}

VI parent, depth;
VI heavy; // the heaviest child
VI size; // size of subtree

VI chain; // chain id
VI head; // the topmost node of the chain

void init(int n) {
  parent.resize(n);
  depth.resize(n);
  heavy.resize(n);
  size.resize(n);
  chain.resize(n);
  head.resize(n);
} 
 
void DFS(int i)
{
    if(parent[i] < 0) depth[i] = 0;
    size[i] = 1;
    for (int j: adj[i])
    {
        if (j == parent[i]) continue;
        parent[j] = i;
        depth[j] = depth[i] + 1;
 
        DFS(j);
 
        size[i] += size[j];
        if (heavy[i] == -1 || size[j] > size[heavy[i]]) 
            heavy[i] = j;
    }
}

void heavylight_DFS(int N, int root=0)
{
    init(N);
    fill(heavy.begin(), heavy.end(), -1);
 
    parent[root] = -1;
    depth[root] = 0;
    DFS(root);
 
    int c = 0;  
    for (int i=0; i<N; ++i)
        if (parent[i] == -1 || heavy[parent[i]] != i)
        {
            int l = 0;
            for (int k = i; k != -1; k = heavy[k])
                chain[k] = c, head[k] = i, l++;
            segTrees.EB(l);
            c++;
        }
}

int q[200000], *qf, *qb; // BFS queue
 
void heavylight_BFS(int N, int root = 0)
{
    init(N);
    qf = qb = q;
    parent[root] = -1;
    depth[root] = 0;
    *qb++ = root;
    while (qf < qb)
        for (int i=*qf++, k=0; k<adj[i].size(); ++k)
        {
            int j = adj[i][k];
            if (j == parent[i]) continue;
            parent[j] = i;
            depth[j] = depth[i] + 1;
            *qb++ = j;
        }
    fill(size.begin(), size.end(), 0);
    fill(heavy.begin(), heavy.end(), -1);
    for (int k=N-1; k>0; --k)   
    {
        int j = q[k], i = parent[q[k]];
        size[j]++;
        size[i] += size[j];
        if (heavy[i] == -1 || size[j] > size[heavy[i]])
            heavy[i] = j;
    }
    size[0]++;
 
    int c = 0;
    for (int i=0; i<N; ++i)
        if (parent[i] == -1 || heavy[parent[i]] != i)
        {
            int l = 0;
            for (int k = i; k != -1; k = heavy[k])
                chain[k] = c, head[k] = i, l++;
            segTrees.EB(l);
            c++;
        }
}
 
int lca(int i, int j)
{
    while (chain[i] != chain[j])
        if (depth[head[i]] > depth[head[j]])
            i = parent[head[i]];
        else
            j = parent[head[j]];
 
    return depth[i] < depth[j] ? i : j;
}