#include <unordered_map>
#include <vector>


int findLucky(std::vector<int> &arr)
{
    // use hashmap to traverse O(n)
    std::unordered_map<int, int> hp;
    for (int val : arr) {
        if (hp.count(val)) {
            hp[val]++;
        } else {
            hp[val] = 1;
        }
    }

    int maxVal = -1;
    for (auto val : hp) {
        if (val.first == val.second && val.first > maxVal) {
            maxVal = val.first;
        };
    }
    return maxVal;
}