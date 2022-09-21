/* 

Problem description:

You are given an integer array nums and an array queries where queries[i] = [vali, indexi].

For each query i, first, apply nums[indexi] = nums[indexi] + vali, then print the sum of the even values of nums.

Return an integer array answer where answer[i] is the answer to the ith query.

 

Example 1:

Input: nums = [1,2,3,4], queries = [[1,0],[-3,1],[-4,0],[2,3]]
Output: [8,6,2,4]
Explanation: At the beginning, the array is [1,2,3,4].
After adding 1 to nums[0], the array is [2,2,3,4], and the sum of even values is 2 + 2 + 4 = 8.
After adding -3 to nums[1], the array is [2,-1,3,4], and the sum of even values is 2 + 4 = 6.
After adding -4 to nums[0], the array is [-2,-1,3,4], and the sum of even values is -2 + 4 = 2.
After adding 2 to nums[3], the array is [-2,-1,3,6], and the sum of even values is -2 + 6 = 4.
Example 2:

Input: nums = [1], queries = [[4,0]]
Output: [0]
 

Constraints:

1 <= nums.length <= 104
-104 <= nums[i] <= 104
1 <= queries.length <= 104
-104 <= vali <= 104
0 <= indexi < nums.length

Description end.

This problem seems very simple for a leetcode medium. The one issue you could run into when solving it would be by 
trying to recalculate the sum of even numbers over the entire nums array instead of simply modifying the sum of evens
with the single value being accessed. The first strategy would be O(n**2) where the second would be O(n).

The steps for the O(n) solution:
1. Find the sum of all even values in the nums array.
2. Iterate over all queries using an index.
3. Subtract the currently queried value from the sum of even numbers if it is even.
4. Add the query val to the current nums val.
5. If the current nums val is even add it to the current sum of even numbers.
6. Log the current sum to the answers array.

Code in C++ below using the doctest module for testing:
*/



#include "doctest.h"
#include <vector>


Solution {
public:
    std::vector<int> sumEvenAfterQueries(std::vector<int>& nums, std::vector<std::vector<int>>& queries) {
        int even_sum = 0;

        // Find the initial sum of all even numbers.
        for (int num : nums) {
            if (!(num & 1)) {
                even_sum += num;
            }
        }

        std::vector<int> answers (queries.size());
        for (int i = 0; i < queries.size(); i++) {
            int query_index = queries[i].back();

            // If even remove the current value being changed as it is currently a part of the current even sum.
            if (!(nums[query_index] & 1)) {
                even_sum -= nums[query_index];
            }

            // If new value is even add it back to the current even sum then log the answer.
            nums[query_index] += queries[i].front();
            if (!(nums[query_index] & 1)) {
                even_sum += nums[query_index];
            }
            answers[i] = even_sum;
        }
        return answers;
    }
};


TEST_CASE("Leetcode 985 - Sum after queries")
{
    Solution tester;

    std::vector<int> nums1 {1,2,3,4};
    std::vector<std::vector<int>> queries {{1,0},{-3,1},{-4,0},{2,3}};
    std::vector<int> check {8,6,2,4};
    auto answer = tester.sumEvenAfterQueries(nums1, queries);
    CHECK(answer == check);

    nums1 = {1};
    queries = {{4,0}};
    check = {0};
    answer = tester.sumEvenAfterQueries(nums1, queries);
    CHECK(answer == check);

}
