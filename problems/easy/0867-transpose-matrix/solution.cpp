#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {

        int m = matrix.size();        // number of rows
        int n = matrix[0].size();     // number of columns

        // create transpose matrix of size n x m
        vector<vector<int>> result(n, vector<int>(m));

        // fill transpose matrix
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                result[j][i] = matrix[i][j];
            }
        }

        return result;
    }
};