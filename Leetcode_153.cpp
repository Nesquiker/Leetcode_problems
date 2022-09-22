/*
Problem Description:

153. Find Minimum in Rotated Sorted Array
Medium

Suppose an array of length n sorted in ascending order is rotated between 1 and n times. For example, the array nums = [0,1,2,4,5,6,7] might become:

[4,5,6,7,0,1,2] if it was rotated 4 times.
[0,1,2,4,5,6,7] if it was rotated 7 times.
Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

Given the sorted rotated array nums of unique elements, return the minimum element of this array.

You must write an algorithm that runs in O(log n) time.

 

Example 1:

Input: nums = [3,4,5,1,2]
Output: 1
Explanation: The original array was [1,2,3,4,5] rotated 3 times.
Example 2:

Input: nums = [4,5,6,7,0,1,2]
Output: 0
Explanation: The original array was [0,1,2,4,5,6,7] and it was rotated 4 times.
Example 3:

Input: nums = [11,13,15,17]
Output: 11
Explanation: The original array was [11,13,15,17] and it was rotated 4 times. 
 

Constraints:

n == nums.length
1 <= n <= 5000
-5000 <= nums[i] <= 5000
All the integers of nums are unique.
nums is sorted and rotated between 1 and n times.

End Description.

Problem seems trivial as it is essentially a subset of the problem "33. Search in Rotated Sorted Array".

Core Idea:

[3, 4, 0, 1, 2]

Take 0th index as temp_max = 3;
Guess middle value aka 0;

[#3, 4, $0, 1, 2]

Check if the next value is less which due to the sorted nature would mean that the next value is the minimum.
If current val is less move upper down.

[#3, $4, 0, 1, 2]
And so forth.

Time Complexity - O(log(n)) due to the binary search.
Space - constant.
*/

#include "doctest.h"
#include <vector>

class Solution {
public:
    int findMin(const std::vector<int>& nums) {
        int temp_max = nums[0];
        int upper = nums.size() - 1;
        int lower = 0;
        int answer = temp_max;
        while (lower <= upper) {
            int guess = (upper + lower) / 2;
            int next = guess + 1;
            if (next == nums.size()) {
                next = 0;
            }
            if (nums[next] < nums[guess]) {
                answer = nums[next];
                break;
            }
            if (temp_max <= nums[guess]) {
                lower = guess + 1;
                temp_max = nums[guess];
            } else {
                upper = guess - 1;
            }
        }
        return answer;
    }
};


TEST_CASE("153. Find Minimum in Rotated Sorted Array")
{
    Solution tester;

    std::vector<int> nums {4,5,6,7,0,1,2};
    int check = 0;
    auto answer = tester.findMin(nums);
    CHECK(answer == check);

    nums = {3,4,5,1,2};
    check = 1;
    answer = tester.findMin(nums);
    CHECK(answer == check);

    nums = {11,13,15,17};
    check = 11;
    answer = tester.findMin(nums);
    CHECK(answer == check);

    nums = {18,11,13,15,17};
    check = 11;
    answer = tester.findMin(nums);
    CHECK(answer == check);

    nums = {11,13,15,17, 10};
    check = 10;
    answer = tester.findMin(nums);
    CHECK(answer == check);

    nums = {0};
    check = 0;
    answer = tester.findMin(nums);
    CHECK(answer == check);

    nums = {3300, 5000, -3000, -2000, -1, 0, 1, 2, 3, 4, 3000};
    check = -3000;
    answer = tester.findMin(nums);
    CHECK(answer == check);

}
