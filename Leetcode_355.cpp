/*
355. Design Twitter
Medium

Design a simplified version of Twitter where users can post tweets, follow/unfollow another user, and is able to see the 10 most recent tweets in the user's news feed.

Implement the Twitter class:

Twitter() Initializes your twitter object.
void postTweet(int userId, int tweetId) Composes a new tweet with ID tweetId by the user userId. Each call to this function will be made with a unique tweetId.
List<Integer> getNewsFeed(int userId) Retrieves the 10 most recent tweet IDs in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user themself. Tweets must be ordered from most recent to least recent.
void follow(int followerId, int followeeId) The user with ID followerId started following the user with ID followeeId.
void unfollow(int followerId, int followeeId) The user with ID followerId started unfollowing the user with ID followeeId.
 

Example 1:

Input
["Twitter", "postTweet", "getNewsFeed", "follow", "postTweet", "getNewsFeed", "unfollow", "getNewsFeed"]
[[], [1, 5], [1], [1, 2], [2, 6], [1], [1, 2], [1]]
Output
[null, null, [5], null, null, [6, 5], null, [5]]

Explanation
Twitter twitter = new Twitter();
twitter.postTweet(1, 5); // User 1 posts a new tweet (id = 5).
twitter.getNewsFeed(1);  // User 1's news feed should return a list with 1 tweet id -> [5]. return [5]
twitter.follow(1, 2);    // User 1 follows user 2.
twitter.postTweet(2, 6); // User 2 posts a new tweet (id = 6).
twitter.getNewsFeed(1);  // User 1's news feed should return a list with 2 tweet ids -> [6, 5]. Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
twitter.unfollow(1, 2);  // User 1 unfollows user 2.
twitter.getNewsFeed(1);  // User 1's news feed should return a list with 1 tweet id -> [5], since user 1 is no longer following user 2.
 

Constraints:

1 <= userId, followerId, followeeId <= 500
0 <= tweetId <= 104
All the tweets have unique IDs.
At most 3 * 104 calls will be made to postTweet, getNewsFeed, follow, and unfollow.
End.

The calls to news_feed are... special. Sorry if anyone ever reads this. By the time I put it all together I was convinced that something had to be wrong. Somehow
it passed the leetcode checker first time, thank god for small miracles. 
*/


class Twitter {
public:
    Twitter() = default;

    void postTweet(int userId, int tweetId) {
        std::vector<int> tweet {time, tweetId};
        news_feed[userId].emplace_back(tweet);
        time++;
    }

    std::vector<int> getNewsFeed(int userId) {
        std::vector<int> followees (following[userId].begin(), following[userId].end());
        followees.emplace_back(userId);
        std::vector<int> position_f (followees.size(), 0);
        std::vector<int> output;
        std::priority_queue<std::pair<int, std::pair<int, int>>> feed_sorter;
        for (int i = 0; i < followees.size(); i++) {
            if (news_feed[followees[i]].size() > position_f[i]) {
                std::pair<int, std::pair<int, int>> feed_data;
                feed_data.first = news_feed[followees[i]][news_feed[followees[i]].size() - position_f[i] - 1].front();
                feed_data.second = std::make_pair(i, news_feed[followees[i]][news_feed[followees[i]].size() - position_f[i] - 1].back());
                feed_sorter.emplace(feed_data);
            }
        }
        while (output.size() < 10 && !feed_sorter.empty()) {
            auto feed = feed_sorter.top().second;
            feed_sorter.pop();
            output.emplace_back(feed.second);
            position_f[feed.first]++;
            if (news_feed[followees[feed.first]].size() > position_f[feed.first]) {
                std::pair<int, std::pair<int, int>> feed_data;
                feed_data.first = news_feed[followees[feed.first]][news_feed[followees[feed.first]].size() - 1 - position_f[feed.first]].front();
                feed_data.second = std::make_pair(feed.first,
                                                  news_feed[followees[feed.first]][news_feed[followees[feed.first]].size() - 1 - position_f[feed.first]].back());
                feed_sorter.emplace(feed_data);
            }
        }
        return output;
    }

    void follow(int followerId, int followeeId) {
        following[followerId].insert(followeeId);
    }

    void unfollow(int followerId, int followeeId) {
        following[followerId].erase(followeeId);
    }
private:
    std::unordered_map<int, std::vector<std::vector<int>>> news_feed;
    std::unordered_map<int, std::unordered_set<int>> following;
    int time = 0;
};
