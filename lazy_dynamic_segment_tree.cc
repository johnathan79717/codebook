#include <new>

#ifdef DEBUG
const int POOL_SIZE = 4e4;
#else
const int POOL_SIZE = 4e6;
#endif

struct Data {
    mint pairs, sum;
};

struct Node {
    Node *child[2];
    mint lazy;
    Data dat;
    int l, r;
    Node(): lazy(0), dat((Data){0, 0}), l(-1), r(-1) {
        memset(child, 0, sizeof child);
    }
    Node(int l, int r): lazy(0), dat((Data){0, 0}), l(l), r(r) {
        memset(child, 0, sizeof child);
    }
    static Node pool[POOL_SIZE];
    static Node *ptr;
    Node* getChild(int c) {
        int m = (l + r) / 2;
        return child[c] ? child[c] : (child[c] = new(ptr++) Node(c ? m : l, c ? r : m));
    }

    void propagate() {
        dat = query();
        if (r - l > 1) {
            Node *chl = getChild(0);
            Node *chr = getChild(1);
            chl->lazy += lazy;
            chr->lazy += lazy;
        }
        lazy = 0;
    }

    Data query() {
        mint ps = r - l;
        return (Data){ dat.pairs + dat.sum * lazy + ps * (lazy.val() * (lazy.val() - 1ll) / 2), dat.sum + lazy * ps };
    }

    static Data combine(Data vl, Data vr) {
        return Data({vl.pairs + vr.pairs, vl.sum + vr.sum});
    }

    void update(mint d) {
        lazy += d;
    }
} Node::pool[POOL_SIZE], *Node::ptr = pool;
#include <new>

const int POOL_SIZE = 4e6;

struct Data {
    mint pairs, sum;
};

struct Node {
    Node *child[2];
    mint lazy;
    Data dat;
    Node() : lazy(0), dat((Data){0, 0}) {
        memset(child, 0, sizeof child);
    }
    static Node pool[POOL_SIZE];
    static Node *ptr;
    Node* getChild(int c) {
        return child[c] ? child[c] : (child[c] = new(ptr++) Node);
    }

    void propagate(int l, int r) {
        mint ps = r - l;
        dat.pairs += dat.sum * lazy + ps * (lazy.val() * (lazy.val() - 1ll) / 2);
        dat.sum += lazy * ps;
        if (r - l > 1) {
            getChild(0)->lazy += lazy;
            getChild(1)->lazy += lazy;
        }
        lazy = 0;
    }

    static Data combine(Data vl, Data vr) {
        return Data({vl.pairs + vr.pairs, vl.sum + vr.sum});
    }

    void update(int a, int b, int l, int r, mint d) {
        debug("update", a, b, d.val());
        // we have to make sure dat[k] is the right value after update
        // also all ancestor's lazy values should have already been propagated here
        if (a <= l && r <= b) {
            lazy += d;
            propagate(l, r);
        } else {
            propagate(l, r);
            if (r <= a || b <= l) {
                return;
            }
            int m = (l+r)/2;
            Node *chl = getChild(0);
            Node *chr = getChild(1);
            chl->update(a, b, l, m, d);
            chr->update(a, b, m, r, d);
            dat = combine(chl->dat, chr->dat);
        }
    }

    void update(int a, int b, mint d) {
        update(a, b, a, b, d);
    }
} Node::pool[POOL_SIZE], *Node::ptr = pool;
