#include <cmath>
using namespace std;

class Solution {
public:
    bool judgeSquareSum(int c) {
        long long a = 0;
        long long b = sqrt(c);

        while (a <= b) {
            long long sum = a * a + b * b;

            if (sum == c) return true;
            if (sum < c) a++;
            else b--;
        }
        return false;
    }
};
