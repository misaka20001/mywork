#ifndef GRAPH_INCLUDED
#define GRAPH_INCLUDED

#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <cstring>
#include <utility>
#include <cstdlib>
#include <cstdio>
#include <iterator>

#define MEMSET(a) do{\
        for(int i=0;i<MAX_VERTEX_NUM;i++)\
            a[i]=false;}while(0)

using namespace std;

typedef int VRType;
typedef char *InfoType;

//extern const int MAX_NAME;
//extern const int MAX_INFO;
//extern const int MAX_VERTEX_NUM;
//extern const int MAX_ARC_NUM;
//extern const int MAX_VALUE;
//extern int incinfo;

extern vector<bool> visit;
#define MAX_NAME 10
#define MAX_INFO 20
#define MAX_VERTEX_NUM 100
#define MAX_ARC_NUM 100
#define MAX_VALUE 32767
extern int incinfo;

class Graph_Matrix;
class Graph_Edge
{
    public:
    friend class Graph_Matrix;
    typedef struct
    {
        int startvex;
        int endvex;
        int weight;
    }edge,edgeset[MAX_ARC_NUM];

    edgeset G;
    int count;

    public:
    Graph_Edge(){}
    void init(Graph_Matrix &G1);
    void sort();
};

class Graph_Matrix
{
    private:
    friend class Graph_Edge;
    typedef struct
    {
        char name[MAX_NAME];
    }VertexType;

    typedef struct
    {
        VRType adj;
        InfoType info;
    }ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

    VertexType m_vexs[MAX_VERTEX_NUM];
    AdjMatrix m_arcs;
    int m_vexnum,m_arcnum;
    int m_kind;

    public:
    Graph_Matrix(int vexnum=0,int arcnum=0,char **vexs=0,int kind=0);
    ~Graph_Matrix();

    int LocateVex(char *name);
    bool SetGraph(int vexnum,int arcnum,char **vexs,vector<pair<char*,char*> > arc,int kind);

    VertexType GetVex(int v);
    bool PutVex(char *v,char *name);
    int FirstAdjvex(int v);
    int NextAdjvex(int v,int w);

    void InsertVex(char *v);
    void InsertArc(char *v,char *w);
    bool DeleteArc(char *v,char *w);
    bool DeleteVex(char *v);

    void DFS_Graph_Matrix(int v);
    void RS_DFS_Graph_Matrix(int v);
    void BFS_Graph_Matrix(int v);

    void Primer_tree(Graph_Edge &g);
    void KrusKal_tree(Graph_Edge &in,Graph_Edge &out);

    //void shortest_distance_DFS(int v,int u);
    //void shortest_distance_RS_DFS(int v,int w);
    //void shortest_distance_BFS(int v,int u);
    void shortest_distance_Dijkstra(int v,int w);
    //int all_two_shortest_distance(int v,int w);

    void PrintGraph();
    void DestroyGraph();
};

class Graph_AdjList
{
    private:
    typedef struct
    {
        char name[MAX_NAME];
    }VertexType;

    typedef struct
    {
        VRType weight;
    }WeightInfo;

    typedef struct ArcNode
    {
        int adjvex;
        WeightInfo *info;
        struct ArcNode *next;
    }ArcNode;

    typedef struct
    {
        VertexType data;
        ArcNode *firstarc;
    }VNode,AdjList[MAX_VERTEX_NUM];

    AdjList m_vertices;
    int m_vexnum,m_arcnum;
    int m_kind;

    public:
    Graph_AdjList(int vexnum=0,int arcnum=0,char **vexs=0,int kind=0);
    ~Graph_AdjList();

    int LocateVex(char *name);
    bool SetGraph(int vexnum,int arcnum,char **vexs,vector<pair<char*,char*> > arc,int kind);

    VertexType GetVex(int v);
    bool PutVex(char *v,char *name);
    int FirstAdjVex(int v);
    int NextAdjvex(int v,int w);

    void InsertVex(char *v);
    void InsertArc(char *v,char *w);
    bool DeleteArc(char *v,char *w);
    bool DeleteVex(char *v);

    void DFS_Graph_AdjList(int v);
    void BFS_Graph_AdjList(int v);

    void set_indegree(int *indegree);
    void put_Topological_sort(int *indegree);

    void PrintGraph();
    void DestroyGraph();
};
#endif
