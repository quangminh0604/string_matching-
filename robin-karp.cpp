#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int modulus = 101;

int hash_string(string s) {
    int h = 0;
    for (char c : s) {
        h = (h * 256 + c) % modulus;
    }
    return h;
}

vector<int> rabin_karp_search(string pattern, string text) {
    int n = text.length();
    int m = pattern.length();
    int pattern_hash = hash_string(pattern);
    int text_hash = hash_string(text.substr(0, m));
    vector<int> matches;
    for (int i = 0; i <= n - m; i++) {
        if (pattern_hash == text_hash) {
            if (text.substr(i, m) == pattern) {
                matches.push_back(i);
            }
        }
        if (i < n - m) {
            text_hash = (256 * (text_hash - text[i] * modulus) + text[i + m]) % modulus;
            if (text_hash < 0) {
                text_hash += modulus;
            }
        }
    }
    return matches;
}
