#include "Graph.h"

using namespace std;

//const int MAX_NAME=10;
//const int MAX_INFO=20;
//const int MAX_VERTEX_NUM=100;
//const int MAX_ARC_NUM=100;
//const int MAX_VALUE=32767;
//int incinfo;

Graph_Matrix::Graph_Matrix(int vexnum,int arcnum,char **vexs,int kind)
{
    m_vexnum=vexnum;
    m_arcnum=arcnum;
    m_kind=kind;
    for(int i=0;i<vexnum;i++)
        strcpy(m_vexs[i].name,vexs[i]);
}

Graph_Matrix::~Graph_Matrix()
{
    DestroyGraph();
}

int Graph_Matrix::LocateVex(char *name)
{
    for(int i=0;i<m_vexnum;i++)
        if (strcmp(m_vexs[i].name,name)==0)
            return i;
    return -1;
}

bool Graph_Matrix::SetGraph(int vexnum,int arcnum,char **vexs,vector<pair<char*,char*> > arc,int kind)
    {
        int i,j,k;
        m_vexnum=vexnum;
        m_arcnum=arcnum;
        m_kind=kind;
        for(i=0;i<vexnum;i++)
            strcpy(m_vexs[i].name,vexs[i]);
        for(i=0;i<vexnum;i++)
            for(j=0;j<vexnum;j++)
            {
                if (!(kind%2))
                    m_arcs[i][j].adj=0;
                else
                    m_arcs[i][j].adj=MAX_VALUE;
                m_arcs[i][j].info=0;
            }
        for(k=0;k<arcnum;k++)
        {
            i=LocateVex(arc[k].first);
            j=LocateVex(arc[k].second);
            if (i<0 || j<0)
            {
                cout<<"archead or arctail vexter isn't exit\n";
                return false;
            }
            if (!(kind%2)) m_arcs[i][j].adj=1;
            else
            {
                cout<<"please enter weight : ";
                int w;
                cin>>w;
                m_arcs[i][j].adj=w;
            }
            if (incinfo)
            {
                cout<<"please enter info of this arc,(less than "<<MAX_INFO<<" words : ";
                m_arcs[i][j].info=new char[MAX_INFO];
                cin>>m_arcs[i][j].info;
            }
            if (kind>1)
            m_arcs[j][i].adj=m_arcs[i][j].adj;
        }
        return true;
    }

Graph_Matrix::VertexType Graph_Matrix::GetVex(int v)
    {
        if (v>=m_vexnum || v<0)
        {
            cout<<"no such vextex exits\n";
            exit(EXIT_FAILURE);
        }
        return m_vexs[v];
    }

bool Graph_Matrix::PutVex(char *v,char *name)
    {
        int k=LocateVex(v);
        if (k<0)
        {
            cout<<"no such vextex exits\n";
            return false;
        }
        strcpy(m_vexs[k].name,name);
        return true;
    }

int Graph_Matrix::FirstAdjvex(int v)
    {
        VRType j;
        m_kind%2?j=MAX_VALUE:j=0;
        for(int i=0;i<m_vexnum;i++)
            if(m_arcs[v][i].adj!=j)
                return i;
        return -1;
    }

int Graph_Matrix::NextAdjvex(int v,int w)
    {
        VRType j;
        m_kind%2?j=MAX_VALUE:j=0;
        for(int i=w+1;i<m_vexnum;i++)
            if(m_arcs[v][i].adj!=j)
                return i;
        return -1;
    }

void Graph_Matrix::InsertVex(char *v)
    {
        VRType j;
        m_kind%2?j=MAX_VALUE:j=0;
        strcpy(m_vexs[m_vexnum].name,v);
        for(int i=0;i<m_vexnum;i++)
        {
            m_arcs[m_vexnum][i].adj=m_arcs[i][m_vexnum].adj=j;
            m_arcs[m_vexnum][i].info=m_arcs[i][m_vexnum].info=0;
        }
        m_vexnum++;
    }

void Graph_Matrix::InsertArc(char *v,char *w)
    {
        int i,j,k;
        i=LocateVex(v);
        j=LocateVex(w);
        if (i<0 || j<0 ||i==j)
        {
            cout<<"no such vextex exits\n";
            return;
        }
        if (m_kind%2)
        {
            cout<<"please enter weight : ";
            cin>>m_arcs[i][j].adj;
        }
        else
        m_arcs[i][j].adj=1;
        cout<<"enter 0 or 1 to show whether has informations or not (0--no,1--yes) : ";
        if (cin>>k)
        {
            if (k)
            {
                cout<<"please enter info of this arc,(less than "<<MAX_INFO<<" words : ";
                m_arcs[i][j].info=new char[MAX_INFO];
                cin>>m_arcs[i][j].info;
            }
        }
        if (m_kind>1)
            m_arcs[j][i]=m_arcs[i][j];
    }

bool Graph_Matrix::DeleteArc(char *v,char *w)
    {
        int i,j;
        VRType k;
        m_kind%2?k=MAX_VALUE:k=0;
        i=LocateVex(v);
        j=LocateVex(w);
        if (i<0 || j<0 )
        {
            cout<<"no such vextex exits\n";
            return false;
        }
        if (m_arcs[i][j].adj!=k)
        {
            m_arcs[i][j].adj=k;
            if (m_arcs[i][j].info)
            {
                delete [] m_arcs[i][j].info;
                m_arcs[i][j].info=0;
            }
            if (m_kind>2)
                m_arcs[j][i]=m_arcs[i][j];
            m_arcnum--;
        }
        return true;
    }

bool Graph_Matrix::DeleteVex(char *v)
    {
        int j,k;
        int i=LocateVex(v);
        if (i<0)
        {
            cout<<"no such vextex exits\n";
            return false;
        }

        for(j=0;j<m_vexnum;j++)
            DeleteArc(v,m_vexs[j].name);
        if(m_kind<2)
        for(j=0;j<m_vexnum;j++)
            DeleteArc(m_vexs[j].name,v);

        for(j=i+1;j<m_vexnum;j++)
            m_vexs[j-1]=m_vexs[j];

        for(j=0;j<m_vexnum;j++)
            for(k=i+1;k<m_vexnum;k++)
                m_arcs[j][k-1]=m_arcs[j][k];
        for(j=0;j<m_vexnum;j++)
            for(k=i+1;k<m_vexnum;k++)
                m_arcs[k-1][j]=m_arcs[k][j];
        m_vexnum--;
        return true;
    }

void Graph_Matrix::DFS_Graph_Matrix(int v)
    {
        visit[v]=true;
        cout<<GetVex(v).name<<" ";
        for(int w=FirstAdjvex(v);w>=0;w=NextAdjvex(v,w))
            if(!visit[w])
                DFS_Graph_Matrix(w);
    }

void Graph_Matrix::RS_DFS_Graph_Matrix(int v)
    {
        stack <int> S;
        int next;
        if(!visit[v])
        {
            visit[v]=true;
            S.push(v);
            cout<<GetVex(v).name<<" ";
            while(!S.empty())
            {
                int top=S.top();
                for(next=FirstAdjvex(top);next>=0;next=NextAdjvex(top,next))
                    if(!visit[next])
                    {
                        visit[next]=true;
                        S.push(next);
                        cout<<GetVex(next).name<<" ";
                        break;
                    }
                if (next<0)
                S.pop();
            }
        }
    }

void Graph_Matrix::BFS_Graph_Matrix(int v)
    {
        queue<int> Q;
        if(!visit[v])
        {
            visit[v]=true;
            cout<<GetVex(v).name<<" ";
            Q.push(v);
            while(!Q.empty())
            {
                int w=Q.front();
                Q.pop();
                for(int v1=FirstAdjvex(w);v1>=0;v1=NextAdjvex(w,v1))
                {
                    if(!visit[v1])
                    {
                        visit[v1]=true;
                        cout<<GetVex(v1).name<<" ";
                        Q.push(v1);
                    }
                }
            }
        }
    }

void Graph_Matrix::Primer_tree(Graph_Edge &g)
    {
        for(int i=0;i<m_vexnum-1;i++)
        {
            g.G[i].startvex=0;
            g.G[i].endvex=i+1;
            g.G[i].weight=m_arcs[0][i+1].adj;
        }
        for(int k=0;k<m_vexnum-1;k++)
        {
            int min=MAX_VALUE;
            int index=k;

            for(int i=k;i<m_vexnum-1;i++)
            {
                if (g.G[i].weight<min)
                {
                    min=g.G[i].weight;
                    index=i;
                }
            }

            Graph_Edge::edge temp=g.G[k];
            g.G[k]=g.G[index];
            g.G[index]=temp;
            int j=g.G[k].endvex;

            for(int i=k+1;i<m_vexnum-1;i++)
            {
                int t=g.G[i].endvex;
                int w=m_arcs[j][t].adj;
                if (w<g.G[i].weight)
                {
                    g.G[i].weight=w;
                    g.G[i].startvex=j;
                }
            }
        }
        cout<<"Primer tree is : \n";
        for(int i=0;i<m_vexnum-1;i++)
        {
            cout<<m_vexs[g.G[i].startvex].name
                <<"-->"<<m_vexs[g.G[i].endvex].name
                <<"  "<<g.G[i].weight<<endl;
        }
    }

void Graph_Matrix::KrusKal_tree(Graph_Edge &in,Graph_Edge &out)
    {
        in.init(*this);
        in.sort();
        int set_union[m_vexnum];
        for(int i=0;i<m_vexnum;i++)
            set_union[i]=i;
        int k=0;
        int d=0;
        while(d<m_vexnum-1)
        {
            int m1=set_union[in.G[k].startvex];
            int m2=set_union[in.G[k].endvex];
            if (m1!=m2)
            {
                out.G[d].startvex=in.G[k].startvex;
                out.G[d].endvex=in.G[k].endvex;
                out.G[d].weight=in.G[k].weight;
                for(int i=0;i<m_vexnum;i++)
                    if (set_union[i]==m2)
                        set_union[i]=m1;
                d++;
            }
            k++;
        }
        cout<<"KrusKal tree is : \n";
        for(int i=0;i<d;i++)
        {
            cout<<m_vexs[out.G[i].startvex].name
                <<"-->"<<m_vexs[out.G[i].endvex].name
                <<"  "<<out.G[i].weight<<endl;
        }
    }


/*void Graph_Matrix::shortest_distance_DFS(int v,int u)
    {
        if (v==u)
        {
            for(int i=0;i<path.size();i++)
                cout<<path[i]<<" ";
            cout<<endl;
            if (sum<minest)
            {
                minest=sum;
                minway=path;
            }
        }
        else
        {
            visit[v]=true;
            for(int w=FirstAdjvex(v);w>=0;w=NextAdjvex(v,w))
            {
                if(!visit[w])
                {
                    if (v==0)
                    sum=0;
                    visit[w]=true;
                    sum+=m_arcs[v][w].adj;
                    path.push_back(w);
                    if (u==w)
                    pre=v;
                    shortest_distance(w,u);
                    sum-=m_arcs[pre][u].adj;
                    path.pop_back();
                    visit[w]=false;
                }
            }
        }
    }*/

/*void Graph_Matrix::shortest_distance_RS_DFS(int v,int w)
    {
        typedef pair<int,int> PAIR;
        stack <int> S;
        stack <pair<int,int> > way;
        vector <int> path;
        //vector <vector<int> > way_set;
        int next,pre,minindex,index=0,sum=0,mindistance=MAX_VALUE;
        if(!visit[v])
        {
            visit[v]=true;
            S.push(v);
            path.push_back(v);
            while(!S.empty())
            {
                int top=S.top();
                for(next=FirstAdjvex(top);next>=0;next=NextAdjvex(top,next))
                    if(!visit[next])
                    {
                        visit[next]=true;
                        S.push(next);
                        path.push_back(v);
                        way.push_back(PAIR(top,next);
                        //sum+=m_arcs[top][next].adj;
                        if (next==w)
                        {
                            for(int i=0;i<way.size();i++)
                                cout<<path[i]<<" ";
                                cout<<endl;
                            //way_set.push_back(way);
                            //if (sum<mindistance)
                            //{
                                //mindistance=sum;
                                //minindex=index;
                            //}
                            //sum-=m_arcs[top][next].adj;
                            visit[next]=false;
                            //index++;
                            path.pop_back();
                            S.pop();
                            way.pop();
                        }
                        else
                        {
                            //if (NextAdjvex(top,next)<0)
                            //pre=next;
                            break;
                        }
                    }
                    if (next<0)
                    {
                        S.pop();
                        //sum-=m_arcs[top][pre].adj;
                        way.pop_back();
                    }
            }
        }
        //for(i=0;i<way_set[minindex].size();i++)
            //cout<<way_set[minindex][i]<<"-->";
        //cout<<way_set[minindex][i]<<endl;
        cout<<"the shorteset distance is "<<mindistance<<endl;
    }*/

/*void Graph_Matrix::shortest_distance_BFS(int v,int u)
    {
        queue<int> Q;
        int sum[m_vexnum][m_vexnum];
        int min=MAX_VALUE,w;

        for (int i=0;i<m_vexnum;i++)
            for(int j=0;j<m_vexnum;j++)
                {
                    if (i==j)
                    sum[i][j]=0;
                    else
                    sum[i][j]=m_arcs[i][j].adj;
                }

        if(!visit[v])
        {
            visit[v]=true;
            Q.push(v);
            while(!Q.empty())
            {
                w=Q.front();
                Q.pop();

                for(int v1=FirstAdjvex(w);v1>=0;v1=NextAdjvex(w,v1))
                {
                    if(!visit[v1])
                    {
                        if (sum[v][w]+sum[w][v1]<sum[v][v1])
                        sum[v][v1]=sum[v][w]+sum[w][v1];

                        if (v1==u)
                        {
                            if (sum[v][u]<min)
                                min=sum[v][u];
                        }
                        else {Q.push(v1); visit[v1]=true;}
                    }
                    else
                    {
                        if (sum[v][w]+sum[w][v1]<sum[v][v1])
                        {
                            sum[v][v1]=sum[v][w]+sum[w][v1];
                            min=sum[v][v1]+sum[v1][u];
                        }
                    }
                }
            }
        }
        cout<<"the minest way is "<<min<<endl;
    }*/

void Graph_Matrix::shortest_distance_Dijkstra(int v,int w)
    {
        vector<int> distance(m_vexnum,0);
        vector<int> pre(m_vexnum,-1);
        vector<bool> visit(m_vexnum,0);
        vector <int> S;

        for(int i=0;i<m_vexnum;i++)
        {
            distance[i]=m_arcs[i][v].adj;
            if (distance[i]==MAX_VALUE)
            pre[i]=0;
            else pre[i]=v;
        }
        distance[v]=0;
        visit[v]=1;

        for(int i=1;i<m_vexnum;i++)
        {
            int min=MAX_VALUE;
            int index=v;

            for(int j=0;j<m_vexnum;j++)
                if (!visit[j] && distance[j]<min)
                {
                    min=distance[j];
                    index=j;
                }
                visit[index]=1;

            for(int j=0;j<m_vexnum;j++)
                if (!visit[j] && m_arcs[j][index].adj<MAX_VALUE)
                {
                    if (distance[j]>distance[index]+m_arcs[index][j].adj)
                    {
                        distance[j]=distance[index]+m_arcs[index][j].adj;
                        pre[j]=index;
                    }
                }

        }

        cout<<"the minest path is ";
        S.push_back(w);
        int temp=pre[w];
        while(temp!=v)
        {
            S.push_back(temp);
            temp=pre[temp];
        }
        S.push_back(v);

        copy(S.rbegin(),S.rend()-1,ostream_iterator<int,char>(cout,"-->"));
        cout<<w<<"  the minest distance is "<<distance[w]<<endl;
    }


/*int Graph_Matrix::all_two_shortest_distance(int v,int w)
    {
        for(int i=0;i<m_vexnum;i++)
            for(int j=0;j<m_vexnum;j++)
                if (i==j)
                    m_arcs[i][j].adj=0;
            for(int i=0;i<m_vexnum;i++)
            {
                for(int j=0;j<m_vexnum;j++)
                {
                    for(int k=0;k<m_vexnum;k++)
                        if (m_arcs[i][j].adj>m_arcs[i][k].adj+m_arcs[k][j].adj)
                            m_arcs[i][j].adj=m_arcs[i][k].adj+m_arcs[k][j].adj;
                }
            }
            return m_arcs[v][w].adj;
    }*/


void Graph_Matrix::PrintGraph()
    {
        char s[20]="NoDirectNet",s1[10]="Side";
        switch(m_kind)
        {
            case 0:strcpy(s,"DirectGraph");
                   strcpy(s1,"Arc");
                   break;
            case 1:strcpy(s,"DirectNet");
                   strcpy(s1,"Arc");
                   break;
            case 2:strcpy(s,"NoDirectGraph");
                   break;
            case 3:break;
        }

        cout<<m_vexnum<<" vertex,"<<m_arcnum<<" "<<s1<<endl;
        cout<<"each vertex is : ";
        for(int i=0;i<m_vexnum;i++)
            cout<<setw(5)<<GetVex(i).name;
        cout<<endl<<"its AdjMatrix is : "<<endl;
        for(int i=0;i<m_vexnum;i++)
        {
            for(int j=0;j<m_vexnum;j++)
                cout<<setw(8)<<m_arcs[i][j].adj;
            cout<<endl;
        }

        if(incinfo)
        {
            cout<<"arc informations : "<<endl;
            if(m_kind<2)
            cout<<"arctail archead "<<s1<<"'s information : "<<endl;
            else
            cout<<"vertex1 vertex2 "<<s1<<"'s information : "<<endl;
            for(int i=0;i<m_vexnum;i++)
            {
                if(m_kind<2)
                {
                    for(int j=0;j<m_vexnum;j++)
                        if(m_arcs[i][j].info)
                        {
                            cout<<setw(5)<<m_vexs[i].name<<setw(5)<<m_vexs[j].name;
                            cout<<setw(9)<<m_arcs[i][j].info<<endl;
                        }
                }
                else
                for(int j=i+1;j<m_vexnum;j++)
                    if(m_arcs[i][j].info)
                    {
                        cout<<setw(5)<<m_vexs[i].name<<setw(5)<<m_vexs[j].name;
                        cout<<setw(9)<<m_arcs[i][j].info<<endl;
                    }
            }
        }
    }

void Graph_Matrix::DestroyGraph()
    {
        for(int i=0;i<m_vexnum;i++)
            DeleteVex(m_vexs[i].name);
    }

void Graph_Edge::init(Graph_Matrix &G1)
{
        int k=0;
        for(int i=0;i<G1.m_vexnum;i++)
            for(int j=0;j<G1.m_vexnum;j++)
                if (G1.m_arcs[i][j].adj!=MAX_VALUE && i<j)
                {
                    G[k].startvex=i;
                    G[k].endvex=j;
                    G[k].weight=G1.m_arcs[i][j].adj;
                    k++;
                }
        count=k-1;
}

void Graph_Edge::sort()
{
    for(int i=0;i<count;i++)
        for(int j=0;j<count-i;j++)
            if (G[j].weight>G[j+1].weight)
            {
                edge temp=G[j];
                G[j]=G[j+1];
                G[j+1]=temp;
            }
}

Graph_AdjList::Graph_AdjList(int vexnum,int arcnum,char **vexs,int kind)
    {
        m_vexnum=vexnum;
        m_arcnum=arcnum;
        m_kind=kind;
        for(int i=0;i<vexnum;i++)
        {
            strcpy(m_vertices[i].data.name,vexs[i]);
            m_vertices[i].firstarc=0;
        }
    }

Graph_AdjList::~Graph_AdjList()
    {
        DestroyGraph();
    }

int Graph_AdjList::LocateVex(char *name)
    {
        for(int i=0;i<m_vexnum;i++)
            if(strcmp(m_vertices[i].data.name,name)==0)
                return i;
        return -1;
    }

bool Graph_AdjList::SetGraph(int vexnum,int arcnum,char **vexs,vector<pair<char*,char*> > arc,int kind)
    {
        int i,j,k;
        m_vexnum=vexnum;
        m_arcnum=arcnum;
        m_kind=kind;
        for(i=0;i<vexnum;i++)
            strcpy(m_vertices[i].data.name,vexs[i]);

        for(k=0;k<arcnum;k++)
        {
            i=LocateVex(arc[k].first);
            j=LocateVex(arc[k].second);
            if (i<0 || j<0)
            {
                cout<<"archead or arctail vexter isn't exit\n";
                return false;
            }

            ArcNode *p=new ArcNode;
            p->info=0;
            if (m_kind%2)
            {
                p->info=new WeightInfo;
                cout<<"please enter weight : ";
                cin>>p->info->weight;
            }
            p->adjvex=j;
            p->next=m_vertices[i].firstarc;
            m_vertices[i].firstarc=p;

            if (m_kind>=2)
            {
                ArcNode *q=new ArcNode;
                q->info=new WeightInfo;

                if(p->info)
                memcpy(q->info,p->info,sizeof(p->info));
                q->adjvex=i;
                q->next=m_vertices[j].firstarc;
                m_vertices[j].firstarc=q;
            }
        }
        return true;
    }

Graph_AdjList::VertexType Graph_AdjList::GetVex(int v)
    {
        if (v>=m_vexnum || v<0)
        {
            cout<<"no such vextex exits\n";
            exit(EXIT_FAILURE);
        }
        return m_vertices[v].data;
    }

bool Graph_AdjList::PutVex(char *v,char *name)
    {
        int i=LocateVex(v);
        if (i<0)
        {
            cout<<"no such vextex exits\n";
            return false;
        }
        strcpy(m_vertices[i].data.name,name);
        return true;
    }

int Graph_AdjList::FirstAdjVex(int v)
    {
        if (m_vertices[v].firstarc)
            return m_vertices[v].firstarc->adjvex;
        return -1;
    }

int Graph_AdjList::NextAdjvex(int v,int w)
    {
        ArcNode *p=m_vertices[v].firstarc;
        while (p && p->adjvex!=w)
            p=p->next;
        if (!p || !p->next)
            return -1;
        return p->next->adjvex;
    }

void Graph_AdjList::InsertVex(char *v)
    {
        strcpy(m_vertices[m_vexnum].data.name,v);
        m_vertices[m_vexnum].firstarc=0;
        m_vexnum++;
    }

void Graph_AdjList::InsertArc(char *v,char *w)
    {
        int i,j;
        i=LocateVex(v);
        j=LocateVex(w);
        if (i<0 || j<0 || i==j)
        {
            cout<<"no such vextex exits\n";
            return;
        }
        ArcNode *p=new ArcNode;
        p->adjvex=j;
        p->info=0;
        if (m_kind%2)
        {
            cout<<"please enter this arc's weight : ";
            p->info=new WeightInfo;
            cin>>p->info->weight;
        }
        p->next=m_vertices[i].firstarc;
        m_vertices[i].firstarc=p;

        if (m_kind>=2)
        {
            ArcNode *q=new ArcNode;
            q->info=p->info;
            q->adjvex=i;
            q->next=m_vertices[j].firstarc;
            m_vertices[j].firstarc=q;
        }
        m_arcnum++;
    }

bool Graph_AdjList::DeleteArc(char *v,char *w)
    {
        int i,j;
        ArcNode *pre,*q;
        i=LocateVex(v);
        j=LocateVex(w);
        if (i<0 || j<0)
            return false;
        q=m_vertices[i].firstarc;
        pre=0;

        while (q && q->adjvex!=j)
        {
            pre=q;
            q=q->next;
        }

        if(q)
        {
            if (pre)
            pre->next=q->next;
            else
            m_vertices[i].firstarc=q->next;
            m_arcnum--;

            if (m_kind%2)
            {
                delete q->info;
                delete q;
            }

            if (m_kind>=2)
            DeleteArc(w,v);
        }
        return true;
    }

bool Graph_AdjList::DeleteVex(char *v)
    {
        ArcNode *p;
        int k=LocateVex(v);
        if (k<0)
        {
            cout<<"no such vextex exits\n";
            return false;
        }

        for(int i=0;i<m_vexnum;i++)
            DeleteArc(v,m_vertices[i].data.name);

        if (m_kind<2)
        {
            for(int i=0;i<m_vexnum;i++)
                DeleteArc(m_vertices[i].data.name,v);
        }

        for(int i=0;i<m_vexnum;i++)
        {
            p=m_vertices[i].firstarc;
            while (p)
            {
                if (p->adjvex>k)
                p->adjvex--;
                p=p->next;
            }
        }

        for(int i=k+1;i<m_vexnum;i++)
            m_vertices[i-1]=m_vertices[i];
        m_vexnum--;
        return true;
    }

void Graph_AdjList::DFS_Graph_AdjList(int v)
    {
        visit[v]=true;
        cout<<GetVex(v).name<<" ";
        for(int w=FirstAdjVex(v);w>=0;w=NextAdjvex(v,w))
            if(!visit[w])
                DFS_Graph_AdjList(w);
    }

void Graph_AdjList::BFS_Graph_AdjList(int v)
    {
        queue<int> Q;
        if (!visit[v])
        {
            visit[v]=true;
            Q.push(v);
            while(!Q.empty())
            {
                int w=Q.front();
                Q.pop();
                cout<<m_vertices[w].data.name<<" ";
                for(ArcNode *v1=m_vertices[w].firstarc;v1;v1=v1->next)
                {
                    if (!visit[v1->adjvex])
                    {
                        visit[v1->adjvex]=true;
                        Q.push(v1->adjvex);
                    }
                }
            }
        }
    }

void Graph_AdjList::set_indegree(int *indegree)
    {
        ArcNode *p;
        for(int i=0;i<m_vexnum;i++)
        {
            p=m_vertices[i].firstarc;
            while(p)
            {
                indegree[p->adjvex]++;
                p=p->next;
            }
        }
    }

void Graph_AdjList::put_Topological_sort(int *indegree)
    {
        stack<int> S;
        ArcNode *p;
        vector<int> index;
        for(int i=0;i<m_vexnum;i++)
            if (!indegree[i])
                S.push(i);

        while (!S.empty())
        {
            int top=S.top();
            S.pop();
            index.push_back(top);
            p=m_vertices[top].firstarc;
            while (p)
            {
                if (!(--indegree[p->adjvex]))
                S.push(p->adjvex);
                p=p->next;
            }
        }
        if (index.size()<m_vexnum)
        {
            cout<<"topological sort doesn't exit\n";
            return;
        }
        copy(index.begin(),index.end(),ostream_iterator<int,char>(cout," "));
        cout<<endl;
    }

void Graph_AdjList::PrintGraph()
    {
        ArcNode *p;
        char s1[10]="Side",s2[10]="------";
        if (m_kind<2)
        {
            strcpy(s1,"Arc");
            strcpy(s2,"----->");
        }
        switch(m_kind)
        {
            case 0:cout<<"DirectGraph"<<endl;
                   break;
            case 1:cout<<"DirectNet"<<endl;
                   break;
            case 2:cout<<"NoDirectGraph"<<endl;
                   break;
            case 3:cout<<"NoDirectNet"<<endl;
                   break;
        }

        cout<<m_vexnum<<" vertex,"<<"each vertex is : ";
        for(int i=0;i<m_vexnum;i++)
            cout<<setw(5)<<GetVex(i).name;
        cout<<endl<<m_arcnum<<" "<<s1<<" : "<<endl;

        for(int i=0;i<m_vexnum;i++)
        {
            p=m_vertices[i].firstarc;
            while(p)
            {
                if (m_kind<=1 || i<p->adjvex)
                {
                    cout<<setw(6)<<m_vertices[i].data.name<<s2;
                    cout<<m_vertices[p->adjvex].data.name;
                    if (m_kind%2)
                        cout<<" : "<<p->info->weight;
                }
                p=p->next;
            }
            cout<<endl;
        }
    }

void Graph_AdjList::DestroyGraph()
    {
        for(int i=0;i<m_vexnum;i++)
            DeleteVex(m_vertices[i].data.name);
    }
