#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAX_V 1000
#define MAX_E 100000
#define INF 0x3f3f3f3f

// FORWARD STAR
typedef struct Edge {
    int next;   
    int to;     // TO
    int w;      // WEIGHT
} Edge;

Edge edge[MAX_E * 2];  // BOTH WAY
int head[MAX_V + 1];   
int cnt = 0;          
int dist[MAX_V + 1];  
bool visited[MAX_V + 1];


void add(int u, int v, int w) {
    edge[cnt].w = w;
    edge[cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

// 验证Dijkstra
bool isDijkstraSequence(int n, int* seq) {
    // init
    memset(dist, INF, sizeof(dist));
    memset(visited, false, sizeof(visited));
    
    int source = seq[0];
    dist[source] = 0;
    
     for (int i = 0; i < n; i++) {
        int u = seq[i];
        
        if (visited[u]) return false;
        visited[u] = true;
        
        for (int v = 1; v <= n; v++) {
            if (!visited[v] && dist[v] < dist[u]) {
                return false;
            }
        }
        
        // update dist
        for (int j = head[u]; j != -1; j = edge[j].next) {
            int v = edge[j].to;
            int w = edge[j].w;
            if (!visited[v] && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    }
    
    return true;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    
    //init
    memset(head, -1, sizeof(head));
    // read edges

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
        add(v, u, w);  
    }
    
    int k;
    scanf("%d", &k);
    
    // verify
    for (int i = 0; i < k; i++) {
        int seq[MAX_V];
        for (int j = 0; j < n; j++) {
            scanf("%d", &seq[j]);
        }   

        // 验证
        if (isDijkstraSequence(n, seq)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    
    return 0;
}