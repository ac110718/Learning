#include<iostream>
#include<vector>
#include<random>

using namespace std;

// pick random k elements from vector
// for each i.. pick uniform random from range i.. end.. and swap into 1.. kth position
void RandomSampling(int k, vector<int>* A_ptr) {
    vector<int>& A = *A_ptr;
    default_random_engine seed((random_device())());
    for (int i = 0; i < k; i++) {
        swap(A[i], A[uniform_int_distribution<int>{i, static_cast<int>(A.size()) - 1}(seed)]);
    }
}

// pick random k elements from an ongoing stream..
// generate random num from 1... n (size of stream)
// if falls within 1.. k (desired set size), then swap newest element with kth element in set
// will swap out each kth element with decreasing probability as time goes on..
// like initiate swap with 3/4th prob.. 3 / 5.. 3 / 6.. 3 / 7 etc

vector<int> OnlineRandomSample(vector<int>::const_iterator stream_begin, const vector<int>::const_iterator stream_end, int k) {
    //populate with first k elements 
    vector<int> running_sample;
    for (int i = 0; i < k; i++) {
        running_sample.emplace_back(*stream_begin++);
    }

    default_random_engine seed((random_device())());

    int num_read_so_far = k;
    while (stream_begin != stream_end) {
        int x = *stream_begin++;
        num_read_so_far++;
        // if random int from 1.. n.. is < k.. kth element is newest element (x)
        if (const int idx_to_replace = uniform_int_distribution<int>{0, num_read_so_far-1}(seed); idx_to_replace < k) {
            running_sample[idx_to_replace] = x;
        }
    }
    return running_sample;
};

int main() {
    auto a = vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    RandomSampling(3, &a);
    for (int i : a) {
        cout << i << ", ";
    }
    cout << endl;
}