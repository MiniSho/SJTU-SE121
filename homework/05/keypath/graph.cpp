#include <iostream>
#include <list>
#include <stack>
using namespace std;
int edge = 22;
class AdjListNode {
    int v;
    int weight;

   public:
    AdjListNode(int _v, int _w) : v(_v), weight(_w) {}
    int getV() { return v; }
    int getWeight() { return weight; }
};

class Graph {
   private:
    int num;
    list<AdjListNode> *adj;
    list<int> *Path = new list<int>[10];
    void topologicalSortUtil(int v, bool visited[], stack<int> &Stack);

   public:
    Graph(int N);

    void addEdge(int u, int v, int weight);
    void longestPath(int u, int v);
};

Graph::Graph(int N) {
    this->num = N;
    adj = new list<AdjListNode>[num];
}

void Graph::addEdge(int u, int v, int weight) {
    AdjListNode node(v, weight);
    adj[u].push_back(node);
}

//得到该顶点的拓扑排序,压入Stack中
void Graph::topologicalSortUtil(int v, bool visited[], stack<int> &Stack) {
    visited[v] = true;
    list<AdjListNode>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); i++) {
        AdjListNode node = *i;
        if (!visited[node.getV()]) {
            topologicalSortUtil(node.getV(), visited, Stack);
        }
    }

    Stack.push(v);
}

void Graph::longestPath(int u, int v) {
    stack<int> Stack;  // 用于存储拓扑排序
    int *dist = new int[num + 1];
    bool *visited = new bool[num];

    //是否访问过 初始化
    for (int i = 0; i < num; i++) visited[i] = false;

    topologicalSortUtil(u, visited, Stack);  //得到拓扑排序，存进Stack

    /*到点u的距离初始化为0，到其他点的距离初始化为负无穷大*/
    for (int i = 0; i < num; i++) dist[i] = -100;
    dist[u] = 0;

    //根据得到的拓扑排序，进行longest的查找
    while (Stack.empty() == false) {
        int tmp = Stack.top();  //按照顺序取出拓扑排序中的值
        Stack.pop();

        // 更新到所有邻接点的距离
        list<AdjListNode>::iterator i;
        if (dist[tmp] != -100) {  //当u到该点的距离不为-100时 (-100代表负无穷远)
            for (i = adj[tmp].begin(); i != adj[tmp].end(); ++i) {
                int next = i->getV();  //取出点tmp的指向的下一个顶点next

                //若(u->next)的距离小于( u->tmp + tmp->next
                //)的距离,则更新u到next的距离和路径
                if (dist[next] < dist[tmp] + i->getWeight()) {
                    dist[next] = dist[tmp] + i->getWeight();
                    Path[next].clear();
                    Path[next] = Path[tmp];
                    Path[next].push_back(next);
                }
            }
        }
    }
    //输出结果
    cout << u << "->" << v << endl;
    cout << "the longest length: " << dist[v] << endl;
    cout << "the longest path: " << u << ' ';
    while (!Path[v].empty()) {
        cout << Path[v].front() << ' ';
        Path[v].pop_front();
    }
    cout << endl;
}

int main() {
    Graph g(10);
    g.addEdge(0, 3, 2);
    g.addEdge(0, 6, 38);
    g.addEdge(9, 2, 42);
    g.addEdge(9, 0, 10);

    g.addEdge(1, 0, 12);
    g.addEdge(1, 4, 29);
    g.addEdge(2, 4, 47);
    g.addEdge(9, 7, 31);
    g.addEdge(2, 8, 28);
    g.addEdge(3, 4, 24);
    g.addEdge(3, 5, 14);
    g.addEdge(3, 6, 26);
    g.addEdge(4, 5, 16);
    g.addEdge(1, 9, 9);
    g.addEdge(4, 6, 48);
    g.addEdge(4, 7, 14);
    g.addEdge(5, 7, 26);
    g.addEdge(5, 8, 1);
    g.addEdge(6, 7, 29);
    g.addEdge(6, 8, 11);
    g.addEdge(8, 7, 1);

    g.addEdge(1, 2, 13);
    g.longestPath(1, 7);

    return 0;
}