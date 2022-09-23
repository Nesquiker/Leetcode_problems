/*
1680. Concatenation of Consecutive Binary Numbers
Medium

Given an integer n, return the decimal value of the binary string formed by concatenating the binary representations of 1 to n in order, modulo 109 + 7.

 

Example 1:

Input: n = 1
Output: 1
Explanation: "1" in binary corresponds to the decimal value 1. 
Example 2:

Input: n = 3
Output: 27
Explanation: In binary, 1, 2, and 3 corresponds to "1", "10", and "11".
After concatenating them, we have "11011", which corresponds to the decimal value 27.
Example 3:

Input: n = 12
Output: 505379714
Explanation: The concatenation results in "1101110010111011110001001101010111100".
The decimal value of that is 118505380540.
After modulo 109 + 7, the result is 505379714.
 

Constraints:

1 <= n <= 105

End.

Interesting problem. The pattern came to me fairly quickly, the only stumbling block was that I did not understand that modulo 1e9 + 7 would essentially shift the 
bits back so to speak. So I wasted some time looking for a way to make bigints. Still came back around to the algorithm below fairly quickly. 

Steps:
1. Find number of left shifts which is pretty conveniently deduced by taking the base 2 log (floored as an int).
2. Add the number.
3. Modulo the number repeatedly to keep it from overflowing.

Time complexity: O(n)

*/
#include "doctest.h"
#include <cmath>


class Solution {
public:
    int concatenatedBinary(int n) {
        long long output = 0;
        int modulo = 1e9 + 7;
        for (int i = 1; i < n + 1; i++) {
            int shift = std::log2(i) + 1;
            output <<= shift;
            output += i;
            output %= modulo;
        }
        return output;
    }
};


TEST_CASE("1680. Concatenation of Consecutive Binary Numbers")
{
    Solution tester;

    int num = 1;
    int check = 1;
    auto answer = tester.concatenatedBinary(num);
    CHECK(answer == check);

    num = 3;
    check = 27;
    answer = tester.concatenatedBinary(num);
    CHECK(answer == check);

    num = 12;
    check = 505379714;
    answer = tester.concatenatedBinary(num);
    CHECK(answer == check);

}
