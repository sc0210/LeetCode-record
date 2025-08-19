#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <vector>

void bubbleSort(std::vector<int> &);
void selectionSort(std::vector<int> &);
void insertSort(std::vector<int> &);

void mergerSort(std::vector<int> &, int l, int r);
void mergerSortBottomup(std::vector<int> &nums);
void merge(std::vector<int> &, int l, int m, int r);
void quickSort(std::vector<int> &, int l, int r);
int partition(std::vector<int> &, int l, int r);

void printVec(std::vector<int> &nums);
bool Check(std::vector<int> nums, std::vector<int> sol);
void reset(std::vector<int> &, std::vector<int> &);

int main()
{
    // random create testcase
    long long N = rand() % INT_MAX;
    std::vector<int> testcase(N);
    std::vector<int> t(N);
    for (int i = 0; i < N; i++)
        testcase[i] = rand() % 1000;
    // printVec(testcase);
    reset(t, testcase);

    // bubbleSort, insertSort, selectionSort
    std::cout << "bubbleSort: ";
    reset(t, testcase);
    bubbleSort(t);
    Check(testcase, t);

    std::cout << "insertSort: ";
    reset(t, testcase);
    insertSort(t);
    Check(testcase, t);

    std::cout << "selectionSort: ";
    reset(t, testcase);
    selectionSort(t);
    Check(testcase, t);

    // mergerSort, mergerSortBottomup, quickSort
    std::cout << "mergerSort: ";
    reset(t, testcase);
    mergerSort(t, 0, t.size() - 1);
    Check(testcase, t);

    std::cout << "mergerSortBottomup: ";
    reset(t, testcase);
    mergerSortBottomup(t);
    Check(testcase, t);

    std::cout << "quickSort: ";
    reset(t, testcase);
    quickSort(t, 0, t.size() - 1);
    Check(testcase, t);

    return 0;
}

void bubbleSort(std::vector<int> &nums)
{
    // in each iteration, compare the neighbor value
    for (int i = 0; i < nums.size(); i++) {
        for (int j = i + 1; j < nums.size(); j++) {
            if (nums[i] > nums[j]) {
                std::swap(nums[i], nums[j]);
            }
        }
    }
}

void selectionSort(std::vector<int> &nums)
{
    // in each iteration, select the minimal value
    for (int i = 0; i < nums.size(); i++) {
        int minIndex = i;
        for (int j = i + 1; j < nums.size(); j++) {
            if (nums[minIndex] > nums[j]) {
                minIndex = j;
            }
        }
        std::swap(nums[i], nums[minIndex]);
    }
}

void insertSort(std::vector<int> &nums)
{
    // in each iteration, insert the value in the right position
    for (int i = 1; i < nums.size(); i++) {
        int key = nums[i];
        int j = i - 1;
        // shift the larger value to the next index
        while (j >= 0 && nums[j] > key) {
            nums[j + 1] = nums[j];
            j--;
        }
        nums[j + 1] = key;
    }
};

void mergerSort(std::vector<int> &nums, int l, int r)
{
    // termination
    if (l >= r)
        return;
    int m = l + (r - l) / 2;

    // Divide and conquer
    mergerSort(nums, l, m);
    mergerSort(nums, m + 1, r);
    merge(nums, l, m, r);
}

void merge(std::vector<int> &nums, int l, int m, int r)
{
    std::vector<int> L(nums.begin() + l, nums.begin() + m + 1);
    std::vector<int> R(nums.begin() + m + 1, nums.begin() + r + 1);

    int i = 0, j = 0, k = l;
    // both exist value to merge
    while (i < L.size() && j < R.size()) {
        if (L[i] <= R[j])
            nums[k++] = L[i++];
        else
            nums[k++] = R[j++];
    }

    // only either one exist value to merge
    while (i < L.size())
        nums[k++] = L[i++];
    while (j < R.size())
        nums[k++] = R[j++];
}

void mergerSortBottomup(std::vector<int> &nums)
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

int partition(std::vector<int> &nums, int l, int r)
{
    int piv = nums[r];
    int i = l - 1;

    for (int j = l; j < r; j++) {
        if (nums[j] <= piv) {
            i++;
            std::swap(nums[i], nums[j]);
        }
    }
    std::swap(nums[i + 1], nums[r]);
    return i + 1;
}

void quickSort(std::vector<int> &nums, int l, int r)
{
    if (l < r) {
        int pivot = partition(nums, l, r);
        quickSort(nums, l, pivot - 1);
        quickSort(nums, pivot + 1, r);
    }
}

void printVec(std::vector<int> &nums)
{
    for (int i = 0; i < nums.size(); i++) {
        std::cout << nums[i] << " ";
        if (i > 0 && i % 20 == 0)
            std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool Check(std::vector<int> nums, std::vector<int> sol)
{
    std::vector<int> ans(nums.begin(), nums.end());
    std::sort(ans.begin(), ans.end());
    bool res = (ans == sol);
    if (res)
        std::cout << "Sorted\n";
    else
        std::cout << "NotSorted\n";

    return ans == sol;
}

void reset(std::vector<int> &t, std::vector<int> &testcase)
{
    for (int i = 0; i < testcase.size(); i++) {
        t[i] = testcase[i];
    }
}
