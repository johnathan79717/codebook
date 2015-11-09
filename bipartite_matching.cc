#include <iostream>
#include <cstring>
#include <map>
using namespace std;

int nx, ny;             // X的點數目、Y的點數目
int mx[1000], my[1000];   // X各點的配對對象、Y各點的配對對象
int px[1000], py[1000];   // 交錯森林
bool adj[1000][1000];     // 精簡過的adjacency matrix
 
// 由樹葉往樹根找擴充路徑，並擴充。
int trace(int y)
{
    int x = py[y], yy = px[x];
    py[y] = px[x] = -1; // 一旦拜訪過的點就不再拜訪
    if (mx[x] == -1 || (yy != -1 && trace(yy)))
    {
        mx[x] = y; my[y] = x;
        return 1;
    }
    return 0;
}
 
int bipartite_matching()
{
    memset(mx, -1, sizeof(mx));
    memset(my, -1, sizeof(my));
 
    int q[1000], *qf, *qb;
    int c = 0;
    while (true)    // 如果還能找到擴充路徑就繼續
    {
        memset(px, -1, sizeof(px));
        memset(py, -1, sizeof(py));
        qf = qb = q;
 
        // 把X的未匹配點，作為交錯森林的樹根。
        for (int x=0; x<nx; ++x)
            if (mx[x] == -1)
            {
                *qb++ = x;
//              px[x] = -2;
            }
 
        // 採用BFS建立交錯森林，一次僅延展一整層，
        // 直到發現所有目前最短的擴充路徑。
        bool ap = false;    // 是否存在擴充路徑
        for (int* tqb = qb; qf < tqb && !ap; tqb = qb)
            for (int x=*qf++, y=0; y<ny; ++y)
                if (adj[x][y] /*&& mx[x] != y*/ && py[y] == -1)
                {
                    py[y] = x;
                    if (my[y] == -1) ap = true;
                    else *qb++ = my[y], px[my[y]] = y;
                }
        if (!ap) break;
 
        // 由樹葉往樹根找擴充路徑，並擴充。
        for (int y=0; y<ny; ++y)
            if (my[y] == -1 && py[y] != -1)
                c += trace(y);
    }
    return c;
}


int main() {
  int T;
  cin >> T;
  while(T--) {
    int N;
    cin >> N;
    map<int, int> ix, iy;
    nx = 0;
    ny = 0;
    memset(adj, false, sizeof(adj));
    while(N--) {
      int X, Y;
      cin >> X >> Y;
      if(ix.find(X) == ix.end())
        ix[X] = nx++;
      if(iy.find(Y) == iy.end())
        iy[Y] = ny++;
      adj[ix[X]][iy[Y]] = true;
    }
    cout << bipartite_matching() << endl;
  }
}