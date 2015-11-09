struct Node {
    Node *child[26];
};

Node pool[1000001];
int p = 0;
Node *newNode() {
    return &pool[p++];
}