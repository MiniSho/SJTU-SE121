#include "common.h"
#include "algorithm"
#include <memory.h>
#include <math.h>

//#define MAXN 160
using namespace std;

//const int HP = 10007, N = 157, M = 5007;
int N;

//You should only code here.Don't edit any other files in this
//int func1(int amount, vector<int> &coins) {
//    sort(coins.begin(), coins.end());//此步骤多余 但便于理解
//    //初始化 建立表格dp[amount][coins.size()]
//    int size = coins.size();
//    if (size == 0) return 0;
//    int **dp = new int *[size + 1];
//    for (int i = 0; i < size + 1; i++) {
//        dp[i] = new int[amount + 1];
//    }
//    for (int i = 0; i < amount + 1; i++) {
//        dp[0][i] = 0;
//    }
//    dp[0][0] = 1;
//
//    for (int j = 1; j < size + 1; j++) {//j-1代表coin的index
//        for (int i = 0; i < amount + 1; i++) {//金额
//            if (i < coins[j - 1]) {
//                dp[j][i] = dp[j - 1][i];
//            } else {
//                dp[j][i] = dp[j - 1][i] + dp[j][i - coins[j - 1]];
//            }
//        }
//    }
//    int result = dp[size][amount];
//
//    for (int j = 0; j < size + 1; j++)
//        delete[]dp[j];
//    delete[]dp;
//    return result;
//}
int func1(int amount, vector<int> &coins) {
    sort(coins.begin(), coins.end());//此步骤多余 但便于理解
    //初始化 建立表格dp[amount][coins.size()]
    int size = coins.size();
    if (size == 0) return 0;
    int **dp = new int *[size + 1];
    for (int i = 0; i < 2; i++) {
        dp[i] = new int[amount + 1];
    }
    for (int i = 0; i < amount + 1; i++) {
        dp[0][i] = 0;
    }
    dp[0][0] = 1;

    int line = 0;
    int j = 1;
    while (line < size) {
        for (int i = 0; i < amount + 1; i++) {//金额
            if (j == 1) {
                if (i < coins[line]) {
                    dp[1][i] = dp[0][i];
                } else {
                    dp[1][i] = dp[0][i] + dp[1][i - coins[line]];
                }
            }
            if (j == 0) {
                if (i < coins[line]) {
                    dp[0][i] = dp[1][i];
                } else {
                    dp[0][i] = dp[1][i] + dp[0][i - coins[line]];
                }
            }
        }
        line++;
        j++;
        j %= 2;
    }
    int result;
    if(j == 0){
         result = dp[1][amount];
    }
    else{
        result = dp[0][amount];
    }

    for (int m = 0; m < 2; m++)
        delete[]dp[j];
    delete[]dp;
    return result;
}

int func2(int amount, vector<vector<int> > &conquer) {

    // 初始化 dp[amount][amount]
    bool **dp = new bool *[amount];
    for (int i = 0; i < amount; i++) {
        dp[i] = new bool[amount];
        for (int j = 0; j < amount; j++) {
            dp[i][j] = false;
        }
        dp[i][(i + 1) % amount] = true;// 1.确定第i个人可以跟第i+1个人相遇决斗
    }

    for (int i = 2; i <= amount; i++) {
        for (int end, start = 0; start != amount; start++) {
            end = (i + start) % amount;
            if (dp[start][end])continue;

            for (int k = (start + 1) % amount; k != end; k = (k + 1) % amount) {
                if (dp[start][k] && dp[k][end] && (conquer[start][k] || conquer[end][k])) {
                    dp[start][end] = true;
                    break;
                }
            }
        }
    }
//    for(int i = 0; i < amount; i++){
//        for(int j = 0; j < amount; j++){
//            cout << dp[i][j]<< ' ';
//        }
//        cout << endl;
//    }

    int result = 0;
    for (int i = 0; i < amount; i++) {
        if (dp[i][i]) result++;
    }
    return result;
}

void add(int x, int y, int *son, int *next, int *index, int &total) {
    son[total] = y; // 邻接表
    next[total] = index[x];// 在顶点x的邻接表的第一条边的索引
    index[x] = total++; // 索引
}

struct data {
    int x;
    int y;
    double s;
};


double func3(int n, int hp, vector<int> &damage, vector<int> &edges) {
    int *degree = new int[n + 1]; // 度 init
    auto **f = new double *[hp + 1];// f[hp][n] init
    auto **K = new double *[n + 1];// / init
    double result = 0;// return值

    int total = 0;
    int *son = new int[edges.size() + 1];// 邻接表
    int *next = new int[edges.size() + 1];// 在顶点x的邻接表的第一条边的索引
    int *index = new int[n + 1]; // 索引 init
    data *g = new data[(n + 1) * (n + 1)];
    auto *t = new double[n + 1]; // init


    // 数据初始化 --begin
    for (int i = 0; i <= hp; i++) {
        f[i] = new double[n + 1];
        for (int j = 0; j <= n; j++) {
            f[i][j] = 0;
        }
    }
    for (int i = 0; i <= n; i++) {
        K[i] = new double[n + 1];
        index[i] = -1;

        for (int j = 0; j <= n; j++) {
            K[i][j] = 0;
        }

        degree[i] = 0;
        t[i] = 0;
    }
    // 数据初始化 --end

    for (int i = 0; i < int(edges.size()); i += 2) {
        add(edges[i], edges[i + 1], son, next, index, total);
        add(edges[i + 1], edges[i], son, next, index, total);
        degree[edges[i]]++;
        degree[edges[i + 1]]++;
    }
//    for (int i = 0; i <= n; i++) {
//        cout << i << ' ' << fir[i] << endl;
//    }

    for (int i = 1; i <= n; i++) {
        K[i][i] = 1.0;
        if (!damage[i - 1]) {
            for (int j = index[i]; j != -1; j = next[j]) {
                if (son[j] != n) {
                    K[i][son[j]] -= 1.0 / degree[son[j]];
                }
            }
        }
    }
    total = 0;

//    for(int i = 0; i <= n;i++){
//        for(int j = 0; j <= n; j++){
//            cout << K[i][j] << ' ';
//        }
//        cout << endl;
//    }

    // DP
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j && fabs(bool(K[j][i]))) {
                total++;
                g[total].x = i;
                g[total].y = j;
                g[total].s = K[j][i] / K[i][i];
                for (int k = 1; k <= n; k++) {
                    K[j][k] -= g[total].s * K[i][k];
                }
            }
        }
    }

//    for (int i = 0; i <= n; i++) {
//        for (int j = 0; j <= n; j++) {
//            cout << K[i][j] << ' ';
//        }
//        cout << endl;
//    }

    for (int i = hp; i > 0; i--) {
        //t初始化 
        for (int m = 0; m <= n; m++) {
            t[m] = 0;
        }
        if (i == hp) {
            t[1] = 1.0;
        }
        for (int j = 1; j <= n; j++) {
            for (int k = index[j]; k != -1; k = next[k]) {
                if (son[k] != n && damage[j - 1] && (i + damage[j - 1] <= hp)) {
                    t[j] += f[i + damage[j - 1]][son[k]] / (double) degree[son[k]];
                }
            }

        }
        for (int j = 1; j <= total; j++) {
            t[g[j].y] -= t[g[j].x] * g[j].s;
        }
        for (int j = 1; j <= n; j++) {
            f[i][j] = t[j] / K[j][j];
        }
    }

    for (int i = 1; i <= hp; i++) {
        result += f[i][n];
    }

    return result;
}