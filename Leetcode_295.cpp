/*
295. Find Median from Data Stream
Hard

The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value and the median 
is the mean of the two middle values.

For example, for arr = [2,3,4], the median is 3.
For example, for arr = [2,3], the median is (2 + 3) / 2 = 2.5.
Implement the MedianFinder class:

MedianFinder() initializes the MedianFinder object.
void addNum(int num) adds the integer num from the data stream to the data structure.
double findMedian() returns the median of all elements so far. Answers within 10-5 of the actual answer will be accepted.
 

Example 1:

Input
["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
[[], [1], [2], [], [3], []]
Output
[null, null, null, 1.5, null, 2.0]

Explanation
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.addNum(2);    // arr = [1, 2]
medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
medianFinder.addNum(3);    // arr[1, 2, 3]
medianFinder.findMedian(); // return 2.0
 

Constraints:

-105 <= num <= 105
There will be at least one element in the data structure before calling findMedian.
At most 5 * 104 calls will be made to addNum and findMedian.
 

Follow up:

If all integer numbers from the stream are in the range [0, 100], how would you optimize your solution?
If 99% of all integer numbers from the stream are in the range [0, 100], how would you optimize your solution?
END.

Definetly an easier hard problem. My solution was to make two priority queues one max queue and one min queue containing the smaller values and the larger values
respectively. The tops of the queues then served as my median(s). Could have just as easily done this with a c++ multiset while tracking the index of
the median value. Maybe faster as there would be no rebalancing the queues. Regardless the speed of the various algos in leetcode differed between 1 - 2x which is
inconsequential normally.

Follow up questions:
1. I would utilize a frequency array in that case and query it with a combination of running sums.
2. I would have a frequency array where those less than 0 counted as 0 and those greater than 100 counted as 100.
*/

#include <queue>

class MedianFinder {
public:
    MedianFinder() {
        below_median.emplace(INT_MIN);
        above_median.emplace(INT_MAX);
    };

    void addNum(const int num) {
        last = !(last);
        if (num > below_median.top()) {
            above_median.emplace(num);
        } else {
            below_median.emplace(num);
        }
        if (abs((int)above_median.size() - (int)below_median.size()) > 1) {
            balanceQueues();
        }

    }

    double findMedian() {
        if (last) {
            return ((double)below_median.top() + above_median.top()) / 2;
        } else {
            return (below_median.size() > above_median.size()) ? below_median.top() : above_median.top();
        }

    }
private:
    bool last = true;
    std::priority_queue<int> below_median;
    std::priority_queue<int, std::vector<int>, std::greater<>> above_median;

    void balanceQueues() {
        if (below_median.size() > above_median.size()) {
            above_median.emplace(below_median.top());
            below_median.pop();
        } else {
            below_median.emplace(above_median.top());
            above_median.pop();
        }
    }

};
