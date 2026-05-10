#include <vector>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {

        int left = 0;                          // left pointer
        int right = height.size() - 1;         // right pointer
        
        int maxWater = 0;                      // maximum area

        while(left < right) {

            int width = right - left;          // distance between lines

            int minHeight;
            if(height[left] < height[right]) {
                minHeight = height[left];
            } else {
                minHeight = height[right];
            }

            int currentArea = width * minHeight;

            if(currentArea > maxWater) {
                maxWater = currentArea;
            }

            // Move smaller height pointer
            if(height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }

        return maxWater;
    }
};