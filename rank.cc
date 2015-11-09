int Rank() {
    int N = A.size();
    if (N == 0) return 0;
    int M = A[0].size();
    int rank = 0;
    for(int i = 0; i < M; i++) {
        for(int j = rank; j < N; j++) {
            if(A[j][i]) {
                swap(A[rank], A[j]);
                break;
            }
        }
        if(!A[rank][i]) {
            continue;
        }
        for(int j = rank+1; j < N; j++) {
            if(A[j][i]) {
                for(int k = i; k < M; k++)
                    A[j][k] ^= A[rank][k];
            }
        }
        rank++;
        if (rank == N) {
            break;
        }
    }
    return rank;
}