#include <cstring>
#include <vector>
#include <iostream>

using namespace std;

void kmp_table(char *W, int *T) {
    T[0] = -1;
    int lw = strlen(W);
    int pos = 1, cnd = 0;
    while(pos < lw) {
        if(W[pos] == W[cnd]) {
            // when we need to backtrack,
            // the next character must be different from W[pos]
            // which implies it will not match W[cnd] either
            // so we can skip cnd and go to T[cnd] directly
            T[pos] = T[cnd];
        } else {
            T[pos] = cnd;
            do {
                cnd = T[cnd];
            } while (cnd >= 0 && W[pos] != W[cnd]);
        }
        pos++;
        cnd++;
    }
    T[lw] = cnd;
}

// search W in S, time complexity O(|S|)
vector<int> kmp_search(char *S, char *W, int *T) {
    int j = 0, k = 0;
    int ls = strlen(S), lw = strlen(W);
    vector<int> P;
    while(j < ls) {
        if (W[k] == S[j]) {
            k++;
            j++;
            if(k == lw) {
                P.push_back(j - lw);
                k = T[k];
            }
        } else {
            k = T[k];
            if (k < 0) {
                j++;
                k = 0;
            }
        }
    }
    return P;
}

int advance(char *str, int l, int *kmp, char ch, int j) {
    while (j == l || ch != str[j]) {
        if (kmp[j] < 0) {
            return 0;
        }
        j = kmp[j];
    }
    // j < ls && c[i] == str[j]
    return j + 1;
}
