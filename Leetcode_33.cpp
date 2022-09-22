/*
Problem Description:

33. Search in Rotated Sorted Array
Medium

There is an integer array nums sorted in ascending order (with distinct values).

Prior to being passed to your function, nums is possibly rotated at an unknown pivot index k (1 <= k < nums.length) such that the resulting array
is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be rotated at pivot index
3 and become [4,5,6,7,0,1,2].

Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.

You must write an algorithm with O(log n) runtime complexity.

Example 1:

Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
Example 2:

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
Example 3:

Input: nums = [1], target = 0
Output: -1
 

Constraints:

1 <= nums.length <= 5000
-104 <= nums[i] <= 104
All values of nums are unique.
nums is an ascending array that is possibly rotated.
-104 <= target <= 104

End Description.

Submission Detail
195 / 195 test cases passed.
Status: Accepted
Runtime: 3 ms
Memory Usage: 11.1 MB

Your runtime beats 89.88 % of cpp submissions.

Your memory usage beats 74.95 % of cpp submissions.

Steps:

1. Find where the largest value of the rotated array is. This requires a binary search of the array.
2. Use the location of the largest value to create a local indexing system that is consistent with the sorted
   requirement for a binary search.
3. Implement a binary search of the localized indexes and return the result in the original index system.

Took me a while to wrap my head around the binary search for the largest value in the un-rotated array. After that the next challenge was how
do we take that and get a efficient binary sort. That required the creation of a new local index system with mutation to the system and out
of the local index numbering which is solved in convert_to_base and convert_from_rot.

Time Complexity: O(log(n)) Everything that is non constant is in logn time.
Space: constant, no new arrays etc...
*/

#include "doctest.h"
#include <vector>


class Solution {
public:
    int search(const std::vector<int>& nums, const int target) {
        int upper = nums.size() - 1;
        int lower = 0;
        int curr_max = nums[0];
        int rotate_key = -1;
        
        // Binary search for the end of the sorted array before the rotation. This is going to be called
        // the rotate_key.
        while (lower <= upper) {
            int guess = (upper + lower) / 2;
            if (nums[guess] == target) {
                return guess;
            }
            int next = guess + 1;
            if (next == nums.size()) {
                next = 0;
            }
            if (nums[next] < nums[guess]) {
                rotate_key = guess;
                break;
            }
            if (nums[guess] >= curr_max) {
                curr_max = nums[guess];
                lower = guess + 1;
            } else {
                upper = guess - 1;
            }
        }
        
        // There are two helpers convert_to_base and convert_to_rot. These allow us to 
        // do a binary search on the array as if it were in the original sorted position.
        // Imagine the array with the indexes 
        // [4 -> 0, 5 -> 1, 6 -> 2, 0 -> 3, 1 -> 4, 2 -> 5, 3 -> 6] 
        // after convert to base:
        // [4 -> 7, 5 -> 8, 6 -> 9, 0 -> 3, 1 -> 4, 2 -> 5, 3 -> 6] 
        // In an index sorted order (for visualization only we don't do a sort):
        // [0 -> 3, 1 -> 4, 2 -> 5, 3 -> 6, 4 -> 7, 5 -> 8, 6 -> 9] 
        // Then convert back after potentially finding the val.
        upper = convert_to_base(rotate_key, rotate_key, nums.size());
        if (rotate_key == nums.size()) {
            lower = 0;
        } else {
            lower = rotate_key + 1;
        }
        lower = convert_to_base(lower, rotate_key, nums.size());
        // Binary search.
        while (lower <= upper) {
            int guess = (upper + lower) / 2;
            int guess_val = nums[convert_from_rot(guess, nums.size())];
            if (guess_val == target) {
                return convert_from_rot(guess, nums.size());
            }
            if (guess_val > target) {
                upper = guess - 1;
            } else {
                lower = lower + 1;
            }
        }
        return -1;
    }
private:
    int convert_to_base(const int input, const int key, const int nums_end) {
        int output = input;
        if (input <= key) {
            output = nums_end + input;
        }
        return output;
    }
    int convert_from_rot(const int input, const int nums_end) {
        int output = input;
        if (input >= nums_end) {
            output = input - nums_end;
        }
        return output;
    }

TEST_CASE("33. Search in Rotated Sorted Array")
{
    Solution tester;

    std::vector<int> nums {4,5,6,7,0,1,2};
    int target = 0;
    int check = 4;
    auto answer = tester.search(nums, target);
    CHECK(answer == check);

    nums = {4,5,6,7,0,1,2};
    target = 3;
    check = -1;
    answer = tester.search(nums, target);
    CHECK(answer == check);

    nums = {1};
    target = 0;
    check = -1;
    answer = tester.search(nums, target);
    CHECK(answer == check);

    nums = {1};
    target = 1;
    check = 0;
    answer = tester.search(nums, target);
    CHECK(answer == check);

    nums = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    target = 0;
    check = 0;
    answer = tester.search(nums, target);
    CHECK(answer == check);

    nums = {8, 9, 2, 3, 4};
    target = 9;
    check = 1;
    answer = tester.search(nums, target);
    CHECK(answer == check);

}
