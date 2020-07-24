#include <cstring>
#include <cassert>
#include <queue>

//int equiv[1000];

struct TrieNode {
    TrieNode* l[26], *suffix, *dictsuffix, *root;
    int index;  // dict string ID

    TrieNode(TrieNode* root): suffix(0), dictsuffix(0), index(-1) {
        memset(l, 0, sizeof(l));
        this->root = root ? root : this;
    }

    // 把一個字串加入trie
    void add(char* s, int idx) {
        TrieNode* p = this;
        for (; *s; ++s) {
            if (!p->l[*s - 'a'])
                p->l[*s - 'a'] = new TrieNode(root);
            p = p->l[*s - 'a'];
        }

        // 如果此字串之前有出現，就特別紀錄起來。
        if (p->index == -1) {
            p->index = idx;
        } else {
            assert(false);
            //equiv[index] = p->index;
        }
    }

    void build() {
        std::queue<TrieNode*> que;
        que.push(this);

        while (que.size()) {
            TrieNode* p = que.front();
            que.pop();
            for (int i=0; i<26; ++i)
                if (p->l[i])
                {
                    TrieNode* q = p->suffix;
                    while (q && !q->l[i]) q = q->suffix;
                    if (q) p->l[i]->suffix = q->l[i];
                    else   p->l[i]->suffix = this;

                    TrieNode* r = p->l[i]->suffix;
                    if (r->index != -1) p->l[i]->dictsuffix = r;
                    else p->l[i]->dictsuffix = r->dictsuffix;

                    que.push(p->l[i]);
                }
        }
    }

    TrieNode* match(char c) {
        TrieNode *p = this;
        while (p && !p->l[c - 'a']) {
            p = p->suffix;
        }
        p = p ? p->l[c - 'a'] : root;
        return p;
    }

    std::vector<int> matched_indices() {
        std::vector<int> ret;
        if (index != -1) {
            ret.push_back(index);
        }
        for (TrieNode* q = this->dictsuffix; q; q = q->dictsuffix) {
            ret.push_back(q->index);
        }
        return ret;
    }

    ~TrieNode() {
        for (int i = 0; i < 26; ++i) {
            if (l[i]) {
                delete l[i];
            }
        }
    }
} *trie;
