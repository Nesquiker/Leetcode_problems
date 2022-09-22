/*
Problem Description:

875. Koko Eating Bananas
Medium

Share
Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. The guards have gone and will come back in h hours.

Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of bananas and eats k bananas from that pile. If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return the minimum integer k such that she can eat all the bananas within h hours.

 

Example 1:

Input: piles = [3,6,7,11], h = 8
Output: 4
Example 2:

Input: piles = [30,11,23,4,20], h = 5
Output: 30
Example 3:

Input: piles = [30,11,23,4,20], h = 6
Output: 23
 

Constraints:

1 <= piles.length <= 104
piles.length <= h <= 109
1 <= piles[i] <= 109

End Description.

The following steps were performed:

1. Sort the piles so that an std::upper_bound binary search may be performed.
2. Make a guess to the valid solution. To efficiently guess we will do so with a binary search.
3. Check the guess by seeing if it finishes over or under the required hours (h).
4. Check using upper_bound and using multiples of the current guess to track how many hours need to be spent.
5. If guess is made at or under the requisite hours record as lowest guess and make another until exit criteria is met.

Time complexity Log(h <= 10**9) (n <= 10**4) log(n)  == O(log(h)*n*log(n))
Space == constant extra space.

Notes - encountered overflow error on the last test in the test_cases. This resulted in an incorrect submission. Did not properly anticipate
that this term: #output += (upper_it - current_it) * mults_of_guess;# would overflow int as an extremely low guess with an extremely high value
was unforeseen. Need to consider adding test cases in future problems that may cause overflow.
*/

#include "doctest.h"
#include <vector>
#include <algorithm>


class Solution {
public:
    int minEatingSpeed(std::vector<int>& piles, const int h) {

        // Need sorted for binary search aka std::upper_bound.
        std::sort(piles.begin(), piles.end());

        // Setting the upper and lower bounds of the answer guessing binary search.
        int upper = piles.back();
        int lower = 1;
        int lowest_valid_guess = piles.back();
        while (lower <= upper) {
            int guess = (lower + upper) / 2;
            long long result = BinaryGuessResult(piles, guess, h);
            if (result > h) {
                lower = guess + 1;
            } else {
                lowest_valid_guess = guess;
                upper = guess - 1;
            }
        }
        return lowest_valid_guess;
    }
private:

    long long BinaryGuessResult(std::vector<int>& piles, const long long guess, const int h) {
        auto current_it = piles.begin();
        int current_guess = guess;
        int mults_of_guess = 1;
        long long output = 0;
        while (output <= h) {
            auto upper_it = std::upper_bound(current_it, piles.end(), current_guess);
            output += (upper_it - current_it) * mults_of_guess;
            if (upper_it == piles.end())
                break;
            mults_of_guess = *upper_it / guess + (*upper_it % guess != 0);
            current_guess = guess * mults_of_guess;
            current_it = upper_it;
        }
        return output;
    }

};


TEST_CASE("875. Koko Eating Bananas")
{
    Solution tester;

    std::vector<int> piles {3,6,7,11};
    int h = 8;
    int check = 4;
    auto answer = tester.minEatingSpeed(piles, h);
    CHECK(answer == check);

    piles = {30,11,23,4,20};
    h = 5;
    check = 30;
    answer = tester.minEatingSpeed(piles, h);
    CHECK(answer == check);

    piles = {30,11,23,4,20};
    h = 6;
    check = 23;
    answer = tester.minEatingSpeed(piles, h);
    CHECK(answer == check);

    piles = {1};
    h = 20;
    check = 1;
    answer = tester.minEatingSpeed(piles, h);
    CHECK(answer == check);

    piles = {20};
    h = 1;
    check = 20;
    answer = tester.minEatingSpeed(piles, h);
    CHECK(answer == check);

    piles = {99, 1, 2, 3, 1000};
    h = 10;
    check = 167;
    answer = tester.minEatingSpeed(piles, h);
    CHECK(answer == check);

    piles = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    h = 55;
    check = 1;
    answer = tester.minEatingSpeed(piles, h);
    CHECK(answer == check);

    piles = {805306368,805306368,805306368};
    h = 1000000000;
    check = 3;
    answer = tester.minEatingSpeed(piles, h);
    CHECK(answer == check);

}
