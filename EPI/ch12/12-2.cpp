#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

// LRU Cache for ISBN number. If inserted or looked up, update to be most recent. Evict old entries when capacity is reached
// Store "recency" via a queue that is limited at certain capacity
// store ISBN price + location in queue (recency) via an unordered map
// table + queue will effectively be the cache, and should be same size as capacity

class LruCache {
  public:
    LruCache(size_t capacity) {}
    explicit LruCache(int capacity) : capacity_(capacity) {} // don't allow for implicit conversion

    int Lookup(int isbn) {
        if (auto it = isbn_price_table_.find(isbn); it == end(isbn_price_table_)) {
            return -1;
        } else {
            int price = it -> second.second; // stored as pair {queue location, isbn price}
            MoveToFront(isbn, it); // update timestamp
            return price;
        }
    }

    void Insert(int isbn, int price) {
        if (auto it = isbn_price_table_.find(isbn); it != end(isbn_price_table_)) {
            MoveToFront(isbn, it);
        } else {
            if (size(isbn_price_table_) == capacity_) {
                cout << "Capacity reached : " << size(isbn_price_table_) << " | Removing : " << lru_queue_.back() << endl;
                isbn_price_table_.erase(lru_queue_.back());
                lru_queue_.pop_back();
            }
            lru_queue_.emplace_front(isbn);
            isbn_price_table_[isbn] = {begin(lru_queue_), price};
            cout << "Inserted isbn : " << lru_queue_.front() << endl;
        }
    }

    bool Erase(int isbn) {
        if (auto it = isbn_price_table_.find(isbn); it == end(isbn_price_table_)) {
            return false;
        } else {
            lru_queue_.erase(it->second.first);
            isbn_price_table_.erase(it);
            cout << "Erasure complete. Number of stored elements : " << size(isbn_price_table_) << endl;
            return true;
        }
    }

  private:
    // isbn -> {queue_iterator[location], price}
    typedef unordered_map<int, pair<list<int>::iterator, int>> Table;
    // second input is found entry of table map
    void MoveToFront(int isbn, const Table::iterator& it) {
        lru_queue_.erase(it->second.first); // remove old location
        lru_queue_.emplace_front(isbn); // yank to front
        it->second.first = begin(lru_queue_); // update location in table
    }
    int capacity_;
    Table isbn_price_table_;
    list<int> lru_queue_;
};

int main() {
    auto isbn_cache = new LruCache(10);
    for (int i = 0; i < 10; i++) {
        isbn_cache -> Insert(1000 + i, i);
    }
    isbn_cache -> Insert (2000, 11);
    isbn_cache -> Insert (3000, 12);
    isbn_cache -> Erase(1005);
    isbn_cache -> Insert (4000, 12);
    isbn_cache -> Lookup(1002);
    isbn_cache -> Insert (5000, 12);
}