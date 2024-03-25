#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> compute_prefix_function(string pattern) {
    int m = pattern.length();
    vector<int> pi(m, 0);
    int k = 0;
    for (int q = 1; q < m; q++) {
        while (k > 0 && pattern[k] != pattern[q]) {
            k = pi[k - 1];
        }
        if (pattern[k] == pattern[q]) {
            k++;
        }
        pi[q] = k;
    }
    return pi;
}

vector<int> kmp_search(string pattern, string text) {
    int n = text.length();
    int m = pattern.length();
    vector<int> pi = compute_prefix_function(pattern);
    int q = 0;
    vector<int> matches;
    for (int i = 0; i < n; i++) {
        while (q > 0 && pattern[q] != text[i]) {
            q = pi[q - 1];
        }
        if (pattern[q] == text[i]) {
            q++;
        }
        if (q == m) {
            matches.push_back(i - m + 1);
            q = pi[q - 1];
        }
    }
    return matches;
}
