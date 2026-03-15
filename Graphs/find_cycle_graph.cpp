/*
    Given an undirected graph.
    Detect whether the given graph has a cycle inside it or not
    V -> No of nodes
    adj -> Adjacency matrix
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool bfs(int srcNode, vector<vector<int>>& adj, vector<bool>& vis){
    vis[srcNode] = true;
    queue<pair<int, int>> q;
    q.push({srcNode, -1});
    while(!q.empty()){
        int node = q.front().first;
        int parent = q.front().second;
        q.pop();
        for(auto& adjNode: adj[srcNode]){
            if(!vis[adjNode]){
                vis[adjNode] = true;
                q.push({adjNode, srcNode});
            }
            else if(adjNode != srcNode){
                return true;
            }
        }
    }
    return false;
}

bool detectCycleBFS(int V, vector<vector<int>>& adj){
    vector<bool> vis(false);
    for(int i = 0; i<V; i++){
        if(!vis[i]){
            if(bfs(i, adj, vis))    return true;
        }
    }
    return false;   
}

bool dfs(int srcNode, int parentNode, vector<vector<int>>& adj, vector<bool>& vis){
    vis[srcNode] = true;
    for(auto& adjNode: adj[srcNode]){
        if(!vis[adjNode]){
            if(dfs(adjNode, parentNode, adj, vis))  return true;
        }
        else if(adjNode != parentNode){
            return true;
        }
    }
    return false;
}

bool detectCycleDFS(int V, vector<vector<int>>& adj){
    vector<bool> vis(V, false);
    for(int i = 0; i<V; i++){
        if(!vis[i]){
            if(dfs(i, i, adj, vis))    return true;
        }
    }
    return false;   
}