/*
1046. Last Stone Weight
Easy

You are given an array of integers stones where stones[i] is the weight of the ith stone.

We are playing a game with the stones. On each turn, we choose the heaviest two stones and smash 
them together. Suppose the heaviest two stones have weights x and y with x <= y. The result of this smash is:

If x == y, both stones are destroyed, and
If x != y, the stone of weight x is destroyed, and the stone of weight y has new weight y - x.
At the end of the game, there is at most one stone left.

Return the weight of the last remaining stone. If there are no stones left, return 0.

 

Example 1:

Input: stones = [2,7,4,1,8,1]
Output: 1
Explanation: 
We combine 7 and 8 to get 1 so the array converts to [2,4,1,1,1] then,
we combine 2 and 4 to get 2 so the array converts to [2,1,1,1] then,
we combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
we combine 1 and 1 to get 0 so the array converts to [1] then that's the value of the last stone.
Example 2:

Input: stones = [1]
Output: 1
 

Constraints:

1 <= stones.length <= 30
1 <= stones[i] <= 1000

End description.

Nothing to say. Simple application of a priority queue.

*/

#include <queue>
#include <vector>


class Solution {
public:
    int lastStoneWeight(std::vector<int>& stones) {
        std::priority_queue<int> stone_stack (stones.begin(), stones.end());
        int output = 0;
        while (stone_stack.size() > 1) {
            int stone_1 = stone_stack.top();
            stone_stack.pop();
            int stone_2 = stone_stack.top();
            stone_stack.pop();
            if (stone_1 != stone_2) {
                stone_stack.push(stone_1 - stone_2);
            }
        }
        if (!stone_stack.empty()) {
            output = stone_stack.top();
        }
        return output;
    }
};
