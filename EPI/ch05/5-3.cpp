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

double BuyAndSellStockTwice(const vector<double>& prices) {
    double max_total_profit = 0;
    vector<double> first_buy_sell_profits(size(prices), 0);
    double min_price_so_far = numeric_limits<double>::max();
    // buy and sell on ith day on the forward pass
    for (int i = 0; i < size(prices); ++i) {
        min_price_so_far = min(min_price_so_far, prices[i]);
        max_total_profit = max(max_total_profit, prices[i] - min_price_so_far);
        first_buy_sell_profits[i] = max_total_profit;
    }
    // buy on ith day on the second pass.. sell at max retroactively
    double max_price_so_far = numeric_limits<double>::min();
    for (int i = size(prices) - 1; i > 0; --i) {
        max_price_so_far = max(max_price_so_far, prices[i]);
        // either do nothing.. or execute best trade on ith day forward + best trade up to i-1th day
        max_total_profit = max(max_total_profit, max_price_so_far-prices[i] + first_buy_sell_profits[i-1]);
    }
    return max_total_profit;
}

//rearrange so that A0 < A1 > A2 < A3 > A4 etc..
// don't need to do a TOTAL sort and interweave.. instead leverage locality of the solution
// simple swap can be done as each swap would only further enhance the desired delta
// need < if ODD on ith position and > if EVEN on ith position

void Rearrange(vector<int>* A_ptr) {
    vector<int>& A = *A_ptr;
    for (size_t i = 1; i < size(A); ++i) {
        if ((!(i%2) && A[i-1] < A[i]) || ((i%2) && A[i-1] > A[i])) {
            swap(A[i-1], A[i]);
        }
    }
}

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
    auto b = vector<double>{12,11,13,9,12,8,14,13,15};
    cout << BuyAndSellStockTwice(b) << endl;
    Rearrange(&m);
    for (int i : m) {
        cout << i << ", ";
    }
    cout << endl;
}