/*
Problem description:
Write an efficient algorithm that searches for a value target in an m x n integer matrix matrix. This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.

End Description.

This problem requires us to find a specific value in a sorted matrix where each row is greater than the last and each row is sorted.
The key to an optimal solution here is the sorted characteristic. If the data is sorted we can use a logarithmic finding algorithm such 
as a binary search. The following algorithm should operate in O(logn) time.

1. Do a binary search of the beginnings of every row to find which row the target value may reside.
2. Do a binary search of the targot row for the target value.
3. Return the location. If we have a location return true else false.

*/



#include <vector>


class Solution {
public:
    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
      // The problem decription wants a bool but I had the info for the location available so just decided to record
      // it as it seemed a better algorithm with the location. No other reason.
        std::vector<int> points = BinarySearch(matrix, target);
        return !points.empty();
    }

private:
    std::vector<int> BinarySearch(const std::vector<std::vector<int>>& matrix, const int target) {
      
        // Doing a binary search on the first values of every row.
        int lower = 0;
        int upper = matrix.size() - 1;
        while (lower <= upper) {
            int mid_point = (upper + lower) / 2;

            if (matrix[mid_point].front() == target) {
              return {mid_point, 0};
            }

            if (matrix[mid_point].front() < target) {
                lower = mid_point + 1;
            } else {
                upper = mid_point - 1;
            }
        }
        
        // This relationship is interesting. Whenever the value is not found the value of the upper index is guaranteed to point to the row before the row with
        // a beginning value above the target value. This happens to be the row where our value will be located unless it does not exist. -1 means that the value 
        // does not exist.
        const int row = upper;
        if (row == -1) return {};
      
        // Binary search on the row which may or may not contain the value.
        upper = matrix[row].size() - 1;
        lower = 1;
        while (lower <= upper) {
            int mid_point = (upper + lower) / 2;

            if (matrix[row][mid_point] == target) {
              return {row, mid_point};
            }

            if (matrix[row][mid_point] < target) {
                lower = mid_point + 1;
            } else {
                upper = mid_point - 1;
            }
        }
        return {};

    }
};
