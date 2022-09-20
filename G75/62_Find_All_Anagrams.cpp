class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if (s.size() < p.size()) return {};
        vector<int> p_freq(26,0);
        vector<int> win_freq(26,0);
        for (int i = 0; i < p.size(); i++) {
            p_freq[p[i]-'a']++;
            win_freq[s[i]-'a']++;
        }
        vector<int> result;
        if (p_freq == win_freq) result.push_back(0);
        for (int i = p.size(); i < s.size(); i++) {
            win_freq[s[i]-'a']++;
            win_freq[s[i-p.size()]-'a']--;
            if (p_freq == win_freq) result.push_back(i-p.size()+1);
        }
        return result; 
    }
};