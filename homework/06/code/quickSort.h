#include <iostream>
#include <vector>

using namespace std;

int QuickSort(vector<int> &nums, int left, int right, int k) {
    if (left == right) {
        return nums[left];
    }

    if (left < right) {  //快排思想 从大至小排序
        int i = left;
        int j = right;
        int key = nums[left];
        while (i < j) {
            while (i < j && nums[j] < key) j--;
            if (i < j) {
                nums[i] = nums[j];
                i++;
            }
            while (i < j && nums[i] >= key) i++;
            if (i < j) {
                nums[j] = nums[i];
                j--;
            }
        }
        // i=j退出循环
        nums[i] = key;

        //进行基准的新下标与k的比较
        if (i > k)
            return QuickSort(nums, left, i - 1, k);
        else if (i < k)
            return QuickSort(nums, i + 1, right, k);
        else
            return nums[i];
    }
}

int kthLargestElement(int k, vector<int> nums) {
    //第k大 下标k-1
    return QuickSort(nums, 0, nums.size() - 1, k - 1);
}
