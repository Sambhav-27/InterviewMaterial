#include<bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define pb push_back
#define N 1001
#define INF 10000

/**
 * see: CP algo
 * If there is an edge from u,v
 * 
 * residual(u,v) = cap(u,v) - flow(u,v)
 * flow(v,u) = -flow(u,v)  // we need this because flow might be returned at same stage
 * // think like water pipe
 *
 * flow assigned to each edge = initial capacity matrix - residual matrix
 * 
 * augmented path = path from src to sink with flow > 0; see wikipedia
 * Time = O(E * F);
 * E = number of edges; comes from bfs
 * F = max flow pf graph; beacuse in every path in worst case we can reduce cacpcity by 1
 */


vector<pii> graph[N]; // weight represents residual capacity
int residual[N][N]; // keeping residual separate because we don't want to modify initial graph

int bfs(int src, int dest, vector<int> &parent) {

    fill(parent.begin(), parent.end(), -1);
    
    parent[src] = -2; // if we keep it 1, loop will terminate in first iteration
    
    queue<pii> q;
    q.push({src, INF}); // stores min flow in path from src till this node
    
    while(!q.empty()) {
        int p = q.front().first;
        int minFlowInPath = q.front().second;
        q.pop();
        
        for(pii child: graph[p]) {
            int c = child.first;
            
            if(parent[c] == -1 && residual[p][c] > 0) { // parent is also used as visited here
                
                minFlowInPath = min(minFlowInPath, residual[p][c]);
                parent[c] = p;
                
                if(c == dest)
                return minFlowInPath;
                
                q.push({c, minFlowInPath});
            }
        }
    }
    
    return 0;
}

int getMaxFlow(int src, int dest, int n) {
    
    int totalFlow = 0;
    vector<int> parent(N);
    
    while(1) {
        int minFlowOfPath = bfs(src, dest, parent);
        
        if(minFlowOfPath == 0) break;
        totalFlow += minFlowOfPath;
        
        int cur = dest;
        while(cur != src) {
             
            int prev = parent[cur];
            
            residual[prev][cur] -= minFlowOfPath;
            residual[cur][prev] += minFlowOfPath;
            
            cur = prev;
        }
    }
    
    return totalFlow;
}

int main() {
    
    
    
        int i,n,m;
        cin>>n>>m;
        
        for(i=0;i<m;++i) {
            int src, dst, cap;
            cin>>src>>dst>>cap;
            
            graph[src].pb({dst, cap});
            graph[dst].pb({src, 0}); // initially opposite edge has 0 residual capacity
            
            residual[src][dst] = cap;
            residual[dst][src] = 0;
        }
        
        int x = getMaxFlow(1, n, n);
        
        cout<<x<<"\n";
    
    return 0;
}
