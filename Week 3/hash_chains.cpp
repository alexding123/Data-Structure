#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<vector<string > > elems;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = ((hash * multiplier + s[i]) % prime + prime) % prime; // (-2) % 5 != 3%5 but = (-2)
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {
        vector<vector<string > > temp(bucket_count, vector<string>(0, ""));
        elems = temp;
    }

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            // use reverse order, because we append strings to the end
            for (int i = static_cast<int>(elems[query.ind].size()) - 1; i >= 0; --i)
                std::cout << elems[query.ind][i] << " ";
            std::cout << "\n";
        } else {
            if (query.type == "find") {
                bool isFound = false;
                int m = hash_func(query.s);
                for (int i = 0; i < elems[m].size(); i++) {
                    if (elems[m][i] == query.s) {
                        isFound = true;
                        break;
                    }
                }
                writeSearchResult(isFound);
            } else if (query.type == "add") {
                bool isFound = false;
                int m = hash_func(query.s);
                for (int i = 0; i < elems[m].size(); i++) {
                    if (elems[m][i] == query.s) {
                        isFound = true;
                        break;
                    }
                }
                if (!isFound) {
                    elems[m].push_back(query.s); // pushes only if not found
                }
            } else if (query.type == "del") {
                int m = hash_func(query.s);
                for (int i = 0; i < elems[m].size(); i++) {
                    if (elems[m][i] == query.s) {
                        elems[m].erase(elems[m].begin()+i);
                        break;
                    }
                }
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
