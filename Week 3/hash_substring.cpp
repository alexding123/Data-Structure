#include <iostream>
#include <string>
#include <vector>

using std::string;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

ull poly_hash(const string& s, ull prime, int x) {
    ull hash = 0; 
    for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i) {
        hash = (hash * x + s[i]) % prime;
    }
    return hash;
}

bool are_equal(const string& a, long long start, long long end, const string& b) {
    for (ull i = 0; i <= end - start; i++) {
        if (a[i+start] != b[i]) 
            return false;
    }
    return true;
}

std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    const size_t prime = 1000000007;
    const int multiplier = 263; 
    std::vector<ull> lengths(t.size() - s.size() + 1);
    lengths[t.size() - s.size()] = poly_hash(t.substr(t.size() - s.size(), s.size()), prime, multiplier);
    ull last_term = 1;
    for (ull i = 0; i < s.size(); i++) {
        last_term = (last_term * multiplier) % prime; // precompute multiplier^s.size() mod prime
    }
    for (long long i = static_cast<int>(t.size() - s.size() - 1); i >= 0; --i) {
        lengths[i] = ((multiplier * lengths[i+1] + t[i] - (last_term * t[i+s.size()] % prime)) + prime) % prime; 
    }

    std::vector<int> ans;
    ull hash_val = poly_hash(s, prime, multiplier);
    for (ull i = 0; i <= (t.size() - s.size()); i++) {
        if (lengths[i] == hash_val) {
            if (are_equal(t, i, i+s.size()-1, s)) {
                ans.push_back(i);
            }
        }
    }
    
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
