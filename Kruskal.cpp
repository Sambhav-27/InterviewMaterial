
#include <bits/stdc++.h>
#define pii pair<int, int>
#define f first
#define s second
#define N 10000
using namespace std;
pii v[N]; // f=parent; s=rank;

struct piii{
    int f,s,w;
    piii(){}
    piii(int a, int b, int c){
        f=a; s=b; w=c;
    }
};

int find(int i){
    if(v[i].f!=i)
    v[i].f=find(v[i].f); // path compression; This flattens the tree, and reduces time to logn from n
    
    return v[i].f;
}
void Union(int x, int y){
    int r1=find(x); // r1=root1
    int r2=find(y);
    
    // make higher ranked root the parent of other
    if(v[r1].s < v[r2].s)
    v[r1].f=r2;
    else if(v[r1].s > v[r2].s)
    v[r2].f=r1;
    else{ // make any 1 the parent of other and increase rank of parent; for non root node doesn't matter what its rank is
        v[r2].f=r1;
        v[r1].s++;
    }
}

bool comp(piii a, piii b){
    if(a.w==b.w)
        return a.f+a.s+a.w < b.f+b.s+b.w;
    return a.w < b.w;
}

int main() {
    int i,j,k,n,m;
    cin>>n>>m;
    vector< piii > gr; 
    for(i=0;i<m;++i){
        int x,y,l;
        cin>>x>>y>>l;
        
        gr.push_back(piii(x,y,l));
        // create sets with 1 elements
        v[i].f=i; // parent is self 
        v[i].s=0; // rank is 0
    }
    sort(gr.begin(), gr.end(), comp);
    
    j=0;
    int ans=0;
    for(i=0; i<n-1; ){
        piii t= gr[j++];
        
        int x=find(t.f);
        int y=find(t.s);
        if(find(x!=y)){ // no cycle is formed by edge
            Union(x, y);
            ans+=t.w; // if you want the edges, add another vector of piii and push t in it
            
            ++i;
        }
    }
    cout<<ans<<"\n";
   
    return 0;
}


// Time: O(N * logE); E = edges; N = nodes; Infact in practice, log part comes constant
// acc to CLRS: O(N * alpha(E)); where alpha(E) is a very slowly growing function; max value is 4
