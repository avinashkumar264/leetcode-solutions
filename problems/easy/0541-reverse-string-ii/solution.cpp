#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    string reverseStr(string s, int k) {

        int n = s.length();

        // Har 2k block ke liye
        for(int i = 0; i < n; i = i + 2*k) {

            // Reverse karne ka range
            int left = i;
            int right = i + k - 1;

            // Agar remaining characters k se kam ho
            if(right >= n) {
                right = n - 1;
            }

            // Manual reverse using two pointers
            while(left < right) {
                char temp = s[left];
                s[left] = s[right];
                s[right] = temp;

                left++;
                right--;
            }
        }

        return s;
    }
};