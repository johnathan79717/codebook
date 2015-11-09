double EPS = 1e-10;

double add(double a, double b) {
  if(abs(a + b) < EPS * (abs(a) + abs(b))) return 0;
  return a + b;
}

struct P {
  double x, y;
  P() {}
  P(double x, double y) : x(x), y(y) {}
  P operator + (const P &p) const {
    return P(add(x, p.x), add(y, p.y));
  }
  P operator - (const P &p) const {
    return P(add(x, -p.x), add(y, -p.y));
  }
  P operator * (double d) const {
    return P(x * d, y * d);
  }
  bool operator == (const P &p) const {
    return abs(this->x - p.x) < EPS * (abs(this->x) + abs(p.x))
     && abs(this->y - p.y) < EPS * (abs(this->y) + abs(p.y));
  }
  bool operator < (const P &p) const {
    if(abs(this->x - p.x) > EPS) return this->x < p.x;
    return this->y < p.y;
  }
  double dot(const P &p) const {
    return add(x * p.x, y * p.y);
  }
  double cross(const P &p) const {
    return add(x * p.y, -y * p.x);
  }
  bool on_seg(const P &p1, const P &p2) const {
    return (p1 - *this).cross(p2 - *this) == 0 && (p1 - *this).dot(p2 - *this) <= 0;
  }
  // int rel_pos(const P &p1, const P &p2) const {
  //   return sign((p1 - *this).det(p2 - *this));
  // }
};

P intersection(const P &p1, const P &p2, const P &q1, const P &q2) {
  return p1 + (p2 - p1) * ((q2 - q1).cross(q1 - p1) / (q2 - q1).cross(p2 - p1));
}

bool intersect(const P &p1, const P &p2, const P &q1, const P &q2) {
  P r = intersection(p1, p2, q1, q2);
  return r.on_seg(p1, p2) && r.on_seg(q1, q2);
}

bool cmp_x(const P& p, const P& q) {
    if (p.x != q.x) return p.x < q.x;
    return p.y < q.y;
}

vector<P> convex_hull(vector<P> &ps) {
    int n = ps.size();
    sort(ALL(ps), cmp_x);
    int k = 0;
    vector<P> qs(n * 2);
    REP(i, n) {
        // XXX To include points ON the edges, change "<=" to "<"
        while (k > 1 && (qs[k-1] - qs[k-2]).cross(ps[i] - qs[k-1]) <= 0) k--;
        qs[k++] = ps[i];
    }
    for (int i = n-2, t = k; i >= 0; i--) {
        // XXX To include points ON the edges, change "<=" to "<"
        while (k > t && (qs[k-1] - qs[k-2]).cross(ps[i] - qs[k-1]) <= 0) k--;
        qs[k++] = ps[i];
    }
    qs.resize(k-1);
    return qs;
}