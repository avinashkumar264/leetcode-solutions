class Solution {
public:
    int strStr(string haystack, string needle) {
        int n=haystack.size();
        int n1=needle.size();
        int i=0,j=0;
        int count=0,found;

        while(i<n){
            if(haystack[i]==needle[j]){
                i++;
                j++;
                if(j==n1){
                    return i-j;
                }
            }
            else{
                i = i - j + 1;
                j=0;
            }   
        }
        return -1;
    }
};