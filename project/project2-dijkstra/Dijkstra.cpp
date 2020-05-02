//
// Created by kobe on 2020/4/23.
//

#include <iostream>
#include <fstream>
#include <ostream>
#include "Dijkstra.h"

using namespace std;

static int countPath = 0;

void DijkstraProject2::countNum(int nodeKey) {
    if (nodeKey == source) {
        countPath++;
        return;
    }
    for (auto &it : relaxMap[nodeKey]->prev) {
        path.push_back(it);
        countNum(it);
        path.pop_back();
    }
}

void DijkstraProject2::dfs(int nodeKey, const char *outputFile) {
    if (nodeKey == source) {
        ofstream out(outputFile, ios::app);
        if (!out.is_open()) {
            cout << "Error opening file";
            exit(1);
        }
//        countPath++;
        for (int i = path.size() - 1; i >= 0; i--) {
            if (i != 0)
                out << path[i] << " ";
            else {
                out << path[i] << "\n";
                out << "end" << "\n";
            }
        }
        out.close();
        return;
    }
    for (auto &it : relaxMap[nodeKey]->prev) {
        path.push_back(it);
        dfs(it, outputFile);
        path.pop_back();
    }
}

void DijkstraProject2::readFromFile(const char *inputfile) {
    // init
    fstream fs(inputfile);
    if (!fs.is_open()) {
        cout << "Error opening file";
        exit(1);
    }

    int tmp_src, tmp_des, tmp_cost;
    char tmp;
    fs >> NodeNum >> tmp >> edgeNum;

    //tmp init
//    tmpAdjMap = new int *[NodeNum];
//    for (int i = 0; i < NodeNum; i++) {
//        tmpAdjMap[i] = new int[NodeNum];
//        for (int j = 0; j < NodeNum; j++) {
//            tmpAdjMap[i][j] = INT_MAX;
//        }
//    }

//    edges.resize(edgeNum);

    for (int i = 0; i < edgeNum; i++) {
        fs >> tmp_src >> tmp >> tmp_des >> tmp >> tmp_cost;
        if (adjMap.find(tmp_src) != adjMap.end()) {
            adjMap[tmp_src].push_back(pair<int, int>(tmp_des, tmp_cost));
        } else {
            adjMap[tmp_src] = vector<pair<int, int>>{pair<int, int>(tmp_des, tmp_cost)};
        }
//        tmpAdjMap[tmp_src][tmp_des] = tmp_cost;

        //初始化relaxMap
        if (relaxMap.find(tmp_src) == relaxMap.end()) {
            relaxMap[tmp_src] = new Node(tmp_src);
//            relaxMap2[tmp_src] = new Node(tmp_src);
        }
        if (relaxMap.find(tmp_des) == relaxMap.end()) {
            relaxMap[tmp_des] = new Node(tmp_des);
//            relaxMap2[tmp_des] = new Node(tmp_des);
        }
//        edges.push_back(Edge(tmp_src, tmp_des, tmp_cost, -1));
    }

    fs.close();
}

void DijkstraProject2::run1(const char *outputFile) {

    source = 0;
    vector<Node *> que;
    relaxMap[0]->costTillNow = 0;

    for (auto &it : relaxMap) {
        que.push_back(it.second);
    }

    make_heap(que.begin(), que.end(), cmp());//建堆

    //dijkstra核心算法
    while (!que.empty()) {
        map<int, Node *> S;//已经扫描过的节点集合

        pop_heap(que.begin(), que.end(), cmp());//与que.pop_back()搭配使用
        S.insert(pair<int, Node *>(que.back()->key, que.back()));//出队节点进入集合S,便于以后检索
        que.pop_back();//最小元素出队

        //遍历出队节点的邻接节点，更新节点costTillNow
        for (auto &it : S) {//这层循环遍历出队节点
            for (auto &iter : adjMap[it.second->key])//这层循环遍历出队节点的邻接节点
            {
                //两个if完成松弛操作
                if ((it.second->costTillNow + iter.second) < relaxMap[iter.first]->costTillNow) {
                    relaxMap[iter.first]->costTillNow = it.second->costTillNow +
                                                        iter.second;//松弛节点,下一个节点的costTillNow = 当前节点的costTillNow + 二者之间边的cost
                    relaxMap[iter.first]->prev.clear();
                    relaxMap[iter.first]->prev.push_back(it.first);//指向前节点,记录路径，这里是求多条路径的关键点，用vector来存储多个前向节点
                } else if ((it.second->costTillNow + iter.second) == relaxMap[iter.first]->costTillNow) {
                    relaxMap[iter.first]->prev.push_back(it.first);
                }
            }
        }
        make_heap(que.begin(), que.end(), cmp());//松弛之后重置堆
    }//end of while



    for (int i = 1; i < NodeNum; i++) {
        path.clear();
        ofstream out(outputFile, ios::app);
        if (!out.is_open()) {
            cout << "Error opening file";
            exit(1);
        }
        out << relaxMap[i]->costTillNow << endl;

        path.push_back(i);
        countPath = 0;
        countNum(i);

        out << countPath << endl;
        out.close();
        dfs(i, outputFile);
    }
    std::cout << "Save result to file:" << outputFile << std::endl;
}

//bool operator<(const QEntry &l, const QEntry &r) {
//    return l.pathWeight > r.pathWeight;
//}

void DijkstraProject2::run2(const char *outputFile) {

}