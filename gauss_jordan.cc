typedef long double LD;
const long double EPS = 1e-11;

template<class T>
vector<T> gauss_jordan(vector<vector<T> > const &M, vector<T> const &b) {
  int n = M.size();
  vector<vector<T> > B(n, vector<T>(n+1));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++)
      B[i][j] = M[i][j];
    B[i][n] = b[i];
  }
  for(int i = 0; i < n; i++) {
    int pivot = i;
    for(int j = i; j < n; j++)
      if(abs(B[j][i]) > abs(B[pivot][i]))
        pivot = j;
    swap(B[i], B[pivot]);
    if(abs(B[i][i]) < EPS) return vector<T>();
    for(int j = i+1; j <= n; j++)
      B[i][j] /= B[i][i];
    for(int j = 0; j < n; j++)
      if(i != j)
        for(int k = i+1; k <= n; k++)
          B[j][k] -= B[j][i] * B[i][k];
  }
  vector<T> x(n);
  for(int i = 0; i < n; i++)
    x[i] = B[i][n];
  return x;
}