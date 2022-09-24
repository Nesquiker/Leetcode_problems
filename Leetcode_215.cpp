/*
215. Kth Largest Element in an Array
Medium

Given an integer array nums and an integer k, return the kth largest element in the array.

Note that it is the kth largest element in the sorted order, not the kth distinct element.

You must solve it in O(n) time complexity.

 

Example 1:

Input: nums = [3,2,1,5,6,4], k = 2
Output: 5
Example 2:

Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
Output: 4
 

Constraints:

1 <= k <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4
End.

Medium difficulty is a stretch. When they said O(n) time did they actually mean to use a frequency array? 
I think they did even though it seems a poor fit given the provided constraints.
I used a priority queue for O(nlog(k)) which performed at the 93rd percentile speed wise. Algorithm is obvious, I'll leave it at that.

*/

#include <queue>
#include <vector>


class Solution {
public:
    int findKthLargest(std::vector<int>& nums, int k) {
        std::priority_queue k_largest (nums.begin(), nums.begin() + k, std::greater<>());
        for (int i = k; i < nums.size(); i++) {
            if (nums[i] > k_largest.top()) {
                k_largest.pop();
                k_largest.push(nums[i]);
            }
        }
        return k_largest.top();
    }
};
