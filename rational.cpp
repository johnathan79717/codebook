struct Rational {
    LL q, p;
    Rational() {}
    Rational(LL qq, LL pp): q(qq), p(pp) {
        assert(p > 0);
        LL d = gcd(abs(q), p);
        p /= d;
        q /= d;
    }
};

Rational operator-(const Rational &r1, const Rational &r2) {
    return Rational(r1.q * r2.p - r2.q * r1.p, r1.p * r2.p);
}

Rational operator+(const Rational &r1, const Rational &r2) {
    return Rational(r1.q * r2.p + r2.q * r1.p, r1.p * r2.p);
}

bool operator>=(const Rational &r1, const Rational &r2) {
    return (__int128)r1.q * r2.p >= (__int128)r2.q * r1.p;
}

bool operator<=(const Rational &r1, const Rational &r2) {
    return (__int128)r1.q * r2.p <= (__int128)r2.q * r1.p;
}

Rational operator*(const Rational &r1, const Rational &r2) {
    return Rational(r1.q * r2.q, r1.p * r2.p);
}