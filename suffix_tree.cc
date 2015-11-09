// 該節點上方的樹枝，儲存s[a,b)的字元。
struct Node
{
    int a, b;
    Node* _l[27], *suffix;
    Node* &l(int i) {
        if (i == 0) return _l[26];
        return _l[i - 'a'];
    }
    Node() {}
    Node(int a, int b): a(a), b(b), suffix(0)
    {
        memset(_l, 0, sizeof(_l));
    }
} pool[100000];
int _p = 0;

Node *get(int a, int b) {
    Node *ans = &pool[_p++];
    *ans = Node(a, b);
    return ans;
}
 
Node *Ukkonen(char *s)
{
    Node* root = get(0, 0), *p = root;
 
    // 逐次加入字元s[i]。包含'\0'。
    int N = strlen(s);
    for (int a=0, i=0; i<N+1; ++i)
    {
        Node* ant = root;
        while (a <= i)
        {
            // 往下走，直到字元s[i-1]出現。
            while (true)
            {
                if (a == i) break;
                Node* q = p->l(s[a]);
                if (a + q->b - q->a > i) break;
                a += q->b - q->a;
                p = q;
            }
 
            Node* q = p;
            if (a == i)     // s[i-1]位在樹枝末梢。
            {
                // 節點已經建立。
                if (p->l(s[i])) break;
            }
            else if (a < i) // s[i-1]位在樹枝中間。
            {
                // 節點已經建立。
                Node* r = p->l(s[a]);
                int k = r->a + i - a;
                if (s[i] == s[k]) break;
 
                // 節點尚未建立。
                // 分裂此樹枝，以利將來插入樹葉。
                p->l(s[a]) = q = get(r->a, k);
                q->l(s[k]) = r; r->a = k;
            }
 
            // 建立樹葉。終身為葉。
            q->l(s[i]) = get(i, 1e9);
 
            // 建立上次樹葉的suffix link，連到這次樹葉。
            // 至於這次樹葉的suffix link要等到下次才知道。
            if (ant != root) ant->suffix = q;
            ant = q;
 
            // 走訪suffix link
            if (p->suffix) p = p->suffix;
            else a++;   // 次長後綴在同一個節點
        }
        if (ant != root) ant->suffix = p;
    }
    return root;
}