/*
TASK 1. The Rabin-Karp algorithm
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int prime;
    string pattern, text;
    int alphabet_size = 26;
    vector<int> matches, spurious_hits;
    int pattern_hash = 0, text_hash = 0;

    cin >> prime;
    cin >> pattern;
    cin >> text;

    int text_length = text.length();
    int pattern_length = pattern.length();
    int h = 1;

    for (int i = 0; i < pattern_length - 1; i++) 
        h = (h * alphabet_size) % prime;

    for (int i = 0; i < pattern_length; i++) {
        text_hash = (alphabet_size * text_hash + text[i]) % prime;
        pattern_hash = (alphabet_size * pattern_hash + pattern[i]) % prime;
    }

    for (int s = 0; s < text_length - pattern_length + 1; s++) {
        if (pattern_hash == text_hash) {
            if (pattern == text.substr(s, pattern_length)) {
                matches.push_back(s);
            } else {
                spurious_hits.push_back(s);
            }
        }
        if (s < text_length - pattern_length + 1) {
            text_hash = (alphabet_size * (text_hash - h * text[s]) + text[s + pattern_length]) % prime;
            if (text_hash < 0) text_hash = (text_hash + prime);
        }
    }

    cout << "Matches:";
    for (int i : matches) 
        cout << " " << i;
    cout << endl;

    cout << "Spurious hits:";
    for (int i : spurious_hits) 
        cout << " " << i;
    cout << endl;

    return 0;
}

/*
TASK 2. The Knuth-Morris-Pratt algorithm
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string pattern, text;
    cin >> pattern >> text;
    vector<int> matches;
    vector<int> prefix(pattern.length(), 0);
    string combined = pattern + '#' + text;
    vector<int> combined_prefix(combined.length(), 0);
    
    for (int i = 1; i < pattern.length(); i++) {
        int j = prefix[i-1];
        while (j > 0 && pattern[i] != pattern[j]) j = prefix[j-1];
        if (pattern[i] == pattern[j]) j += 1;
        prefix[i] = j;
    }
    
    for (int i = 1; i < combined.length(); i++) {
        int j = combined_prefix[i-1];
        while (j > 0 && combined[i] != combined[j]) j = combined_prefix[j-1];
        if (combined[i] == combined[j]) j += 1;
        combined_prefix[i] = j;
    }
    
    for (int i = pattern.length() + 1; i < combined.length(); i++) {
        if (combined_prefix[i] == pattern.length()) matches.push_back(i - 2 * pattern.length());
    }
    
    cout << "Prefix template: ";
    for (int i = 0; i < prefix.size(); i++) cout << prefix[i] << " ";
    cout << endl;
    
    cout << "Prefix function: ";
    for (int i = 0; i < combined_prefix.size(); i++) cout << combined_prefix[i] << " ";
    cout << endl;
    
    cout << "Matches: ";
    for (int i = 0; i < matches.size(); i++) cout << matches[i] << " ";
    cout << endl;
}
