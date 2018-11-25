double EPS = 1e-10;

double add(double a, double b) {
  //if(abs(a + b) < EPS * (abs(a) + abs(b))) return 0;
  return a + b;
}

struct P {
  double x, y, z;
  P() {}
  P(double x, double y, double z) : x(x), y(y), z(z) {}
  void read() {
      scanf("%lf%lf%lf", &x, &y, &z);
  }
  void print() {
      printf("%f %f %f\n", x, y, z);
  }
  P operator + (const P &p) const {
    return P(add(x, p.x), add(y, p.y), add(z, p.z));
  }
  P operator - (const P &p) const {
    return P(add(x, -p.x), add(y, -p.y), add(z, -p.z));
  }
  P operator * (double d) const {
    return P(x * d, y * d, z * d);
  }
  bool operator == (const P &p) const {
    return abs(this->x - p.x) < EPS * (abs(this->x) + abs(p.x))
     && abs(this->y - p.y) < EPS * (abs(this->y) + abs(p.y))
     && abs(this->z - p.z) < EPS * (abs(this->z) + abs(p.z));
  }
  //bool operator < (const P &p) const {
    //if(abs(this->x - p.x) > EPS) return this->x < p.x;
    //return this->y < p.y;
  //}
  double dot(const P &p) const {
    return add(add(x * p.x, y * p.y), z * p.z);
  }
  //double cross(const P &p) const {
    //return add(x * p.y, -y * p.x);
  //}
  //bool on_seg(const P &p1, const P &p2) const {
    //return (p1 - *this).cross(p2 - *this) == 0 && (p1 - *this).dot(p2 - *this) <= 0;
  //}
  // int rel_pos(const P &p1, const P &p2) const {
  //   return sign((p1 - *this).det(p2 - *this));
  // }
};

