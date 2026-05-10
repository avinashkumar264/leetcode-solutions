#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {

        // Step 1: Agar vector empty hai
        if (strs.size() == 0) {
            return "";
        }

        // Step 2: First string ko reference maan lo
        string firstString = strs[0];

        int totalStrings = strs.size();
        int lengthOfFirst = firstString.length();

        // Step 3: First string ke har character ko check karo
        for (int i = 0; i < lengthOfFirst; i++) {

            char currentCharacter = firstString[i];

            // Step 4: Baaki sab strings me check karo
            for (int j = 1; j < totalStrings; j++) {

                string currentString = strs[j];

                int lengthOfCurrent = currentString.length();

                // Case 1: Agar current string choti hai
                if (i >= lengthOfCurrent) {
                    return firstString.substr(0, i);
                }

                // Case 2: Agar character match nahi karta
                if (currentString[i] != currentCharacter) {
                    return firstString.substr(0, i);
                }
            }
        }

        // Agar pura first string match ho gaya
        return firstString;
    }
};