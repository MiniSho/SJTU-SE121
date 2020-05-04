// #include <cstdio>
// #include <cstdlib>
// #include <ctime>
// #include <iostream>
// #include <random>

// #include "quickSort.h"
// #define N 100
// using namespace std;

// default_random_engine e((unsigned)time(NULL));
// int randint(int b) { return (e() % b); }

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#define N 1000000
int rand_X(int x) { return rand() % x; }

void quickSort(int arr[], int left, int right) {
    if (left < right) {
        int key = arr
            [left];  //比较点，这是第一个坑，将left位置的value存入key中，坑就出来了
        int i = left, j = right;
        while (i < j) {
            while (arr[j] > key &&
                   j > i)  // arr[j] > key可以换为arr[j] >= key，但j >
                           // i不可以换为j >= i，边界问题
                j--;
            if (i < j) arr[i++] = arr[j];
            while (arr[i] < key && i < j)  //同理
                i++;
            if (i < j) arr[j--] = arr[i];
        }
        arr[i] = key;  //此时不用纠结是arr[i] = key还是arr[j] = key，因为i = j
        quickSort(arr, left, i - 1);
        quickSort(arr, i + 1, right);
    }
}

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

int Partition(int a[], int low, int high,
              int x) {  //这里数组a是[low,high)的，注意右边界最多到a[high-1]，
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

void sort(int array[], int l, int r) {
    for (int i = l; i < r - 1; i++) {
        for (int j = i + 1; j < r - 1; j++) {
            if (array[i] > array[j])
                swap(array[i], array[j]);  //每次i后面的元素比array[i]小就交换。
        }
    }
}

int l_sort(int a[], int low, int high, int k) {
    int i, j, x, q, n;
    n = high - low;  // n为数组a[low...high]元素个数,注意右边最多取到a[high-1]
    if (n < 5) {  //元素小于5时候单独处理
        sort(a, low, high);
        return a[low + k - 1];
    }
    for (i = 0; i < n / 5; i++) {
        sort(a, low + i * 5, low + i * 5 + 5);  //对每组数据排序
        swap(a[low + i], a[low + i * 5 + 2]);   //中位数移到前面
    }
    x = l_sort(
        a, low, low + n / 5,
        n / 10 +
            1);  //寻找中位数的中位数、n/10+1非常重要，避免n<10时n/10==0此时会出现问题
    j = Partition(a, low, high, x);  //根据x将数组a划分为2部分，j为x所在数组下标
    q = j - low + 1;  // q为小于或者等于x元素的个数
    if (q == k)
        return x;
    else if (q > k)
        return l_sort(a, low, j + 1, k);
    else
        return l_sort(a, j + 1, high, k - q);
}
int Select(int a[], int n, int k) { return l_sort(a, 0, n, k); }

int main() {
    srand(time(NULL));
    int a[N];                      //快排数组
    int b[N];                      // linearSelect数组
    clock_t startTime1, endTime1;  //快速排序
    clock_t startTime2, endTime2;  // linearSelect()

    //填入相同的随机数
    for (int i = 0; i < N; i++) {
        a[i] = b[i] = rand() % N;
    }
    std::cout << '\n';
    std::cout << "N的大小:" << N << '\n';
    //快速排序
    startTime1 = clock();
    quickSort(a, 0, N - 1);
    std::cout << "第100个数字：" << a[N - 100] << '\n';
    endTime1 = clock();
    std::cout << "快速排序:" << (double)(endTime1 - startTime1) / CLOCKS_PER_SEC
              << "s" << std::endl;

    // linearselect()
    startTime2 = clock();
    int result = l_sort(b, 0, N - 1, N - 100);
    std::cout << "第100个数字：" << result << '\n';
    endTime2 = clock();
    std::cout << "linearselect():"
              << (double)(endTime2 - startTime2) / CLOCKS_PER_SEC << "s"
              << std::endl;
    return 0;
}