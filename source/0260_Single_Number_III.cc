#include <vector>

class Solution
{
public:
    std::vector<int> singleNumber(std::vector<int> &nums)
    {
        // Method1: brute force

        // Method2: hashmap
        // unordered_map<int, int> frequencyMap;
        // // Build the frequency map
        // for (int num : nums) {
        //     frequencyMap[num]++;
        // }

        // // Find the elements that appear only once
        // std::vector<int> result;
        // for (const auto& entry : frequencyMap) {
        //     if (entry.second == 1) {
        //         result.push_back(entry.first);
        //     }
        // }
        // return result;

        // Method3: bitwise operation
        int xor2no = 0;
        for (int num : nums) {
            xor2no ^= num;
        }

        // Cast xor2no to unsigned to avoid undefined behavior with -INT_MIN
        unsigned int lowestBit = xor2no & -(unsigned int) xor2no;

        std::vector<int> result(2, 0);
        for (int num : nums) {
            if ((lowestBit & num) == 0) {
                result[0] ^= num;
            } else {
                result[1] ^= num;
            }
        }

        return result;
    }
};