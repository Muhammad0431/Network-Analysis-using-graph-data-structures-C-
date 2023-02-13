#pragma once
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <set>
#include <queue>
#include <utility>
#include <algorithm>
#include "helpers.h"
using namespace std;
class Graph
{
    unsigned int noOfNodes;
    unsigned int noOfEdges;
    unsigned int noOfSourceNodes;
    unsigned int noOfSinkNodes;
    unsigned int noOfIsolatedNodes;
    unsigned int noOfBridgesEdges;
    unsigned int noOfApNodes;
    unsigned int graphDiameter;
    map<int, vector<int>> graph;
    map<int, vector<int>> graphInverse;
    set<int> nodes;
    void dfs(int v, int p, map<int, bool>& vis, map<int, int>& tin, map<int, int>& low, unsigned int& time);
    void apUtil(int v, map<int, bool>& vis, map<int, int>& disc, map<int, int>& low, map<int, int>& parent, map<int, bool>& ap, unsigned int& time);
    vector<int> bfs(map<int, vector<int>>& graph, int node, map<int, bool>& vis);
    set<vector<int>> getScc();
    set<vector<int>> getWcc();
    vector<int> in(int node);
    vector<int> out(int node);

public:
    Graph(const string& filename);
    void getNoOfNodes();
    void getNoOfEdges();
    void getNoOfSourceNodes();
    void getNoOfSinkNodes();
    void getNoOfIsolatedNodes();
    void getNoOfBridgesdEdges();
    void getNoOfAPNodes();
    void getDiameterOfGraph();
    void getMaxSccOfGraph();
    void getMaxWccOfGraph();
    void getInDegreeDist();
    void getOutDegreeDist();
    void getSccDist();
    void getWccDist();
    void getShortestPathDist();
};

Graph::Graph(const string& filename)
{
    this->noOfEdges = 0;
    ifstream file;
    file.open(filename, ios::in);
    if (file.is_open())
    { //checking whether the file is open
        string line;
        while (getline(file, line))
        {
            if (line[0] != '#')
            {
                replace(line.begin(), line.end(), '\t', ' ');
                replace(line.begin(), line.end(), '\r', ' ');
                vector<string> nums = split(line, ' ');
                int s = stoi(nums[0]);
                int v = stoi(nums[1]);
                this->nodes.insert(s);
                this->nodes.insert(v);
                this->noOfEdges++;
                if (s == v)
                    continue;
                this->graph[s].push_back(v);
                this->graphInverse[v].push_back(s);
            }
        }
        file.close();
        this->noOfNodes = nodes.size();
    }
}

void Graph::dfs(int v, int p, map<int, bool>& vis, map<int, int>& tin, map<int, int>& low, unsigned int& time)
{
    vis[v] = true;
    tin[v] = low[v] = time++;
    for (auto to : this->graph[v])
    {
        if (to == p)
            continue;
        if (vis[to])
        {
            low[v] = min(low[v], tin[v]);
        }
        else
        {
            this->dfs(to, v, vis, tin, low, time);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v])
                this->noOfBridgesEdges++;
        }
    }
}

void Graph::getNoOfNodes()
{
    cout << "no of nodes " << this->noOfNodes << endl;
}

void Graph::getNoOfEdges()
{
    cout << "no of edges " << this->noOfEdges << endl;
}

void Graph::getNoOfSourceNodes()
{
    this->noOfSourceNodes = 0;
    for (auto node : this->nodes)
    {
        if (this->graphInverse[node].size() == 0)
            this->noOfSourceNodes++;
    }
    cout << "no of source nodes " << this->noOfSourceNodes << endl;
}

void Graph::getNoOfSinkNodes()
{
    this->noOfSinkNodes = 0;
    for (auto node : this->nodes)
    {
        if (this->graph[node].size() == 0)
            this->noOfSinkNodes++;
    }
    cout << "no of sink nodes " << this->noOfSinkNodes << endl;
}

