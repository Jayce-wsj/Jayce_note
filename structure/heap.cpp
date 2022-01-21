#include <iostream>
#include <vector>
#include <deque>
#include <stack>
using namespace std;

void heap_Down(vector<int> &nums, int i) {
    while (i < nums.size()) {
        int left = i*2+1;
        int right = i*2+2;
        int maxium = i;
        if (left < nums.size() && nums[maxium] < nums[left]) {
            maxium = left;
        }
        if (right < nums.size() && nums[maxium] < nums[right]) {
            maxium = right;
        }
        if (maxium == i) {
            break;
        }
        int tmp = nums[i];
        nums[i] = nums[maxium];
        nums[maxium] = tmp;
        i = maxium;
    }
}

void make_heap(vector<int> &nums) {
    for (int i = nums.size()/2 - 1; i >= 0; i--) {
        heap_Down(nums,i);
    }
}

int main() {
    vector<int>nums = {1,2,3,4,5,6,7,8,9,10};
    make_heap(nums);
    for (auto i:nums) {
        cout << " "<<i;
    }
    return 0;
}
