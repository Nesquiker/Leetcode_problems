/*
Begin Description:

703. Kth Largest Element in a Stream
Easy

Design a class to find the kth largest element in a stream. Note that it is the kth largest element in the sorted order, not the kth distinct element.

Implement KthLargest class:

KthLargest(int k, int[] nums) Initializes the object with the integer k and the stream of integers nums.
int add(int val) Appends the integer val to the stream and returns the element representing the kth largest element in the stream.
 

Example 1:

Input
["KthLargest", "add", "add", "add", "add", "add"]
[[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
Output
[null, 4, 5, 5, 8, 8]

Explanation
KthLargest kthLargest = new KthLargest(3, [4, 5, 8, 2]);
kthLargest.add(3);   // return 4
kthLargest.add(5);   // return 5
kthLargest.add(10);  // return 5
kthLargest.add(9);   // return 8
kthLargest.add(4);   // return 8
 

Constraints:

1 <= k <= 104
0 <= nums.length <= 104
-104 <= nums[i] <= 104
-104 <= val <= 104
At most 104 calls will be made to add.
It is guaranteed that there will be at least k elements in the array when you search for the kth element.

End Description.

The problem is basically to use a heap of k values. The heap should be a min heap and return the smallest value. The only thing that might get someone
would be the null case where they do not initialize with any values. If you were to intitialize your heap / priority queue like I did that would lead
to an error. Because of this I added minimum integers to nums. The algorithm still got 83% on speed with this, maybe because I didn't need to check the size of the 
heap on every add.

Note:
There must be a better way of instantiating m_largest than making k_largest and copying it... I guess just loop through nums and push to m_largest directly.
I wonder if that is even more efficient?

Steps:

1. Add minimum ints until there are k elements in nums.
2. Sort nums.
3. Create priority_queue.
4. Make adds (just use the queue).

Time complexity: O(nlogn) for the setup, O(logn) for add.
Space: k extra space.

*/

#include <algorithm>
#include <vector>
#include <queue>


class KthLargest {
public:
    KthLargest(int k, std::vector<int>& nums) {
        // The problem descripton stated that an add will never be done in a case where an 
        // nth largest does not exist. Because of this we can just fill nums to k to avoid
        // any errors in the setup of the priority queue.
        if (k > nums.size()) {
            for (int i = nums.size(); i < k; i++) {
                nums.emplace_back(INT_MIN);
            }
        }
        std::sort(nums.begin(), nums.end(), std::greater<>());

        // Not a great method
        std::priority_queue k_largest (nums.begin(), nums.begin() + k, std::greater<>());
        m_largest = k_largest;

    }

    int add(int val) {
        if (val > m_largest.top()) {
            m_largest.pop();
            m_largest.push(val);
        }
        return m_largest.top();
    }
private:
    std::priority_queue<int, std::vector<int>, std::greater<>> m_largest;
};