void Graph::getNoOfIsolatedNodes()
{
    this->noOfIsolatedNodes = 0;
    for (auto node : this->nodes)
    {
        if (this->graph[node].size() == 0 && this->graphInverse[node].size() == 0)
            this->noOfIsolatedNodes++;
    }
    cout << "no of isolated nodes " << this->noOfIsolatedNodes << endl;
}

void Graph::getNoOfBridgesdEdges()
{
    map<int, bool> vis;
    map<int, int> tin, low;
    this->noOfBridgesEdges = 0;
    unsigned int time = 0;
    for (auto node : this->nodes)
    {
        tin[node] = -1;
        low[node] = -1;
    }

    for (auto node : this->nodes)
    {
        if (!vis[node])
            this->dfs(node, -1, vis, tin, low, time);
    }

    cout << "no of bridged edges " << this->noOfBridgesEdges << endl;
}

void Graph::apUtil(int u, map<int, bool>& vis, map<int, int>& disc, map<int, int>& low, map<int, int>& parent, map<int, bool>& ap, unsigned int& time)
{
    int children = 0;
    vis[u] = true;
    disc[u] = low[u] = ++time;
    for (auto v : this->graph[u])
    {
        if (!vis[v])
        {
            children++;
            parent[v] = u;
            this->apUtil(v, vis, disc, low, parent, ap, time);
            low[u] = min(low[u], low[v]);
            if (!parent[u] && children > 1)
                ap[u] = true;
            if (parent[u] && low[v] >= disc[u])
                ap[u] = true;
        }
        else if (v != parent[u])
            low[u] = min(low[u], disc[v]);
    }
}

void Graph::getNoOfAPNodes()
{
    map<int, bool> vis, ap;
    map<int, int> parent, low, disc;
    unsigned int time = 0;
    for (auto node : this->nodes)
    {
        vis[node] = false;
        ap[node] = false;
        parent[node] = 0;
    }
    for (auto node : this->nodes)
    {
        if (!vis[node])
            this->apUtil(node, vis, disc, low, parent, ap, time);
    }
    this->noOfApNodes = 0;
    for (auto node : this->nodes)
    {
        if (ap[node])
            this->noOfApNodes++;
    }

    cout << "no of articulation nodes " << this->noOfApNodes << endl;
}

void Graph::getDiameterOfGraph()
{
    this->graphDiameter = 0;
    map<int, bool> vis;
    for (auto node : this->nodes)
    {
        if (vis[node])
            continue;
        queue<pair<int, int>> q;
        q.push({ node, 0 });
        vis[node] = true;
        while (q.size() > 0)
        {
            int v = q.front().first;
            int lvl = q.front().second;

            q.pop();
            for (auto n : this->graph[v])
            {
                if (!vis[n])
                {
                    vis[n] = true;
                    this->graphDiameter = max(this->graphDiameter, (unsigned int)lvl + 1);
                    q.push({ n, lvl + 1 });
                }
            }
        }
    }
    cout << "graph diameter " << this->graphDiameter << endl;
}

vector<int> Graph::bfs(map<int, vector<int>>& graph, int node, map<int, bool>& vis)
{
    vector<int> vec;
    queue<pair<int, int>> q;
    q.push({ node, 0 });
    vis[node] = true;
    vec.push_back(node);
    while (q.size() > 0)
    {
        int v = q.front().first;
        int lvl = q.front().second;

        q.pop();
        for (auto n : graph[v])
        {
            if (!vis[n])
            {
                vis[n] = true;
                q.push({ n, lvl + 1 });
                vec.push_back(n);
            }
        }
    }

    sort(vec.begin(), vec.end());
    return vec;
}

vector<int> Graph::in(int s)
{
    vector<int> vec;
    map<int, bool> vis;
    for (auto node : this->nodes)
    {
        if (vis[node])
            continue;
        vector<int> v = this->bfs(this->graph, node, vis);
        if (find(v.begin(), v.end(), s) != v.end())
        {
            vec.push_back(node);
        }
    }
    sort(vec.begin(), vec.end());
    return vec;
}

