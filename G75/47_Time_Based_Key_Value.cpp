class TimeMap {
unordered_map<string, pair<vector<string>, vector<int>>> ht;
public:
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        if (ht.find(key) == ht.end()) {
            vector<string> vals = {value};
            vector<int> timestamps = {timestamp};
            ht[key] = {vals, timestamps};
        } else {
            ht[key].first.push_back(value);
            ht[key].second.push_back(timestamp);
        }
    }
    
    string get(string key, int timestamp) {
        if (ht.find(key) == ht.end() || timestamp < ht[key].second[0]) return "";
        int n = ht[key].second.size();
        if (timestamp > ht[key].second[n-1]) return ht[key].first[n-1];
        int low = 0, hi = n-1, pos;
        while (low <= hi) {
            int mid = low + (hi - low) / 2;
            if (ht[key].second[mid] > timestamp) {
                hi = mid - 1;
            } else {
                if (ht[key].second[mid] == timestamp || ht[key].second[mid+1] > timestamp) {
                    pos = mid;
                    break;
                } else {
                    low = mid + 1;
                }
            }
        }
        return ht[key].first[pos];
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */