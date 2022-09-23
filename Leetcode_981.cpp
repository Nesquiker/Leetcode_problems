/*
Begin Description:

981. Time Based Key-Value Store
Medium

Design a time-based key-value data structure that can store multiple values for the same key at different time stamps and retrieve the key's value at a 
certain timestamp.

Implement the TimeMap class:

TimeMap() Initializes the object of the data structure.
void set(String key, String value, int timestamp) Stores the key key with the value value at the given time timestamp.
String get(String key, int timestamp) Returns a value such that set was called previously, with timestamp_prev <= timestamp. 
If there are multiple such values, it returns the value associated with the largest timestamp_prev. If there are no values, it returns "".
 

Example 1:

Input
["TimeMap", "set", "get", "get", "set", "get", "get"]
[[], ["foo", "bar", 1], ["foo", 1], ["foo", 3], ["foo", "bar2", 4], ["foo", 4], ["foo", 5]]
Output
[null, null, "bar", "bar", null, "bar2", "bar2"]

Explanation
TimeMap timeMap = new TimeMap();
timeMap.set("foo", "bar", 1);  // store the key "foo" and value "bar" along with timestamp = 1.
timeMap.get("foo", 1);         // return "bar"
timeMap.get("foo", 3);         // return "bar", since there is no value corresponding to foo at timestamp 3 and timestamp 2, then the only value is at timestamp 1 is "bar".
timeMap.set("foo", "bar2", 4); // store the key "foo" and value "bar2" along with timestamp = 4.
timeMap.get("foo", 4);         // return "bar2"
timeMap.get("foo", 5);         // return "bar2"
 

Constraints:

1 <= key.length, value.length <= 100
key and value consist of lowercase English letters and digits.
1 <= timestamp <= 107
All the timestamps timestamp of set are strictly increasing.
At most 2 * 105 calls will be made to set and get.

End Description.

Steps:

1. Establish data. The key reference structure is an obvious use case for an unordered_map. Initially, for the stamps per key, I was going to use std::set as I did not realize the 
   inputs came ordered which is why I ended up using a vector of pairs.
2. Append data in the set call.
3. Do a binary search for the latest timestamp <= the target timestamp. 

Time Complexity: Each set should be in constant O(1) time and each get will be in O(log(n)) time.

Didn't have much trouble with this. Didn't want to mock up tests, everything worked first time!
*/

#include <vector>
#include <unordered_map>
#include <string>

class TimeMap {
public:
    TimeMap() = default;

    void set(const std::string& key, const std::string& value, const int timestamp) {
        data[key].emplace_back(std::make_pair(timestamp, value));
    }

    std::string get(const std::string& key, const int timestamp) {
        std::string out;
        if (data.count(key) == 0) {
            return out;
        }
        int upper = data[key].size() - 1;
        int lower = 0;
        // Binary search.
        while (lower <= upper) {
            int guess = (upper + lower) / 2;
            int val = data[key][guess].first;
            if (val > timestamp) {
                upper = guess - 1;
              
              // Besides the obvious, if the next val is past the end of the array or greater than timestamp we have found the correct guess.
            } else if (val == timestamp || guess + 1 == data[key].size() || data[key][guess + 1].first > timestamp) {
                out = data[key][guess].second;
                break;
            } else {
                lower = guess + 1;
            }
        }
        return out;
    }

private:
    std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> data;
};
