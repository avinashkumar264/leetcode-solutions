class Solution {
public:
    int sumOddLengthSubarrays(vector<int>& arr) {

        int n = arr.size();
        int total = 0;

        for (int i = 0; i < n; i++) {

            // len = 1,3,5,... (odd lengths)
            for (int len = 1; i + len <= n; len += 2) {

                int sum = 0;

                for (int j = i; j < i + len; j++) {
                    sum += arr[j];
                }

                total += sum;
            }
        }

        return total;
    }
};