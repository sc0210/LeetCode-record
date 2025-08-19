/* 912. Sort an Array */
#include <vector>
using std::vector;

class Solution
{
public:
    vector<int> sortArray(vector<int> &nums)
    {
        int N = nums.size();
        mergeSort(nums, 0, N - 1);
        mergeSortBottomUp(nums);
        return nums;
    }

private:
    void merge(vector<int> &arr, int l, int m, int r)
    {
        vector<int> L(arr.begin() + l, arr.begin() + m + 1);
        vector<int> R(arr.begin() + m + 1, arr.begin() + r + 1);

        int i = 0, j = 0, k = l;

        while (i < L.size() && j < R.size()) {
            if (L[i] <= R[j])
                arr[k++] = L[i++];
            else
                arr[k++] = R[j++];
        }

        while (i < L.size())
            arr[k++] = L[i++];
        while (j < R.size())
            arr[k++] = R[j++];
    }

    void mergeSort(vector<int> &arr, int l, int r)
    {
        if (l >= r)
            return;
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }

    void mergeSortBottomUp(vector<int> &arr)
    {
        int n = arr.size();
        // unit size to merge
        for (int sz = 1; sz < n; sz *= 2) {
            /*
                l  ....  m  ....  r
                |<- sz ->|<- sz ->|
            */
            for (int l = 0; l + sz < n; l += 2 * sz) {
                int m = l + sz - 1;
                int r = std::min(l + 2 * sz - 1, n - 1);
                merge(arr, l, m, r);
            }
        }
    }
};