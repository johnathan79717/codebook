const double PI = acos(-1);
struct PT {
    double x, y;
    PT() {}
    PT(double xx, double yy): x(xx), y(yy) {}
    PT operator+(const PT& p) const {
        return PT(x + p.x, y + p.y);
    }
    PT& operator+=(const PT& p) {
        x += p.x;
        y += p.y;
        return *this;
    }
    PT operator-(const PT& p) const {
        return PT(x - p.x, y - p.y);
    }
    PT operator*(double c) const {
        return PT(x * c, y * c);
    }
    PT& operator*=(double c) {
        x *= c;
        y *= c;
        return *this;
    }
    PT operator/(double c) const {
        return PT(x / c, y / c);
    }
    double operator*(const PT& p) const {
        return x * p.x + y * p.y;
    }
    double operator^(const PT& p) const {
        return x * p.y - y * p.x;
    }
    double len2() const {
        return x * x + y * y;
    }
    double len() const {
        return sqrt(len2());
    }
    PT U() const {
        return *this / len();
    }
    PT T() const {
        return PT(-y, x);
    }
    PT rot(double a) const {
        double c = cos(a), s = sin(a);
        return PT(c * x - s * y, s * x + c * y);
    }
    PT rot(int a) const {
        return rot(a * PI / 180);
    }
};

