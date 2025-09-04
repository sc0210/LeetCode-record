/* 973. K Closest Points to Origin */

#include <queue>
#include <vector>
using std::vector;

class Solution
{
public:
    double getDistance(int x1, int y1) { return sqrt(pow(x1, 2) + pow(y1, 2)); }

    vector<vector<int>> kClosest(vector<vector<int>> &points, int k)
    {
        using T = std::pair<double, vector<int>>;

        std::priority_queue<T, vector<T>, std::greater<T>> pq;
        for (const auto &val : points) {
            pq.push({getDistance(val[0], val[1]), val});
            // cout << val[0] << " " << val[1] << "
            // "<<getDistance(val[0],val[1]) << endl;
        }

        vector<vector<int>> res;
        while (k--) {
            res.push_back(pq.top().second);
            pq.pop();
        }
        return res;
    }
};
