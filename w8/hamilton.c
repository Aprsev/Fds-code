# include<stdio.h>
# include<stdlib.h>

#define Maxlen 200

int check_list(int n,int* edge);

int main(void){
    int n,m;
    scanf("%d %d",&n,&m);
    int* edge;
    edge = (int*)malloc(sizeof(int) * (n * n + n));
    int x,y;
    for(int i = 0;i < m;i++){
        scanf("%d %d",&x,&y);
        edge[x * n + y] = 1;
        edge[y * n + x] = 1;
    }
    int num_q;
    scanf("%d",&num_q);
    for(int i = 0;i < num_q;i++){
        int res = check_list(n,edge);
        if(res == 1){
            printf("YES\n");
        }else{
            printf("NO\n");
        }
    }
    return 0;
}

int check_list(int n,int* edge){
    int len;
    scanf("%d",&len);
    int* que;
    que = (int*)malloc(sizeof(int) * len);
    for(int j = 0;j < len;j++){
        scanf("%d",&que[j]);
    }
    if(len != n + 1){
        // printf("1\n");
        return 0;
    }else if(que[0] != que[len - 1]){
        // printf("2\n");
        return 0;
    }

    int check[Maxlen + 1]= {0};
    for(int j = 0;j < len - 1;j++){
        if(check[que[j]] == 1){
            // printf("3\n");
            return 0;
        }
        check[que[j]] = 1;
    }
    for(int j = 1;j <= n;j++){
        if(check[j] != 1){
            // printf("4\n");
            return 0;
        }
    }

    for(int j = 0;j < n -1 ;j++){
        if(edge[que[j] * n + que[j + 1]] != 1){
            // printf("5\n");
            return 0;
        }
    }
    return 1;
}