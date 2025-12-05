# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int check(char** node_name,char* name,int num_of_nodes){
    for(int i = 0;i < num_of_nodes;i++){
        if(strcmp(node_name[i],name) == 0){
            return i;
        }
    }
    return -1;
}

void insert(char** node_name,char* name,int* num_of_nodes){
    strcpy(node_name[*num_of_nodes],name);
    (*num_of_nodes)++;
}

int find(int start,int end,int** node_dis,int num_of_nodes,int* parent){
    parent[start] = -1;
    int que[num_of_nodes];
    int front = 0,rear = 0;
    que[rear++] = start;
    int visited[num_of_nodes];
    for(int i = 0;i < num_of_nodes;i++){
        visited[i] = 0;
    }
    visited[start] = 1;
    while(front != rear){
        int temp = que[front];
        front++;
        for(int i = 0;i < num_of_nodes;i++){
            if(node_dis[temp][i] > 0 && visited[i] == 0){
                que[rear++] = i;
                parent[i] = temp;
                visited[i] = 1;
                if(i == end){
                    return 1;
                }
            }
        }
    }
    return 0;
}

int cal_max_flow(int start,int end,int** node_dis,int num_of_nodes){
    int parent[num_of_nodes];
    int flow = 0;
    while(find(start,end,node_dis,num_of_nodes,parent) != 0){
        int path_flow = 1000000;
        int tem = end;
        while(tem != start && parent[tem] != -1){
            if(node_dis[parent[tem]][tem] < path_flow){
                path_flow = node_dis[parent[tem]][tem];
            }
            tem = parent[tem];
        }
        if(tem != start){
            flow = 0;
            break;
        }
        int temp = end;
        while(temp != start){
            node_dis[parent[temp]][temp] -= path_flow;
            temp = parent[temp];
        }
        flow += path_flow;
    }
    return flow;
}

int main(void){
    char source[5],desti[5];
    int n;
    char** node_name;
    int num_of_nodes = 0;
    int** node_dis;
    char t1[5],t2[5];
    int dis;
    int p1,p2;
    scanf("%s %s %d",source,desti,&n);
    node_name = (char**)malloc(2*n*sizeof(char*));
    node_dis = (int**)malloc(2*n*sizeof(int*));
    for(int i = 0;i < 2 * n;i++){
        node_name[i] = (char*)malloc(5*sizeof(char));
        node_dis[i] = (int*)malloc(2*n*sizeof(int));
    }
    for(int i = 0;i < n;i++){
        scanf("%s %s %d",t1,t2,&dis);
        p1 = check(node_name,t1,num_of_nodes);
        p2 = check(node_name,t2,num_of_nodes);
        if(p1 == -1){
            insert(node_name,t1,&num_of_nodes);
            p1 = num_of_nodes - 1;
        }
        if(p2 == -1){
            insert(node_name,t2,&num_of_nodes);
            p2 = num_of_nodes - 1;
        }
        node_dis[p1][p2] = dis;
    }
    int start,end;
    start = check(node_name,source,num_of_nodes);
    end = check(node_name,desti,num_of_nodes);
    int flow = cal_max_flow(start,end,node_dis,num_of_nodes);

    printf("%d",flow);
    return 0;    
}