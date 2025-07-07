/* 703. Kth Largest Element in a Stream */

class KthLargest
{
public:
    priority_queue<int, vector<int>, greater<int>> minHeap;
    int K;

    KthLargest(int k, vector<int> &nums)
    {
        K = k;
        for (int x : nums) {
            add(x);  // 重複利用 add 處理初始化邏輯
        }
    }

    int add(int val)
    {
        minHeap.push(val);

        // 維持堆大小為 K
        if (minHeap.size() > K) {
            minHeap.pop();
        }

        return minHeap.top();  // 第 K 大的就是最小堆的 top
    }
};



/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */