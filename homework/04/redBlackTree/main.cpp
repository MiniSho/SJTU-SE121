#include <sys/time.h>
#include <chrono>
#include <ctime>
#include <iostream>
#include <random>
#include <stack>
#include "RedBlack.h"

using namespace std;
using namespace chrono;
#include <iostream>

#define RED 1
#define BLACK 0

struct branch {
    Branch* left = NULL;   // children
    Branch* right = NULL;  // children
    Branch* dad = NULL;
    int color;
    int index;
    int content;
};

red_black_tree::red_black_tree() {
    root = NULL;
    count_balances = 0;
}

void red_black_tree::add(
    int value) {  // iteractive insertion - no balancing yet
    if (!root) {
        root = new Branch;
        root->content = value;
        root->color = BLACK;
        return;
    }

    Branch* temp_branch = root;
    char flag = 0;

    while (!flag)
        if (value > temp_branch->content) {
            flag = temp_branch->right ? 0 : 1;
            temp_branch = temp_branch->right ? temp_branch->right : temp_branch;
        } else {
            flag = temp_branch->left ? 0 : -1;
            temp_branch = temp_branch->left ? temp_branch->left : temp_branch;
        }

    if (flag == -1) {
        temp_branch->left = new Branch;
        temp_branch->left->content = value;
        temp_branch->left->color = RED;
        temp_branch->left->dad = temp_branch;
        count_balances += balancing(temp_branch->left);
    } else {
        temp_branch->right = new Branch;
        temp_branch->right->content = value;
        temp_branch->right->color = RED;
        temp_branch->right->dad = temp_branch;
        count_balances += balancing(temp_branch->right);
    }
}

void red_black_tree::get(int value) {
    Branch* node = root;
    int temp_val;
    bool find;

    if (node) temp_val = node->content;

    while ((find = (value != temp_val)) && node) {
        node = value > node->content ? node->right : node->left;

        if (node) temp_val = node->content;
    }

    if (find)
        std::cout << "not find\n";
    else
        std::cout << "encontrado: " << temp_val << '\n';
}

void red_black_tree::print(Branch* node) {  // recursive printing
    if (node->left != NULL) print(node->left);

    std::cout << node->content << '|' << (node->color ? 'V' : 'B') << '|'
              << (node->dad ? node->dad->content : 'R') << " - ";

    if (node->right != NULL) print(node->right);
}

void red_black_tree::print() {
    print(root);
    std::cout << '\n';
}

Branch* red_black_tree::grandfather(Branch* node) {
    if (node && node->dad) return node->dad->dad;

    return NULL;
}

Branch* red_black_tree::uncle(Branch* node) {
    Branch* grandpa = grandfather(node);

    if (!grandpa) return NULL;

    if (grandpa->left == node->dad)
        return grandpa->right;
    else
        return grandpa->left;
}

bool red_black_tree::balancing(Branch* node) {
    bool flag = 0;
    if (!node->dad) {
        node->color = BLACK;
        return 0;
    } else if (node->dad->color) {
        Branch* uncle_node = uncle(node);
        Branch* grandpa_node = grandfather(node);

        if (uncle_node && uncle_node->color) {
            node->dad->color = BLACK;
            uncle_node->color = BLACK;
            grandpa_node->color = RED;
            balancing(grandpa_node);
        } else {
            if ((node == node->dad->right) &&
                (node->dad == grandpa_node->left)) {
                rotate(node->dad, LEFT);
                node = node->left;
            } else if ((node == node->dad->left) &&
                       (node->dad == grandpa_node->right)) {
                rotate(node->dad, RIGHT);
                node = node->right;
            }

            node->dad->color = BLACK;
            grandpa_node->color = RED;

            if ((node == node->dad->left) && (node->dad == grandpa_node->left))
                rotate(grandpa_node, RIGHT);
            else
                rotate(grandpa_node, LEFT);
        }
    }
    return 1;
}

void red_black_tree::rotate(Branch* node, bool direction) {
    Branch* temp_node;

    if (direction) {
        temp_node = node->left;
        node->left = temp_node->right;
        if (node->left) node->left->dad = node;
        temp_node->right = node;
    } else {
        temp_node = node->right;
        node->right = temp_node->left;
        if (node->right) node->right->dad = node;
        temp_node->left = node;
    }

    if (node->dad)
        if (node->dad->left == node)
            node->dad->left = temp_node;
        else
            node->dad->right = temp_node;
    else
        root = temp_node;

    temp_node->dad = node->dad;
    node->dad = temp_node;
}

int red_black_tree::getRedNum() {
    int num(0);
    Branch* ptr = root;
    stack<Branch*> s;
    while (!s.empty() || ptr) {
        while (ptr) {
            s.push(ptr);
            ptr = ptr->left;
        }
        if (!s.empty()) {
            ptr = s.top();
            s.pop();
            if (ptr->color == 1) {
                num++;
            }
            ptr = ptr->right;
        }
    }

    return num;
}

int red_black_tree::height(Branch* ptr) {
    if (ptr == nullptr)
        return 0;
    else {
        int lb = height(ptr->left);
        int rb = height(ptr->right);
        if (lb > rb) {
            return (lb + 1);
        } else {
            return (rb + 1);
        }
    }
}
int red_black_tree::blackheight(Branch* node) {
    int blackheight = 0;
    while (node != nullptr) {
        if (node->color == BLACK) blackheight++;
        node = node->left;
    }
    return blackheight;
}

//工具函数
default_random_engine e((unsigned)time(NULL));
int randint(int b) { return (e() % b); }

int main() {
    clock_t begin, finish;
    red_black_tree tree[100];
    int scale1 = 10000;
    int scale2 = 100000;
    int scale3 = 10000000;
    double time_data = 0;
    // for (int no = 0; no < 1; no++) {  //给每一个tree赋一个值
    //开始计时
    for (int no = 0; no < 5; no++) {
        for (int i = 0; i < scale3; i++)  //测试数据规模
        {
            tree[no].add(randint(scale3));
        }
        tree[no].clear();

        //测试插入时间
        auto start = system_clock::now();
        for (int i = 0; i < scale3 / 100; i++) {
            tree[no].add(randint(scale3));
        }
        auto end = system_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        std::cout << double(duration.count()) * microseconds::period::num /
                         microseconds::period::den
                  << endl;
        std::cout << "height:" << tree[no].getHeight() << endl;
        std::cout << "blackheight:" << tree[no].getBlackHeight() << endl;
        std::cout << "sloveRed:" << tree[no].getCount() << endl;
        std::cout << "-----" << endl;
    }

    // 输出结果
    // for (int i = 0; i < 100; i++) {
    //     cout << tree[i].getRedNum() << endl;
    // }

    // cout << "scale1: " << time_data / 5.0 << "s" << endl;
    return 0;
}