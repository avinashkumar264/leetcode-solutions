class Solution {
public:
    string strWithout3a3b(int a, int b) {
        string ans = "";

        while (a > 0 || b > 0) {

            int n = ans.size();

            // Case 1: last two are 'a'
            if (n >= 2 && ans[n-1] == 'a' && ans[n-2] == 'a') {
                ans += 'b';
                b--;
            }
            // Case 2: last two are 'b'
            else if (n >= 2 && ans[n-1] == 'b' && ans[n-2] == 'b') {
                ans += 'a';
                a--;
            }
            // Case 3: normal greedy
            else if (a >= b && a > 0) {
                ans += 'a';
                a--;
            }
            else {
                ans += 'b';
                b--;
            }
        }

        return ans;
    }
};