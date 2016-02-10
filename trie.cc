#include <new>

struct Node {
    Node *child[26];
    bool isLeaf;
    Node() : isLeaf(false) {
        memset(child, 0, sizeof child);
    }
    void insert(char *word) {
        if (*word) {
            getChild(*word)->insert(word+1);
        } else {
            isLeaf = true;
        }
    }
    static Node pool[POOL_SIZE];
    static Node *ptr;
    Node* getChild(char c) {
        return child[c-'a'] ? child[c-'a'] : (child[c-'a'] = new(ptr++) Node);
    }
} Node::pool[], *Node::ptr = pool;
