//
// Created by kobe on 2020/4/23.
//

#ifndef INC_2_DIJKSTRA_H
#define INC_2_DIJKSTRA_H
#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include<queue>
#include <algorithm>
using namespace std;
/**
 * This file declare the main class of Project2:DijstraProject2.
 * You should implement the methods:`readFromFile`,`run1`and`run2` in Dijstra.cpp.
 * You can add anything in DijstraProject2 class to implement Project2.
 */

class Node {//用于relaxMap中
public:
    int key;
    int costTillNow = INT_MAX;//到该节点为止的cost，松弛的时候会用到
    vector<int> prev;//前向节点。因为是多条最短路径，所以前向节点可以有多个

    explicit Node(int k):key(k) {};
};
//struct Edge
//{
//    int from{};
//    int to{};
//    int weight{};
//    vector<int> backPtr{};
//
//    Edge()= default;
//    Edge(int f, int t, int w, int b):from(f),to(t),weight(w),backPtr(b){}
//};
//using Edges = vector<Edge>;
//
//struct Vertex
//{
//    vector<int> outEdges;//指向下一个顶点的边的集合
//    int pos = 0;
//    int backPtr = -1;
//};
//using Vertices = vector<Vertex>;
//
//struct QEntry
//{
//    int pathWeight;
//    int inEdge;
//};
//bool operator < (const QEntry& l, const QEntry& r);
//using PQ = priority_queue<QEntry>;
//dijkstra算法中的优先队列的比较函数，因为queue中存储的是Node指针的形式，
//所以这个比较函数不能写在Node类里
struct cmp {
    bool operator()(const Node * a, const Node * b) {
        return a->costTillNow > b->costTillNow;
    }
};


class DijkstraProject2 {
private:
    //You can declare your graph structure here.
    int NodeNum, edgeNum;
    map<int, vector<pair<int,int>> > adjMap;//邻接表,pair<des,cost>,邻接表主要任务是记录边，便于以后查找某条边的权值
    map<int, Node*> relaxMap;//dijkstra算法进行中需要维护的所有节点，用来进行松弛操作。我把节点和边分开了，Node中不会有诸如next这样的代表边的成员变量，所有的边都单独存储在adjMap中了

//    Edges edges{};

    int source;//记录出发点的值，供display使用

    vector<int> path;//记录路径，供display使用
    void dfs(int nodeKey,const char *outputFile);//用dfs遍历输出多条最短路径
    void countNum(int nodeKey);


public:

    /**
     * Read graph from Param:`inputfile`.
     *
     */
    void readFromFile(const char* inputfile="input.txt");

    /**
     * Part 1, implement Dijstra algorithm to finish Part 1
     * and save the result to Param:`outputFile`.
     * Save the path as: node_1,node_2...node_n. (seperate nodes with comma)
     *
     */
    void run1(const char* outputFile = "output.txt");

    /**
     * Part 2, find the monotonically increasing path to finish Part 2
     * and save the result to Param:`outputFile`.
     * Save the path as: node_1,node_2...node_n. (seperate nodes with comma)
     *
     */
    void run2(const char* outputFile = "output.txt");

    //bool checkMonotonic( pair<const int, Node *> it, pair<int, int> iter);

};

#endif //INC_2_DIJKSTRA_H
