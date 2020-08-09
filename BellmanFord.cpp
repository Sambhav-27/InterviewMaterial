struct Edge{
    int a, b, cost;
}

// 0 based
int n,m; // n vertices; m edges
vector<Edge> edges;

// find shortest distance of all vertices from src.
void bellmanFord(int src) {
    int i,j;
    
    vector<int> dist(n+1, INF);
    vector<int> parent(n+1, -1);
    dist[src] =0;
    
    for(i=0; i<n-1;++i) {
        
        bool flag = false;
        
        for(j=0;j<m;++j) {
            Edge edge = edges[j];
            
            if(dist[edge.a] < INF && edge.cost + dist[edge.a] < dist[edge.b]) {
                dist[edge.b] = edge.cost + dist[edge.a];
                parent[edge.b] = edge.a;
                flag = true;
            }
            
        }
        
        if(!flag) break;
    }
}
