#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_S 100005

// Helper function to get the value of a character (a=1, b=2, ..., z=26)
int get_val(char c) {
    return c - 'a' + 1;
}

long long solve() {
    static char s[MAX_S];
    if (scanf("%s", s) == EOF) return 0;

    int n = strlen(s);
    int char_count[26] = {0}; // Tracks characters in current window
    long long max_sum = 0;
    long long current_sum = 0;
    int left = 0;

    // We iterate up to 2*n - 1 to handle the cyclic wrap-around.
    // The loop stops when right reaches n + (max unique characters - 1) 
    // or 2*n, whichever is smaller.
    int limit = (n < 26) ? 2 * n : n + 26;

    for (int right = 0; right < limit; right++) {
        // Use modulo to simulate the doubled cyclic string s+s
        char right_char = s[right % n];
        int right_idx = right_char - 'a';

        // Shrink window if we find a duplicate OR if window length > n
        while (char_count[right_idx] > 0 || (right - left) >= n) {
            char left_char = s[left % n];
            char_count[left_char - 'a']--;
            current_sum -= get_val(left_char);
            left++;
        }

        // Add the new character to the window
        char_count[right_idx]++;
        current_sum += get_val(right_char);

        // Update the maximum sum found
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
    }

    return max_sum;
}

int main() {
    printf("%lld\n", solve());
    return 0;
}
