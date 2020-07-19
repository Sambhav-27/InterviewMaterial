#include <bits/stdc++.h>
using namespace std;
#define INF 100000000009
#define lld long long
#define pb push_back
#define N 105

/**

https://cp-algorithms.com/graph/all-pair-shortest-path-floyd-warshall.html
https://cp-algorithms.com/graph/finding-negative-cycle-in-graph.html

FloydWarshall works for negative weights also; But it doesn't work when there is a negative weight cycle in graph;

For finding negative weight cycles:
Run floyd washall; Then use the find negative function;


 
 
*/ 

// 0 based indexing
lld parent[N][N];

void flloydWarshall(lld dist[][N], lld n) { // dist will have INF,if edge doesn't exists
    lld i,j,k;
    
    for(i=0;i<n;++i)
    for(j=0;j<n;++j)
    parent[i][j] = -1;
    
    for(k=0;k<n;++k) {
        for(i=0;i<n;++i) {
            for(j=0;j<n;++j) {
                
                // (i,j) = min((i,j), (i,k) + (k,j))
    
                if(dist[i][k] < INF && dist[k][j] < INF && (dist[i][k] + dist[k][j] < dist[i][j])) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    parent[i][j] = k;
                    
                }
            }
        }
    }
}


// this shoudl be run only after flloywd warshals is run;
void findNegativeCycles(lld dist[][N], lld n) {
    
    lld i,j,t;
    for(i=0;i<n;++i) {
        for(j=0;j<n;++j) {
            for(t=0;t<n;++t) {
                if(dist[i][t] < INF && dist[t][t] < 0 && dist[t][j] < INF) {
                    dist[i][j] = -INF;
                }
            }
        }
    }
    
}


// this is great; works well; If src and dst are same then it will print twice;
// Ex; src = 1, dst =1; then it will return 11 not just 1;
string getPath(lld src, lld dst) {
    
    if(parent[src][dst] == -1) {
        return to_string(src) + to_string(dst);
    }
    
    string firstHalf = getPath(src, parent[src][dst]);
    string secondHalf = getPath(parent[src][dst], dst);
    
    firstHalf.pop_back();
    
    return firstHalf + secondHalf;
}


int main() {
    
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    int t =1;
    while(1) {
        
        lld i,j,n,m,dist[N][N];
        vector<string> nodeNames;
        
        cin>>n;
        
        if(n ==0) break;
        
    
        for(i=0;i<n;++i) {
            for(j=0;j<n;++j) {
                if(i ==j)
                dist[i][j] = 0;
                else
                dist[i][j] = INF;
            }
        }
        
        
        for(i=0;i<n;++i) {
            string name;
            cin>>name;
            nodeNames.pb(name);
            
           for(j=0;j<n;++j) {
               lld wt;
               cin>>wt;
               
               if(i != j && wt == 0) { // specific problem requirement
                   wt = INF;
               }
               if(i ==j && wt > 0) { // specific problem requirement
                   wt = 0;
               }
               dist[i][j] = wt;
           }
           
       }
        
        flloydWarshall(dist, n);
        findNegativeCycles(dist, n);
        
        
        cout<<"Case #"<<t++<<":\n";
        int q;
        cin>>q;
        while(q--) {
            lld u,v;
            cin>>u>>v;
            
            if(dist[u][v] == -INF) {
                    cout<<"NEGATIVE CYCLE\n";
            }
            else if(dist[u][v] == INF) {
                cout<<nodeNames[u]<<"-"<<nodeNames[v]<<" ";
                cout<<"NOT REACHABLE\n";
            }
            else {
                cout<<nodeNames[u]<<"-"<<nodeNames[v]<<" ";
                cout<<dist[u][v]<<"\n";
            }
            
        }
    }
    
	return 0;
}