vector<int> Graph::out(int node)
{
    vector<int> vec;
    map<int, bool> vis;

    vector<int> v = this->bfs(this->graph, node, vis);
    for (auto s : v)
    {
        vec.push_back(s);
    }

    sort(vec.begin(), vec.end());
    return vec;
}

set<vector<int>> Graph::getScc()
{
    set<vector<int>> setScc;

    for (auto node : this->nodes)
    {
        vector<int> v1 = this->in(node);
        vector<int> v2 = this->out(node);
        vector<int> newV(v1.size());
        auto it = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), newV.begin());
        newV.resize(it - newV.begin());
        sort(newV.begin(), newV.end());
        setScc.insert(newV);
    }
    return setScc;
}

set<vector<int>> Graph::getWcc()
{
    set<vector<int>> setWcc;
    map<int, bool> vis;
    for (auto node : this->nodes)
    {
        vector<int> newV = this->bfs(this->graphInverse, node, vis);
        sort(newV.begin(), newV.end());
        setWcc.insert(newV);
    }

    return setWcc;
}

void Graph::getMaxSccOfGraph()
{
    set<vector<int>> setScc = this->getScc();
    int maxScc = 0;
    for (auto v : setScc)
    {

        maxScc = max(maxScc, (int)(v.size()));
    }
    cout << "largest strongest component consist of " << maxScc << " nodes " << endl;
}

void Graph::getMaxWccOfGraph()
{
    set<vector<int>> setWcc = this->getWcc();
    int maxWcc = 0;
    for (auto v : setWcc)
    {

        maxWcc = max(maxWcc, (int)(v.size()));
    }
    cout << "largest weakest component consist of " << maxWcc << " nodes " << endl;
}

void Graph::getInDegreeDist()
{
    map<int, int> dist;
    for (auto node : this->nodes)
    {
        int num = this->graphInverse[node].size();
        dist[num]++;
    }

    for (auto it : dist)
    {
        printf("degree: %d\n%d/%d\n", it.first, it.second, this->noOfNodes);
    }
}

void Graph::getOutDegreeDist()
{
    map<int, int> dist;
    for (auto node : this->nodes)
    {
        int num = this->graph[node].size();
        dist[num]++;
    }

    for (auto it : dist)
    {
        printf("degree: %d\n%d/%d\n", it.first, it.second, this->noOfNodes);
    }
}

void Graph::getSccDist()
{
    set<vector<int>> setScc = this->getScc();
    map<int, int> dist;
    for (auto v : setScc)
    {
        int num = v.size();
        dist[num]++;
    }

    for (auto it : dist)
    {
        printf("Scc Size: %d\n%d/%d\n", it.first, it.second, setScc.size());
    }
}

void Graph::getWccDist()
{
    set<vector<int>> setWcc = this->getWcc();
    map<int, int> dist;
    for (auto v : setWcc)
    {
        int num = v.size();
        dist[num]++;
    }

    for (auto it : dist)
    {
        printf("Wcc Size: %d\n%d/%d\n", it.first, it.second, setWcc.size());
    }
}

void Graph::getShortestPathDist()
{

    map<int, int> dist;
    for (auto node : this->nodes)
    {
        map<int, int> vis;

        queue<pair<int, int>> q;
        vis[node] = true;
        q.push({ node, 0 });
        while (q.size() > 0)
        {
            int v = q.front().first;
            int lvl = q.front().second;
            q.pop();
            for (auto u : this->graph[v])
            {
                if (!vis[u])
                {
                    vis[u] = true;
                    q.push({ u, lvl + 1 });
                    dist[lvl + 1]++;
                }
            }
        }
    }

    for (auto it : dist)
    {
        printf("distance : %d\n%d/%d\n", it.first, it.second, this->nodes.size());
    }
}
#pragma once
