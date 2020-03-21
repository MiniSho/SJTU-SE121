#include <ctime>
#include <iostream>
#include <map>
#include <random>

using namespace std;

//工具函数
default_random_engine e((unsigned)time(NULL));
int randint(int b) { return (e() % b); }

//四种哈希函数
int hash1(int num, int size) {
    unsigned int b = 59;
    unsigned int a = 13;
    unsigned int hash = 0;
    unsigned int i = 0;

    for (i = 0; i < size / 10; i += 10) {
        hash = hash * a + num;
        a = a * b;
        num = num / 10;
    }
    return hash % size;
}
int hash2(int num, int size) {
    unsigned int hash = 114514;
    unsigned int i = 0;

    for (i = 0; i < size; num /= 10, i++) {
        hash ^= ((hash << 5) + num + (hash >> 2));
    }

    return hash % size;
}
int hash3(int num, int size) {
    unsigned int hash = 0;
    unsigned int x = 0;
    unsigned int i = 0;

    for (i = 0; i < size; num /= 10, i++) {
        hash = (hash << 4) + num;
        if ((x = hash & 0xF0000000L) != 0) {
            hash ^= (x >> 24);
        }
        hash &= ~x;
    }

    return hash % size;
}
int hash4(int num, int size) {
    unsigned int hash = 0xAAAAAAAA;
    unsigned int i = 0;

    for (i = 0; i < size; num /= 10, i++) {
        hash ^= ((i & 1) == 0) ? ((hash << 7) ^ num * (hash >> 3))
                               : (~((hash << 11) + num ^ (hash >> 5)));
    }

    return hash % size;
}

class BloomFilter {
   private:
    int size;
    int *storage1_1;
    int *storage1_2;
    int *storage2;

   public:
    BloomFilter() {}
    BloomFilter(int Size) {
        size = Size;
        storage1_1 = new int[size]();  //数组初始化，赋值为0
        storage1_2 = new int[size]();
        storage2 = new int[size * 2]();
    }
    void create(int Size) {
        size = Size;
        storage1_1 = new int[size]();  //数组初始化，赋值为0
        storage1_2 = new int[size]();
        storage2 = new int[size * 2]();
    }

    ~BloomFilter() {
        delete storage1_1;
        delete storage1_2;
        delete storage2;
    }

    void add1(int data) {
        int index_hash1 = hash1(data, size);
        int index_hash2 = hash2(data, size);

        int index_hash3 = hash3(data, size);
        int index_hash4 = hash4(data, size);

        storage1_1[index_hash1] = 1;
        storage1_1[index_hash2] = 1;

        storage1_2[index_hash3] = 1;
        storage1_2[index_hash4] = 1;

        // cout << "index_hash1:" << index_hash1 << '\t'
        //      << "index_hash2:" << index_hash2 << '\t'
        //      << "index_hash3:" << index_hash3 << '\t'
        //      << "index_hash4:" << index_hash4 << endl;
    }

    void check() {
        for (int j = 0, line = 0; line < 10; line++) {
            for (int sec_line = 0; sec_line < 10; sec_line++, j++) {
                cout << storage1_1[j] << ' ';
            }
            cout << endl;
        }
    }
    void add2(int data) {
        int index_hash1 = hash1(data, size * 2);
        int index_hash2 = hash2(data, size * 2);
        int index_hash3 = hash3(data, size * 2);
        int index_hash4 = hash4(data, size * 2);

        storage2[index_hash1] = 1;
        storage2[index_hash2] = 1;
        storage2[index_hash3] = 1;
        storage2[index_hash4] = 1;
    }

    //查找
    bool lookup1(int num) {
        int index_hash1 = hash1(num, size);
        int index_hash2 = hash2(num, size);
        int index_hash3 = hash3(num, size);
        int index_hash4 = hash4(num, size);

        // cout << "index_hash1:" << index_hash1 << '\t'
        //      << "index_hash2:" << index_hash2 << '\t'
        //      << "index_hash3:" << index_hash3 << '\t'
        //      << "index_hash4:" << index_hash4 << endl;

        if (storage1_1[index_hash1] == 1 && storage1_1[index_hash2] == 1 &&
            storage1_2[index_hash3] == 1 && storage1_2[index_hash4] == 1) {
            return true;
        }
        return false;
    }

    bool lookup2(int num) {
        int index_hash1 = hash1(num, size * 2);
        int index_hash2 = hash2(num, size * 2);
        int index_hash3 = hash3(num, size * 2);
        int index_hash4 = hash4(num, size * 2);

        if (storage2[index_hash1] == 1 && storage2[index_hash2] == 1 &&
            storage2[index_hash3] == 1 && storage2[index_hash4] == 1) {
            return true;
        }
        return false;
    }
};

int main() {
    BloomFilter bloom(1000);
    for (int scale = 1000; scale < 50000; scale += 1000) {
        // cout << "+++++++" << scale << endl;
        int *data;
        data = new int[scale]();  //赋值 初始值为0

        bloom.create(1000);
        auto false_positive_1 = 0;
        auto false_positive_2 = 0;
        auto true_negative_1 = 0;
        auto true_negative_2 = 0;

        // 生成数据
        for (int i = 0; i < scale / 10; i++) {
            auto number = randint(scale);

            bloom.add1(number);
            bloom.add2(number);

            data[number] = 1;  //测试用
        }
        // bloom.check();

        //测试环节
        for (int i = 0; i < scale; i++) {
            auto number = randint(scale);  //生成测试数据

            if (bloom.lookup1(number)) {
                if (!data[number])
                    false_positive_1++;
                else
                    true_negative_1++;
            }
            if (bloom.lookup2(number)) {
                if (!data[number])
                    false_positive_2++;
                else
                    true_negative_2++;
            }
        }

        cout << "data scale:" << scale << '\t' << " "
             << (false_positive_1 / double(false_positive_1 + true_negative_1))
             << '\t' << " rate2: "
             << (false_positive_2 / double(false_positive_2 + true_negative_2))
             << endl;
        bloom.~BloomFilter();
    }

    return 0;
}
0.0106383 0.147465 0.36933 0.502762 0.631538 0.68904 0.744722 0.782758 0.80201 0.818253 0.831638 0.85621 0.858967 0.86965 0.873438 0.866937 0.88044 0.884245 0.881286 0.889109 0.889536 0.892037 0.892758 0.894179 0.896798 0.898254 0.896582 0.89801 0.898448 0.904664 0.899008 0.900613 0.902344 0.902339 0.904069 0.902676 0.904261 0.903332 0.903991 0.902319 0.902075 0.906091 0.902968 0.904496 0.903405 0.903294 0.905212 0.903095 0.9056
