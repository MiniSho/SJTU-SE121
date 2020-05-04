#include <iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include <random>

#define Q 5
#define N 1000000
using namespace std;
std::default_random_engine e((unsigned) time(NULL));

int randint(int b) { return (e() % b); }


void quickSort(int arr[], int left, int right) {
    if (left < right) {
        int key = arr[left];  //比较点，这是第一个坑，将left位置的value存入key中，坑就出来了
        int i = left, j = right;
        while (i < j) {
            while (arr[j] > key && j > i)    //arr[j] > key可以换为arr[j] >= key，但j > i不可以换为j >= i，边界问题
                j--;
            if (i < j)
                arr[i++] = arr[j];
            while (arr[i] < key && i < j)    //同理
                i++;
            if (i < j)
                arr[j--] = arr[i];
        }
        arr[i] = key;      //此时不用纠结是arr[i] = key还是arr[j] = key，因为i = j
        quickSort(arr, left, i - 1);
        quickSort(arr, i + 1, right);
    }
}

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

int Partition(int a[], int low, int high, int x) {  //这里数组a是[low,high)的，注意右边界最多到a[high-1]，
    /*利用x将数组划分为2部分*/
    int i = low;
    high--;
    while (a[i] != x) i++;
    swap(a[low], a[i]);  //将基准移到首位置
    while (low < high) {
        while (low < high && a[high] >= x) high--;
        a[low] = a[high];
        while (low < high && a[low] <= x) low++;
        a[high] = a[low];
    }
    a[low] = x;
    return low;
}

void trivialSelect(int array[], int l, int r) {
    for (int i = l; i < r - 1; i++) {
        for (int j = i + 1; j < r - 1; j++) {
            if (array[i] > array[j])
                swap(array[i], array[j]);//每次i后面的元素比array[i]小就交换。
        }
    }
}

int linearSelect(int data[], int low, int high, int k) {
    //init
    int index, median, num_of_less_Median, size;
    size = high - low;

    // 第0步
    if (size < Q) {
        trivialSelect(data, low, high);
        return data[low + k - 1];
    }

    //第一步 划分
    //第二步 排序，计算中位数,调整中位数位置
    for (int i = 0; i < size / Q; i++) {
        trivialSelect(data, low + i * Q, low + i * Q + Q);
        swap(data[low + i], data[low + i * Q + 2]);
    }

    //第三步 递归找全局中位数
    median = linearSelect(data, low, low + size / Q, size / 10 + 1);

    //第四步 划分子集
    index = Partition(data, low, high, median);
    num_of_less_Median = index - low + 1;
    if (num_of_less_Median == k)
        return median;
    else if (num_of_less_Median > k)
        return linearSelect(data, low, index + 1, k);
    else
        return linearSelect(data, index + 1, high, k - num_of_less_Median);
}

int Select(int a[], int n, int k) {
    return linearSelect(a, 0, n, k);
}

int main() {
    srand(time(NULL));
    int a[N]; //快排数组
    int b[N]; //linearSelect数组
    clock_t startTime1, endTime1; //快速排序
    clock_t startTime2, endTime2; //linearSelect()

    //填入相同的随机数
    for (int i = 0; i < N; i++) {
        a[i] = b[i] = randint(N);
    }
    std::cout << '\n';
    std::cout << "the size of N: " << N << '\n';
    //快速排序
    startTime1 = clock();
    quickSort(a, 0, N - 1);
    std::cout << "the 100th largest num in quickSort: " << a[N - 100] << '\n';
    endTime1 = clock();
    std::cout << "time: " << (double) (endTime1 - startTime1) / CLOCKS_PER_SEC << "s" << std::endl;

    //linearselect()
    startTime2 = clock();
    int result = linearSelect(b, 0, N - 1, N - 100);
    endTime2 = clock();
    std::cout << "the 100th largest num in linearSelect: " << result << '\n';

    std::cout << "time: " << (double) (endTime2 - startTime2) / CLOCKS_PER_SEC << "s" << std::endl;
    return 0;
}
