class Solution {
public:
    string reverseOnlyLetters(string s) {
        int i = 0, j = s.length() - 1;

        while (i < j) {
            // move left pointer until letter found
            while (i < j && !isalpha((unsigned char)s[i])) i++;

            // move right pointer until letter found
            while (i < j && !isalpha((unsigned char)s[j])) j--;

            // swap letters
            if (i < j) {
                swap(s[i], s[j]);
                i++;
                j--;
            }
        }
        return s;
    }
};
