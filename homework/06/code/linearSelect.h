// #include <iostream>
// #include <vector>
// #define Q 5
// using namespace std;

// void swap(int *a, int *b) {
//     int tmp = *a;
//     *a = *b;
//     *b = tmp;
// }

// int SonSort(vector<int> &data, int start, int end) {
//     for (int i = start; i < end; i++) {
//         for (int j = start + 1; j <= end; j++) {
//             if (data[i] < data[j]) {
//                 swap(data[i], data[j]);
//             }
//         }  // after the loop, data[i] are definitely larger than data[i+x]
//         (x>0)
//     }

//     // does it requires a return value?
//     int center = (start + end) / 2;
//     return data[center];
// }

// int trivialSelect(vector<int> &data) {
//     for (int i = 0; i < data.size(); i++) {
//         for (int j = i + 1; j < data.size(); j++) {
//             if (data[j] > data[i]) swap(data[i], data[j]);
//         }
//     }
//     return data[data.size() / 2];
// }

// int linearSelect(vector<int> &data) {
//     // 第0步
//     // if (data.size() < k) {
//     //     cout << "数据量不足" << endl;
//     //     return -1;
//     // }
//     if (data.size() <= Q) {  // Q = 5
//         return trivialSelect(data);
//     }

//     //第1步 划分
//     //第2步 排序，计算中位数

//     // for (int i = 0; i < data.size(); i += 5) {
//     //     for (int j = 0; j < 5; i++) {
//     //         int temp = j;
//     //     }
//     // }

//     // to get all the median
//     vector<int> median;

//     for (int i = 0; i < data.size(); i += Q) {
//         median.push_back(SonSort(data, i, i + Q - 1));
//     }

//     return linearSelect()
// }
