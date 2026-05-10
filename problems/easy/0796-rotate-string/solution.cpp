class Solution {
public:
    bool rotateString(string s, string goal) {
        
        if(s.length() != goal.length())
            return false;
        
        string temp = s + s;
        
        size_t pos = temp.find(goal);
        
        if(pos != string::npos)
            return true;
        
        return false;
    }
};