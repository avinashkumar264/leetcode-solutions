class Solution {
public:
    string multiply(string num1, string num2) {

        // edge case
        if (num1 == "0" || num2 == "0")
            return "0";

        int n = num1.size();
        int m = num2.size();

        vector<int> result(n + m, 0);

        // multiply digits from right to left
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {

                int digit1 = num1[i] - '0';
                int digit2 = num2[j] - '0';

                int product = digit1 * digit2;

                int pos1 = i + j;       // carry position
                int pos2 = i + j + 1;   // digit position

                int sum = product + result[pos2];

                result[pos2] = sum % 10;
                result[pos1] += sum / 10;
            }
        }

        // convert result array to string
        string answer = "";
        for (int num : result) {
            if (!(answer.empty() && num == 0))
                answer.push_back(num + '0');
        }

        return answer;
    }
};