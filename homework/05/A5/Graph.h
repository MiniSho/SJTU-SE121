//
//  Graph.h
//  hahhahahahahuah
//
//  Created by 张立鹏 on 2018/10/30.
//  Copyright © 2018年 张立鹏. All rights reserved.
//

#include <iostream>
using namespace std;
template <typename M>
class Graph {
private:
    int numVertex,numEdge;
    int **Edge;
    M *mark;
    void Init(int n) {
        Edge= new int*[n];
        for(int i=0; i<n; i++) Edge[i]=new int[n];
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                Edge[i][j]=0;
        mark=new M[n];
        numVertex=n;
        numEdge=0;
    }
public:
    Graph(int n) {
        Init(n);
    }
    ~Graph() {
        delete []mark;
        for(int i=0; i<numVertex; i++) delete []Edge[i];
        delete []Edge;
    }
    int n() { return numVertex; }
    int e() { return numEdge; }
    int first(int n) {
        for(int i=0; i<numVertex; i++)
            if(Edge[n][i]!=0)
                return i;
        return numVertex ;
    }
    int next(int n, int w) {
        for(int i=w+1; i<numVertex; i++)
            if(Edge[n][i]!=0)
                return i;
        return numVertex;
    }
    void setEdge(int v, int w, int wh) {
        if(wh<=0){ cout<<"wrong! The edge cannot <=0"<<endl; return; }
        if(Edge[v][w]==0)numEdge++;
        Edge[v][w]=wh;
    }
    void deleEdge(int v, int w) {
        if(Edge[v][w]!=0)numEdge--;
        Edge[v][w]=0;
    }
    bool isEdge(int v, int w) {
        if(Edge[v][w]==0)return false;
        return true;
    }
    int weight(int v, int w) {
        return Edge[v][w];
    }
    M getMark(int v) { if(v>=numVertex )cout<<"越界"<<endl; return mark[v]; }
    void setMark(int v, M val) { mark[v]=val; }
    void print() {
        for(int i=0; i<numVertex; i++) {
            for(int j=0; j<numVertex; j++)
                cout<<Edge[i][j]<<' ';
            cout<<endl;
        }
    }
};
