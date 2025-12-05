# include <stdio.h>
# include <stdlib.h>

int check(int n,int** dis,int* parent,int len);
int MST(int n,int** dis,int* visited,int* parent);

int main(void){
    int n,m;
    scanf("%d %d",&n,&m);
    int** dis = (int**)malloc(n * sizeof(int*));
    for(int i = 0;i < n;i++){
        dis[i] = (int*)malloc(n * sizeof(int));
        for(int j = 0;j < n;j++){
            dis[i][j] = 0;
        }
    }
    for(int i = 0;i < m;i++){
        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        dis[u - 1][v - 1] = w;
        dis[v - 1][u - 1] = w;
    }
    int* visited = (int*)malloc(n * sizeof(int));
    int* parent = (int*)malloc(n * sizeof(int));
    for(int i = 0;i < n;i++){
        visited[i] = 0;
        parent[i] = -1;
    }
    visited[0] = 1;
    int min_len = MST(n,dis,visited,parent);
    int count = 1;
    for(int i = 0;i < n;i++){
        if(visited[i] == 0){
            visited[i] = 1;
            int tem_len = MST(n,dis,visited,parent);
            count++;
        }
    }
    if(count > 1){
        printf("No MST\n");
        printf("%d\n",count);
        return 0;
    }
    int result = check(n,dis,parent,min_len);
    printf("%d\n",min_len);
    if(result == -1){
        printf("Yes\n");
    }else{
        printf("No\n");
    }
    return 0;
}

int MST(int n,int** dis,int* visited,int* parent){
    int r_1,r_2;
    int min_dis = 999999999;
    int len = 0;
    for(int k = 0;k < n - 1;k++){
        for(int i = 0;i < n;i++){
            for(int j = 0;j < n;j++){
                if(dis[i][j] > 0 &&dis[i][j] < min_dis && visited[i] == 1 && visited[j] == 0){
                    r_1 = i;
                    r_2 = j;
                    min_dis = dis[i][j];
                }
            }
        }
        visited[r_2] = 1;
        parent[r_2] = r_1;
        if(min_dis != 999999999){
            len = len + min_dis;
            min_dis = 999999999;
        }
    }
    return len;
}

int check(int n,int** dis,int* parent,int len){
    for(int i = 0;i < n;i++){
        for(int j = i + 1;j < n;j++){
            if(dis[i][j] > 0 && parent[i] != j && parent[j] != i){
                int* temp_parent = (int*)malloc(n * sizeof(int));
                for(int k = 0;k < n;k++){
                    temp_parent[k] = parent[k];
                }
                temp_parent[i] = j;
                int u = j;
                int max_weight = -1;
                while(u != -1 && u != i){
                    int v = temp_parent[u];
                    if(v != -1 && dis[u][v] > 0 && dis[u][v] > max_weight){
                        max_weight = dis[u][v];
                    }
                    u = v;
                }
                if(max_weight != -1 && max_weight == dis[i][j]){
                    return 1;
                }
            }
        }
    }
    return -1;
}

