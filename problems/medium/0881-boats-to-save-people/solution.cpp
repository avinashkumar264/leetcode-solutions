#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());

        int i = 0;
        int j = people.size() - 1;
        int boats = 0;

        while (i <= j) {
            if (people[i] + people[j] <= limit) {
                i++;      // light person boards
            }
            j--;          // heavy person always boards
            boats++;     // one boat used
        }
        return boats;
    }
};
