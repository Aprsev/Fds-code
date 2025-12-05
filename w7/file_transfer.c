# include<stdio.h>
# include<stdlib.h>

int* initialize(int n) {
    int* parent = malloc(sizeof(int) * (n + 1));
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }
    return parent;
}

int find(int x ,int* parent){
    if(parent[x] != x){
        parent[x] = find(parent[x] ,parent);
    }
    return parent[x];
}

void Union(int x ,int y ,int* parent){
    int rootX = find(x ,parent);
    int rootY = find(y ,parent);
    if (rootX != rootY) {
        parent[rootX] = rootY;
    }
}

int check(int x ,int y ,int* parent);

int main(void){
    int n;
    scanf("%d",&n);
    char sig;
    int c1,c2;
    int* parent = initialize(n);
    while ((sig = getchar()) == '\n' || sig == '\r');
    // printf("%c",sig);
    while(sig != 'S'){
        scanf("%d %d",&c1,&c2);
        if(sig == 'I'){
            Union(c1 ,c2 ,parent);
        }else if(sig == 'C'){
            int res = check(c1 ,c2 ,parent);
            if(res == -1){
                printf("no\n");
            }else{
                printf("yes\n");
            }
        }else{
            printf("You made a wrong input format!");
            exit(1);
        }
        while ((sig = getchar()) == '\n' || sig == '\r');
    }
    int flag = 0;
    for(int i = 1;i <= n;i++){
        if(parent[i] == i){
            flag++;
        }
    }
    if(flag == 1){
        printf("The network is connected.");
    }else{
        printf("There are %d components.\n",flag);
        }
    return 0;
}

int check(int x ,int y ,int* parent){
    int count = 0;
    int rootX = find(x ,parent);
    int rootY = find(y ,parent);
    if(rootX != rootY){
        return -1;
    }
    return count;
}