#include <iostream>
#include <vector>


using std::cout;
using std::vector;

void merge(vector<int> &, int, int, int);
void mergesort(vector<int> &, int, int);
void mergesortBottom(vector<int> &nums);

int main()
{
    vector<int> testcase = {5, 4, 1, 2, 3};
    for (const auto &val : testcase) {
        cout << val << " ";
    }
    cout << std::endl;
    // mergesort(testcase, 0, testcase.size() - 1);
    mergesortBottom(testcase);
    for (const auto &val : testcase) {
        cout << val << " ";
    }

    return 0;
}

void merge(vector<int> &nums, int l, int m, int r)
{
    vector<int> L(nums.begin() + l, nums.begin() + m + 1);
    vector<int> R(nums.begin() + m + 1, nums.begin() + r + 1);

    int i = 0, j = 0, k = l;
    while (i < L.size() && j < R.size()) {
        if (L[i] <= R[j])
            nums[k++] = L[i++];
        else
            nums[k++] = R[j++];
    }
    while (i < L.size())
        nums[k++] = L[i++];
    while (j < R.size())
        nums[k++] = R[j++];
};


void mergesort(vector<int> &nums, int l, int r)
{
    if (l >= r)
        return;
    int m = l + (r - l) / 2;
    mergesort(nums, 0, m);
    mergesort(nums, m + 1, r);
    merge(nums, l, m, r);
}

void mergesortBottom(vector<int> &nums)
{
    int N = nums.size();
    for (int sz = 1; sz < N; sz *= 2) {
        for (int l = 0; l + sz < N; l += 2 * sz) {
            int m = l + sz - 1;
            int r = std::min(l + 2 * sz - 1, N - 1);
            merge(nums, l, m, r);
        }
    }
}
