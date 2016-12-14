template<class T>
struct Treap {
    //static Treap mem[], *pmem;
    static unsigned state;
    Treap *l, *r;
    unsigned pri;
    T key;
    //int val;
    int size;
    Treap() {}
    Treap(T _key) : l(nullptr), r(nullptr), pri(state), key(_key), size(1) {
        state = state * 1297 + 1301;
    }
    void pull() {
        size = 1;
        if (l) size += l->size;
        if (r) size += r->size;
    }
    void push() {
        //val = val.rot(lazy);
        //data = data.rot(lazy);
        //if (l) l->lazy += lazy;
        //if (r) r->lazy += lazy;
        //lazy = 0;
    }
} /*Treap::mem[], *Treap::pmem = Treap::mem*/;

//Treap *make(int key) {
    //return new (Treap::pmem++) Treap(key);
//}

template<class T>
Treap<T> *merge(Treap<T> *a, Treap<T> *b) {
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

template<class T>
void split(Treap<T> *t, T k, Treap<T> *&a, Treap<T> *&b) {
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

template<class T>
void insert(Treap<T> *&t, T key) {
    Treap<T> *a, *b;
    split(t, key, a, b);
    t = merge(a, merge(new Treap<T>(key), b));
}
