# include<stdio.h>
# include<stdlib.h>

void find(int start,int end,int k,int** table,int n);
int djkstra(int start,int end,int** table,int n,int k,int* dist);
void check(int start,int end,int** table,int n,int* count,int k);

int main(void){
    int n,m,k;                                      //initialize n,m,k to save the para of graph
    scanf("%d %d %d",&n,&m,&k);                     //scan the input
    int** table = (int**)malloc(n*sizeof(int*));    //create the table for the graph
    for(int i = 0;i < n;i++){
        table[i] = (int*)malloc(n*sizeof(int));
        for(int j = 0;j < n;j++){    
            table[i][j] = 0;                        //initalize the graph,mark the unconnected as distance of 0
        }
    }
    for(int i = 0;i < m;i++){
        int c1,c2,dis;
        scanf("%d %d %d",&c1,&c2,&dis);             //scan the input of the vertexes and edges
        table[c1][c2] = dis;                        //save the edge information
        table[c2][c1] = dis;
    }
    int num_of_test;                                //scan the test cases
    scanf("%d",&num_of_test);
    for(int i = 0;i < num_of_test;i++){
        int c1,c2;
        scanf("%d %d",&c1,&c2);                     //scan the start and end for the test case
        find(c1,c2,k,table,n);                      //find the solution for transportation hub
    }
    free(table);                                    //free the space
    return 0;
}
void find(int start,int end,int k,int** table,int n){//function to find the transportation hub
    int* count = (int*)malloc(n*sizeof(int));       //create count as mark of the transportaion hub
    for(int i = 0;i < n;i++){
        count[i] = 0;                               //initialize count as 0
    }
    check(start,end,table,n,count,k);//use the djkstra algorithm to find the minimal distance
    // printf("%d\n",min_dis);
    int check = 0;                                  //mark if there is any transportaion hub
    for(int i = 0;i < n;i++){
        if(count[i] == 1){                          //if count[i] is marked as 1,then it is a transportaion hub
            printf("%d ",i);                        //print out transportaion hub
            check = 1;                              //mark there exist at least 1 hub
        }
    }
    if(check == 0){                                 //hub not found,print "None"
        printf("None");
    }
    printf("\n");
    free(count);                                    //free count
}


int djkstra(int start,int end,int** table,int n,int k,int* dist){//function to calculate the shortest distance from start to end
    int* visted = (int*)malloc(n*sizeof(int));      //create visited to mark whether a node is visited in djkstra
    for(int i = 0;i < n;i++){
        dist[i] = 1000000000;                       //initialize dist big enough
        visted[i] = 0;                              //initialize all node unvisited
    }
    dist[start] = 0;                                //initialize start as distance 0
    for(int i = 0;i < n;i++){
        int temp;                                   //create temp for finding nodes
        int min_dist = 1000000000;                  //initialize min_dist big enough
        for(int j = 0;j < n;j++){
            if(!visted[j] && dist[j] < min_dist){   //find the unvisted node with shortest distance
                min_dist = dist[j];                 //mark min_dist for search
                temp = j;
            }
        }
        visted[temp] = 1;                           //mark the found node as visited
        for(int j = 0;j < n;j++){
            if(table[temp][j] != 0 && dist[temp] + table[temp][j] <= dist[j]){//go through all node connected to the temp node
                dist[j] = dist[temp] + table[temp][j];      //if the path temp->j is shorter than previous found path or j is not connected to found node yet
            }
        }
    }
    return dist[end];                               //return the min_dist from start to end
}

void check(int start,int end,int** table,int n,int* count,int k){
    int* dis_t = (int*)malloc(n*sizeof(int));
    int* dist = (int*)malloc(n*sizeof(int));
    int* dis_e = (int*)malloc(n*sizeof(int));   //create dis_e to save the distance from i to end
    int* his_con_o = (int*)malloc(n*sizeof(int)); //to mark every node's out data(in shortest path)
    int* his_con_i = (int*)malloc(n*sizeof(int));
    int min_dis = djkstra(start,end,table,n,k,dist);
    for(int i = 0;i < n;i++){
        dis_e[i] = djkstra(i,end,table,n,k,dis_t);//initialize the dis_e by using flag = 0 mode of function djkstra
        his_con_o[i] = 0;                         //initialize out data as 0
        his_con_i[i] = 0;
    }

    for(int i = 0;i < n;i++){                   //check every node except start and end
        if(i != start && i != end){
            int con_o = 0;                      //count out data
            int con_i = 0;                      //count in data
            for(int j = 0;j < n;j++){           //table[i][j] != 0 indicate that there is an edge between i and j
                if(table[i][j] != 0 && dis_e[i] == dis_e[j] + table[i][j] && dis_e[i] + dist[i] == dist[end]){
                    con_o++;                    //dis_e[i] == dis_e[j] + table[i][j] indicate that j is the next node in shortest path contains i
                }else if(table[i][j] != 0 && dis_e[j] == dis_e[i] + table[i][j] && dis_e[j] + dist[j] == dist[end]){
                    con_i++;                    //dis_e[j] == dis_e[i] + table[i][j] indicate that i is the next node in shortest path contains j
                }                               //dis_e[i] + dist[i] == dist[end] indicate that i is on a shortest path
                if(table[i][j] != 0 &&dis_e[j] == dis_e[i] + table[i][j] && count[j] == 1 && his_con_o[j] == 1){
                    con_i = k;                  //count[j] == 1 && his_con[j] == 1 indicate that j is a transportaion hub and j is the only possible next node for i
                }
            }
            if(con_o * con_i >= k ){
                his_con_o[i] = con_o;             //mark for the con_o = 1 situation
                his_con_i[i] = con_i;
                count[i] = 1;                   //mark i as transportation hub
            }
        }
    }
    for(int i = n - 1;i >= 0;i--){               //check every node except start and end
        if(i != start && i != end){
            for(int j = 0;j < n;j++){
                if(table[i][j] != 0 && dis_e[i] == dis_e[j] + table[i][j] && dist[i] + dis_e[i] == dist[end] && his_con_i[j] * his_con_o[j] >= k){
                    if(his_con_o[j] >= k){
                        count[i] = 1;           //mark i as transportation hub if j is a transportaion hub and j is the only possible next node for i
                    }
                }else if(table[i][j] != 0 && dis_e[j] == dis_e[i] + table[i][j] && dist[i] + dis_e[i] == dist[end] && his_con_i[j] * his_con_o[j] >= k){
                    if(his_con_i[j] >= k){
                        count[i] = 1;           //mark i as transportation hub if i is a transportaion hub and i is the only possible next node for j
                    }
                }
            }
        }
    }
    free(dis_t);                                //free the space    
    free(dist);
    free(dis_e);
    free(his_con_o);
    free(his_con_i);
    return min_dis;
}