class LRUCache {
    list<pair<int, int>> kv_map;
    unordered_map<int, list<pair<int, int>>::iterator> locator;
    int cap;
     
public:
    LRUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        if(locator.find(key) == locator.end()) return -1;
        auto i = locator[key];
        int val = i->second;
        if (i != kv_map.begin()) {
            kv_map.erase(i);
            kv_map.push_front(make_pair(key, val));
            locator[key] = kv_map.begin();
        }
        return val;  
    }
    
    void put(int key, int value) {
        if (locator.find(key) != locator.end()) {
            kv_map.erase(locator[key]);
        } else if (kv_map.size() >= cap) {
            locator.erase(kv_map.back().first);
            kv_map.pop_back();
        }
        kv_map.push_front(make_pair(key, value));
        locator[key] = kv_map.begin();    
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */