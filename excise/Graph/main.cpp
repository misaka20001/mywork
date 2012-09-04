#include "Graph.h"

using namespace std;

vector<bool> visit(MAX_VERTEX_NUM,false);
vector <int> path;
vector <int> minway;
static int sum;
int minest=MAX_VALUE;
int pre,incinfo;

int main()
{
    path.push_back(0);
    int vexnum,arcnum,kind;
    int indegree[MAX_VERTEX_NUM];
    char *name[MAX_VERTEX_NUM];
    vector<pair<char *,char *> >arcs;
    pair<char *,char *>arc;
    cout<<"please enter graph's vexnum,arcnum and kind"<<endl
        <<"(0--DirectGraph,1--DirectNet,2--NoDirectGraph,3--NoDirectNet) : ";
    cin>>vexnum>>arcnum>>kind;
    cin.get();
    cout<<"please enter this "<<vexnum<<" vertex : \n";
    for (int i=0;i<vexnum;i++)
    {
        name[i]=new char[MAX_NAME];
        cin>>name[i];
    }
    cin.get();
    Graph_Matrix G1(vexnum,arcnum,name,kind);
    Graph_AdjList G2(vexnum,arcnum,name,kind);

    cout<<"please enter this "<<arcnum<<" arc or side : \n";
    for(int i=0;i<arcnum;i++)
    {
        arc.first=new char[MAX_NAME];
        arc.second=new char[MAX_NAME];
        cin>>arc.first>>arc.second;
        cin.get();
        arcs.push_back(arc);
    }

    G1.SetGraph(vexnum,arcnum,name,arcs,kind);
    G1.PrintGraph();
    cout<<endl<<"DFS_Graph_Matrix is : \n";
    G1.DFS_Graph_Matrix(1);
    cout<<endl;
    MEMSET(visit);
    cout<<endl<<"RS_DFS_Graph_Matrix is : \n";
    G1.RS_DFS_Graph_Matrix(1);
    cout<<endl;
    MEMSET(visit);
    cout<<endl<<"BFS_Graph_Matrix is : \n";
    G1.BFS_Graph_Matrix(1);
    cout<<endl<<endl;
    MEMSET(visit);
    //G1.shortest_distance_Dijkstra(0,2);
    //G1.shortest_distance_BFS(0,2);
    //cout<<"the minest way is ";
    //for(int i=0;i<minway.size();i++)
    //cout<<minway[i]<<" ";
    //cout<<minest<<endl;
    /*Graph_Edge in,out,temp;
    G1.KrusKal_tree(in,out);
    cout<<endl;
    G1.Primer_tree(temp);*/
    if(G2.SetGraph(vexnum,arcnum,name,arcs,kind))
    G2.PrintGraph();
    MEMSET(visit);
    //G2.DFS_Graph_AdjList(0);
    cout<<endl;
    MEMSET(visit);
    //G2.BFS_Graph_AdjList(0);
    MEMSET(indegree);
    G2.set_indegree(indegree);
    G2.put_Topological_sort(indegree);
    return 0;
}
