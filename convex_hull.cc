const double EPS = 1e-10;

double add(double a, double b) {
    if (abs(a + b) < EPS * (abs(a) + abs(b))) return 0;
    return a + b;
}

int add(int a, int b) {
    return a + b;
}

template<class T>
struct P {
    double x, y;
    P() {}
    P(double x, double y) : x(x), y(y) {}
    double det(P p) {
        return add(x * p.y, -y * p.x);
    }
    P operator - (P p) {
        return P(add(x, -p.x), add(y, -p.y));
    }
};

template<class T>
bool cmp_x(const P<T>& p, const P<T>& q) {
    if (p.x != q.x) return p.x < q.x;
    return p.y < q.y;
}

template<class T>
vector<P<T> > convex_hull(vector<P<T> > &ps) {
    int n = ps.size();
    sort(ALL(ps), cmp_x<T>);
    int k = 0;
    vector<P<T> > qs(n * 2);
    REP(i, n) {
        // XXX To include points ON the edges, change "<=" to "<"
        while (k > 1 && (qs[k-1] - qs[k-2]).det(ps[i] - qs[k-1]) <= 0) k--;
        qs[k++] = ps[i];
    }
    for (int i = n-2, t = k; i >= 0; i--) {
        // XXX To include points ON the edges, change "<=" to "<"
        while (k > t && (qs[k-1] - qs[k-2]).det(ps[i] - qs[k-1]) <= 0) k--;
        qs[k++] = ps[i];
    }
    qs.resize(k-1);
    return qs;
}