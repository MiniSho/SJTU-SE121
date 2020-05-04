//  main.cpp
//  jiayouaaaaa
//
//  Created by 张立鹏 on 2018/10/30.
//  Copyright © 2018年 张立鹏. All rights reserved.
//
#include <iostream>
#include <map>
#include "Graph.h"
using namespace std;
static int sum1[100]={0};
static int m[10][10]={999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999};
int DFS_all(Graph<int> &G, string u, string v, string *path, int &d, map<string,int> &vert, map<int,string> &vert1, int &flag) {
    int n=vert[u];
    int v1=vert[v];
    G.setMark(n,1);
    path[d]=u;
    d++;
    if(n==v1&&d>=1) {
        flag++;
        cout<<"起点到终点第"<<flag<<"条简单路径为：";
         int sum=0;
        for(int i=0; i<d-1; i++)
        {
            cout<<path[i]<<"-->";
            int m1=stoi(path[i]);
            int n1=stoi(path[i+1]);
            sum=sum+m[m1][n1];
            
        }
        cout<<path[d-1]<<endl;
        sum1[flag]=sum;
        cout<<"路径总长度为"<<sum<<endl;
    }
    else {
        for(int w=G.first(n); w<G.n(); w=G.next(n,w)) {
            if(G.getMark(w)==0)
                DFS_all(G,vert1[w],v,path,d,vert,vert1,flag);
        }
    }
    
    G.setMark(n,0);  //算法关键，回溯，将访问过状态变为未访问状态
    d--;
    return flag;
}
void find_all(Graph<int> &G, string u, string v, map<string,int> vert, map<int,string> vert1) {
    string path[G.n()+10];
    int d=0;
    int flag=0;
    for(int i=0; i<G.n(); i++)G.setMark(i,0);
    int temp=DFS_all(G,u,v,path,d,vert,vert1,flag);
    int min=sum1[1];
    int minw=1;
    for(int w=1;w<=flag;w++){
        if(sum1[w]<min)
        {
            min=sum1[w];
            minw=w;
        }
    }
    cout<<"最短路径为第"<<minw<<"条路径,长度为"<<sum1[minw]<<endl;
    int max=sum1[1];
    int maxw=1;
    for(int w=1;w<=flag;w++){
        if(sum1[w]>max)
        {
            max=sum1[w];
            maxw=w;
        }
    }
    cout<<"最长路径为第"<<maxw<<"条路径,长度为"<<sum1[maxw]<<endl;

    if(temp==0)cout<<"起点到终点没有简单路径"<<endl;
}

int main() {
    map<string,int> vert;
    map<int,string> vert1;
    cout<<"输入顶点数量：";
    int n;
    cin>>n;
    while(n<=0){
        printf("输入错误，请重新输入");
        cin>>n;
    }
    
    Graph<int> g(n);
    cout<<"输入顶点编号。"<<endl;
    string a,b;
    int l;
    for(int i=0; i<n; i++) {
        cin>>a;
        vert[a]=i;
        vert1[i]=a;
    }
    cout<<"输入边，格式为“起始点 终止点 长度”以‘#’结束。"<<endl;
    while(cin>>a && a!="#") {
        cin>>b;
        g.setEdge(vert[a],vert[b],1);
        scanf("%d",&l);
        int j=stoi(a);//字符串转换为整数
        int u=stoi(b);
        m[j][u]=l;
    }
    cout<<"邻接矩阵表达为"<<endl;
    g.print();
    cout<<"输入起点和终点."<<endl;
    while(cin>>a>>b)
        find_all(g,a,b,vert,vert1);
    
    return 0;
}

