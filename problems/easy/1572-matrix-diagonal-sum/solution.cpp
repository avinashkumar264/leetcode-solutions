class Solution {
public:
    int diagonalSum(vector<vector<int>>& mat) {
        int n = mat.size();
        int sum = 0;

        for (int i = 0; i < n; i++) {
            // primary diagonal
            sum += mat[i][i];

            // secondary diagonal (avoid double count)
            if (i != n - 1 - i) {
                sum += mat[i][n - 1 - i];
            }
        }
        return sum;
    }
};