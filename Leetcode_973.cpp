/*
Description:
973. K Closest Points to Origin
Medium

Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane and an integer k, return the k closest points to the origin (0, 0).

The distance between two points on the X-Y plane is the Euclidean distance (i.e., √(x1 - x2)2 + (y1 - y2)2).

You may return the answer in any order. The answer is guaranteed to be unique (except for the order that it is in).

 

Example 1:


Input: points = [[1,3],[-2,2]], k = 1
Output: [[-2,2]]
Explanation:
The distance between (1, 3) and the origin is sqrt(10).
The distance between (-2, 2) and the origin is sqrt(8).
Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
We only want the closest k = 1 points from the origin, so the answer is just [[-2,2]].
Example 2:

Input: points = [[3,3],[5,-1],[-2,4]], k = 2
Output: [[3,3],[-2,4]]
Explanation: The answer [[-2,4],[3,3]] would also be accepted.
 

Constraints:

1 <= k <= points.length <= 104
-104 < xi, yi < 104

End.

Steps:
1. Decided to use multimap. Multiple keys ordered. Used an int index as value rather than copying the vector.
2. Construct the output from the multimap.
*/

class Solution {
public:
    std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>>& points, int k) {
        std::multimap<int, int> sorter;
        for (int i = 0; i < points.size(); i++) {
            int val = points[i].front() * points[i].front() + points[i].back() * points[i].back();
            sorter.emplace(val, i);
        }
        std::vector<std::vector<int>> output (k);
        auto it = sorter.begin();
        for (int i = 0; i < k; i++) {
            output[i] = points[it -> second];
            it++;
        }
        return output;
    }
};
