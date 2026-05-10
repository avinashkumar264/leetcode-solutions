class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {

        unordered_set<string> seen;
        unordered_set<string> repeated;

        int n = s.length();

        for (int i = 0; i <= n - 10; i++) {

            string sub = s.substr(i, 10);

            // agar pehle se seen hai → duplicate
            if (seen.count(sub)) {
                repeated.insert(sub);
            }
            else {
                seen.insert(sub);
            }
        }

        return vector<string>(repeated.begin(), repeated.end());
    }
};