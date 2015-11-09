int N = 1000;   // P的個數
char T[100+1];
char P[1000][100+1];
 
bool occur[1000];   // 紀錄各個P有沒有出現在T當中
 
struct TrieNode
{
  TrieNode* l[26], *suffix, *dictsuffix;
  int index;  // P的編號
 
  TrieNode()
  {
    memset(l, 0, sizeof(l));
    suffix = dictsuffix = 0;
    index = -1;
  }
};
 
// 初始化
void init()
{
  memset(occur, false, sizeof(occur));
  root = new TrieNode();
}
 
// 砍掉整棵trie
void free(TrieNode* p = root)
{
  for (int i=0; i<26; ++i)
    if (p->l[i])
      free(p->i[i]);
  delete p;
}
 
// 把一個字串加入trie
void add(char* s, int index)
{
  TrieNode* p = root;
  for (; *s; ++s)
  {
    if (!p->l[*s - 'A'])
      p->l[*s - 'A'] = new TrieNode();
    p = p->l[*s - 'A'];
  }
 
  // 如果此字串之前有出現，就特別紀錄起來。
  if (p->index == -1)
    p->index = index;
  else
    equiv[index] = p->index;
}
 
// 添上suffix link和dictionary suffix link
// 以BFS順序進行
// 時間複雜度O(Σ(Pi))
void build()
{
  TrieNode* q[100000], **qf, **qb;
  qf = qb = q;
  *qb++ = root;
 
  while (qf < qb)
  {
    TrieNode* p = *qf++;
    for (int i=0; i<26; ++i)
      if (p->l[i])
      {
        // 添上 suffix link
        TrieNode* q = p->suffix;
        while (q && !q->l[i]) q = q->suffix;
        if (q) p->l[i]->suffix = q->l[i];
        else   p->l[i]->suffix = root;
 
        // 添上 dictionary suffix link
        TrieNode* r = p->l[i]->suffix;
        if (r->index != -1) p->l[i]->dictsuffix = r;
        else p->l[i]->dictsuffix = r->dictsuffix;
 
        *qb++ = p->l[i];
      }
  }
}
 
// 拿trie與T進行字串匹配
// 時間複雜度O(T+K)
void match(char* s)
{
  TrieNode* p = root;
  for (; *s; ++s)
  {
    // 不斷比對字元，直到比對成功。
    // 此部分總計時間複雜度為O(T)。
    while (p && !p->l[*s - 'A']) p = p->suffix;
    if (p) p = p->l[*s - 'A'];
    else p = root;
 
    // 走dictionary suffix link找到所有匹配的P。
    // 此部分總計時間複雜度為O(K)。
    for (TrieNode* q = p; q; q = q->dictsuffix)
      if (q->index != -1)
        occur[q->index] = true;
  }
}
 
void aho_corasick()
{
  init();     // 初始化
  for (int i=0; i<N; ++i) // 所有P建立trie
    add(P[i], i);
  build();    // suffix link、dictionary suffix link
  match(T);   // 拿trie與T進行字串匹配
  free();     // 釋放記憶體空間
 
  for (int i=0; i<N; ++i)
    // 匹配到P，或者之前出現過、匹配到P。
    if (occur[i] ||
      equiv[i] != -1 && occur[equiv[i]])
      cout << "第" << i << "個字串有出現";
    else
      cout << "第" << i << "個字串沒出現";
}