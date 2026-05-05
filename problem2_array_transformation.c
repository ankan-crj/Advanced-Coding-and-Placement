#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort to sort in ascending order
int compare(const void *a, const void *b) {
    long long x = *(long long*)a;
    long long y = *(long long*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int main() {
    int N;
    long long K;

    // Input Format: N followed by the array A and then K
    if (scanf("%d", &N) != 1) return 0;
    
    long long *A = (long long*)malloc(N * sizeof(long long));
    for (int i = 0; i < N; i++) {
        scanf("%lld", &A[i]);
    }
    
    if (scanf("%lld", &K) != 1) {
        free(A);
        return 0;
    }

    // Step 1: Feasibility Check
    // All elements must have the same remainder when divided by K
    long long first_rem = A[0] % K;
    // Handle negative remainders in C for consistency
    if (first_rem < 0) first_rem += K; 

    for (int i = 1; i < N; i++) {
        long long current_rem = A[i] % K;
        if (current_rem < 0) current_rem += K;
        
        if (current_rem != first_rem) {
            printf("-1\n");
            free(A);
            return 0;
        }
    }

    // Step 2: Sorting to find the Median
    qsort(A, N, sizeof(long long), compare);
    long long median = A[N / 2];

    // Step 3: Calculate Minimum Operations
    long long total_ops = 0;
    for (int i = 0; i < N; i++) {
        long long diff = (A[i] > median) ? (A[i] - median) : (median - A[i]);
        total_ops += (diff / K);
    }

    printf("%lld\n", total_ops);

    free(A);
    return 0;
}
