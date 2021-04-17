#include <functional>
#include <unordered_map>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
    int from, to, w;
    char dir;
    Edge *prev;
};

// https://en.wikipedia.org/wiki/Edmonds%27_algorithm

unordered_map<int, Edge> Edmonds(const vector<int>& V, vector<Edge>& E, int root) {
    unordered_map<int, bool> visited, visiting; 
    visited[root] = true;
    unordered_map<int, Edge> P;
    for (auto &e : E) {
        int v = e.to;
        if (!P.count(v) || e.w < P[v].w) {
            P[v] = e;
        }
    }
    for (int v : V) {
        queue<int> q;
        while (true) {
            if (visited[v]) {
                while (q.size()) {
                    int u = q.front();
                    visited[u] = true;
                    visiting[u] = false;
                    q.pop();
                }
                break;
            }
            if (visiting[v]) {
                while (q.front() != v) {
                    visiting[q.front()] = false;
                    q.pop();
                }
                break;
            }
            visiting[v] = true;
            q.push(v);
            v = P[v].from;
        }
        if (visiting[v]) {
            // cycle found
            int vc = *max_element(V.begin(), V.end()) + 1;
            vector<int> V1 = {vc};
            for (int v : V) {
                if (!visiting[v]) {
                    V1.push_back(v);
                }
            }
            assert(V1.size() < V.size());

            vector<Edge> E1;
            for (auto &e : E) {
                int u = e.from, v = e.to;
                if (!visiting[u] && visiting[v]) {
                    E1.push_back(Edge{u, vc, e.w - P[v].w, e.dir, &e});
                } else if (visiting[u] && !visiting[v]) {
                    E1.push_back(Edge{vc, v, e.w, e.dir, &e});
                } else if (!visiting[u] && !visiting[v]) {
                    E1.push_back(e);
                }
            }
            auto P1 = Edmonds(V1, E1, root);
            unordered_map<int, Edge> ans;
            for (auto &pr : P1) {
                if (pr.first == vc) {
                    auto &e = *pr.second.prev;
                    assert(!ans.count(e.to));
                    ans[e.to] = e;
                    for (int v : V) {
                        if (visiting[v] && v != e.to) {
                            assert(!ans.count(v));
                            ans[v] = P[v];
                        }
                    }
                } else if (pr.second.from == vc) {
                    ans[pr.second.to] = *pr.second.prev;
                } else {
                    ans.insert(pr);
                }
            }
            return ans;
        }
    }
    // No cycles
    return P;
};

