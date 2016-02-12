struct Treap {
    static Treap mem[], *pmem;
    Treap *l, *r;
    int pri, key;
    Value val;
    Data data;
    Lazy lazy;
    Treap() {}
    Treap(int _key) : l(nullptr), r(nullptr), pri(rand()), key(_key), val(1, 0), data(1, 0) {}
    void pull() {
        data = val;
        if (l) data += l->getData();
        if (r) data += r->getData();
    }
    Data getData() {
        //return data.rot(lazy);
    }
    void push() {
        //val = val.rot(lazy);
        //data = data.rot(lazy);
        //if (l) l->lazy += lazy;
        //if (r) r->lazy += lazy;
        //lazy = 0;
    }
} Treap::mem[], *Treap::pmem = Treap::mem;

Treap *make(int key) {
    return new (Treap::pmem++) Treap(key);
}

Treap *merge(Treap *a, Treap *b) {
    if (!a || !b) return a ? a : b;
    if (a->pri > b->pri) {
        a->push();
        a->r = merge(a->r, b);
        a->pull();
        return a;
    } else {
        b->push();
        b->l = merge(a, b->l);
        b->pull();
        return b;
    }
}

void split(Treap *t, int k, Treap *&a, Treap *&b) {
    if (!t) a = b = nullptr;
    else if (t->key <= k) {
        a = t;
        a->push();
        split(t->r, k, a->r, b);
        a->pull();
    } else {
        b = t;
        b->push();
        split(t->l, k, a, b->l);
        b->pull();
    }
}
