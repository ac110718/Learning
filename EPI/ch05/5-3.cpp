#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool CanReachEnd(const vector<int>& max_advance_steps) {
    int furthest_reach_so_far = 0, last_index = size(max_advance_steps) - 1;
    for (int i = 0; i <= furthest_reach_so_far && furthest_reach_so_far < last_index; ++i) {
        // compare furthest best with current position + future steps
        // constantly reassess the best you can do with each position..
        // ...so long as that position was reachable in first place (i<=furthest_reach_so_far)
        furthest_reach_so_far = max(furthest_reach_so_far, max_advance_steps[i] + i);
    }
    return furthest_reach_so_far >= last_index;
}

// delete duplicates from sorted array
int DeleteDuplicates(vector<int>* A_ptr) {
    vector<int>& A = *A_ptr;
    if(empty(A)) return 0;
    int write_index = 1;
    for (int i = 1; i < size(A); i++) {
        if (A[write_index-1] != A[i])
            A[write_index++] = A[i];
    }
    return write_index;
}

// what can the current element tell you?
// for each element.. the max profit is current minus min price thus far.
double BuyAndSellStockOnce(const vector<double>& prices) {
    double min_price_so_far = numeric_limits<double>::max();
    double max_profit = 0;
    for (double price : prices) {
        double max_profit_today = price - min_price_so_far;
        max_profit = max(max_profit, max_profit_today);
        min_price_so_far = min(price, min_price_so_far);
    }
    return max_profit;
}

//for buy and sell twice.. you pick the running max going both ways and choose the biggest adjacent pair within a list that tracks max profit
//on first and second sale, respectively

double BuyAndSellStockTwice(const vector<double>& prices)

int main() {
    auto m = vector{3, 3, 1, 0, 2, 0, 1};
    auto n = vector{3, 2, 0, 0, 2, 0, 1};
    cout << boolalpha << CanReachEnd(m) << endl;
    cout << CanReachEnd(n) << endl;
    std::sort(m.begin(), m.end());
    auto x = DeleteDuplicates(&m);
    for (int i=0; i < x; i++) {
        cout << m[i] << ", ";
    }
    cout << endl;
    auto a = vector<double>{310,315,275,295,260,270,290,230,255,250};
    cout << BuyAndSellStockOnce(a) << endl;
}