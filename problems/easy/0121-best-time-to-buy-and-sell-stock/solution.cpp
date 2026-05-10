class Solution {
public:
    int maxProfit(vector<int>& prices) {

        int minimum = prices[0];
        int maximumProfit = 0;

        for (int i = 1; i < prices.size(); i++) {

            int profit = prices[i] - minimum;

            maximumProfit = max(maximumProfit, profit);

            minimum = min(minimum, prices[i]);
        }

        return maximumProfit;
    }
};