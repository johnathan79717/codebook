int row = 0;
for(int i = 0; i < N; i++) {
  int pivot = -1;
  for(int j = row; j < N; j++)
    if (B[j][i].i) {
      pivot = j;
      break;
    }
  if (pivot < 0) continue;
  swap(B[row], B[pivot]);
  for(int j = N-1; j >= i; j--)
    B[row][j] /= B[row][i];
  for(int j = 0; j < N; j++)
    if(row != j)
      for(int k = N-1; k >= i; k--)
        B[j][k] -= B[j][i] * B[row][k];
  row++;
}