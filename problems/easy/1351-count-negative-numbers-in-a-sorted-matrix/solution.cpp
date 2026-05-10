class Solution {
public:
    int countNegatives(vector<vector<int>>& grid) {
        
        int rows = grid.size();
        int cols = grid[0].size();
        
        int i = 0;
        int j = cols - 1;
        
        int count = 0;
        
        while(i < rows && j >= 0) {
            
            if(grid[i][j] < 0) {
                
                count += (rows - i);
                
                j--;
            }
            else {
                
                i++;
            }
        }
        
        return count;
    }
};