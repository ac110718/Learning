class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map<char, int> map;
        int cycles = 0;
        for (char t : tasks) {
            map[t]++;
            cycles = max(cycles, map[t]);
        }
        int result = (cycles-1)*(n+1);
        for (auto x : map) {
            if (x.second == cycles) result++;
        }
        return max((int)tasks.size(), result);
        
    }
};