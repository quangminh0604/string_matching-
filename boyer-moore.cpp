#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<char, int> preprocess_bad_character_table(string pattern) {
    int m = pattern.length();
    unordered_map<char, int> bad_character;
    for (int i = 0; i < m - 1; i++) {
        bad_character[pattern[i]] = m - i - 1;
    }
    return bad_character;
}

vector<int> preprocess_good_suffix_table(string pattern) {
    int m = pattern.length();
    vector<int> suffixes(m + 1, 0);
    vector<int> borders(m + 1, 0);
    pattern += '\0'; // Chuỗi kết thúc null
    int i = m, j = m + 1;
    borders[i] = j;
    while (i > 0) {
        while (j <= m && pattern[i - 1] != pattern[j - 1]) {
            if (suffixes[j] == 0) {
                suffixes[j] = j - i;
            }
            j = borders[j];
        }
        i--;
        j--;
        borders[i] = j;
    }
    j = borders[0];
    for (int i = 0; i <= m; i++) {
        if (suffixes[i] == 0) {
            suffixes[i] = j;
        }
        if (i == j) {
            j = borders[j];
        }
    }
    return suffixes;
}

vector<int> boyer_moore_search(string pattern, string text) {
    int n = text.length();
    int m = pattern.length();
    unordered_map<char, int> bad_character = preprocess_bad_character_table(pattern);
    vector<int> good_suffix = preprocess_good_suffix_table(pattern);
    vector<int> matches;
    int i = 0;
    while (i <= n - m) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[i + j]) {
            j--;
        }
        if (j < 0) {
            matches.push_back(i);
            i += good_suffix[0];
        } else {
            if (bad_character.find(text[i + j]) != bad_character.end()) {
                i += max(good_suffix[j + 1], j - bad_character[text[i + j]]);
            } else {
                i += good_suffix[j + 1];
            }
        }
    }
    return matches;
}
