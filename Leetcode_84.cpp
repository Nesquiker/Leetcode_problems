/*
84. Largest Rectangle in Histogram
Hard

Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.

Example 1:
Input: heights = [2,1,5,6,2,3]
Output: 10
Explanation: The above is a histogram where width of each bar is 1.
The largest rectangle is shown in the red area, which has an area = 10 units.
Example 2:
Input: heights = [2,4]
Output: 4
 

Constraints:
1 <= heights.length <= 105
0 <= heights[i] <= 104
END

This problem is basically a combination of two monotonic decreasing stacks. One read from the front and one from the back of the input vector.
Time Complexity - A monotonic stack is linear in time and a the core loop is linear so O(n) time.
Space - O(n) because the monotonic stacks are linear extra space.

*/
#include "doctest.h"
#include <vector>
#include <stack>
#include <math>


class Solution {
public:
    int largestRectangleArea(std::vector<int>& heights) {
        const std::vector<int> decreasing_mono_forward = makeMonoStack(heights, true);
        const std::vector<int> decreasing_mono_reversed = makeMonoStack(heights, false);
        int running_max = INT_MIN;
        for (int i = 0; i < decreasing_mono_forward.size(); i++) {
            // The monotonic stacks are inclusive of end values. This results in an off by one if we don't subtract one.
            const int val = heights[i] * (decreasing_mono_forward[i] - decreasing_mono_reversed[i] - 1);
            running_max = std::max(running_max, val);
        }
        return running_max;
    }
private:
    static std::vector<int> makeMonoStack(const std::vector<int>& heights, const bool is_forward) {
        // Uses a decreasing monotonic stack algorithm to find the next smaller index from every point.
        // There is also the added functionality to read the heights vector from right to left depending on
        // the is_forward boolean flag.
        std::stack<int> mono_stack;
        int index = 0;
        int index_change = 1;
        int end_point = (int)heights.size();

        // This allows us to create the monotonic stack as if we are travelling from the end of the heights vector
        // instead of the front. This creates a very well suited data structure when we do the core processes.
        if (!is_forward) {
            index = (int)heights.size() - 1;
            index_change = -1;
            end_point = -1;
        }

        std::vector<int> output (heights.size(), end_point);
        // Decreasing monotonic stack algorithm.
        while (index < heights.size() && index > -1) {
            while (!mono_stack.empty() && heights[mono_stack.top()] > heights[index]) {
                output[mono_stack.top()] = index;
                mono_stack.pop();
            }
            mono_stack.push(index);
            index += index_change;
        }
        return output;
    }
};


TEST_CASE("84. Largest Rectangle in Histogram")
{
    Solution tester;
    std::vector<int> heights {2,1,5,6,2,3};

    int ans = 10;
    int answer = tester.largestRectangleArea(heights);
    CHECK(ans == answer);


    heights = {2,4};
    ans = 4;
    answer = tester.largestRectangleArea(heights);
    CHECK(ans == answer);

    heights = {0};
    ans = 0;
    answer = tester.largestRectangleArea(heights);
    CHECK(ans == answer);

    heights = {1,2,3,4,5};
    ans = 9;
    answer = tester.largestRectangleArea(heights);
    CHECK(ans == answer);

    heights = {5,4,3,2,1};
    ans = 9;
    answer = tester.largestRectangleArea(heights);
    CHECK(ans == answer);

    heights = {5,4,3,3,3,3,3,3,4,5};
    ans = 30;
    answer = tester.largestRectangleArea(heights);
    CHECK(ans == answer);

    heights = {1,2,3,4,5,4,3,2,1};
    ans = 15;
    answer = tester.largestRectangleArea(heights);
    CHECK(ans == answer);

    heights = {2,1,2};
    ans = 3;
    answer = tester.largestRectangleArea(heights);
    CHECK(ans == answer);

    heights = {4,2,0,3,2,5};
    ans = 6;
    answer = tester.largestRectangleArea(heights);
    CHECK(ans == answer);


}
