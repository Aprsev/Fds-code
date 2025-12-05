#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000000

void init(int*a,int*b, int m);
int find_min(int*b,int m,int* rank);
void print(int**result,int n,int* result_size);

int main(void){
    int n,m;
    scanf("%d %d",&n,&m);
    int* a = (int*)malloc(n*sizeof(int));
    int** result = (int**)malloc(n*sizeof(int*));
    int* result_size = (int*)malloc(n*sizeof(int));
    for(int i = 0;i < n;i++){
        scanf("%d",&a[i]);
        result[i] = (int*)malloc(m*sizeof(int));
        result_size[i] = 0;
    }
    // printf("1\n");
    int* b = (int*)malloc(m*sizeof(int));
    int* rank = (int*)malloc(m*sizeof(int));
    for(int i = 0;i < m;i++){
        rank[i] = 1;
    }
    init(a,b,m);
    for(int i = m;i < n;i++){
        int min_index = find_min(b,m,rank);
        result[rank[min_index]][result_size[rank[min_index]]++] = b[min_index];
        // printf("\n");
        // for(int j = 0;j < m;j++){
        //     printf("%d ",b[j]);
        // }
        // printf("\n");
        // printf("%d %d\n",b[min_index],a[i]);
        if(a[i] > b[min_index]){
            // printf("1\n");
            b[min_index] = a[i];
        }else{
            // printf("2 ");
            b[min_index] = a[i];
            rank[min_index] = rank[min_index] + 1;
            // printf ("rank = %d\n",rank[min_index]);
        }
    }
    for(int i = 0;i < m;i++){
        int min_index = find_min(b,m,rank);
        result[rank[min_index]][result_size[rank[min_index]]++] = b[min_index];
        rank[min_index] = 10000000;
    }

    print(result,n,result_size);
    return 0;
}

void init(int*a,int*b,int m){
    for(int i = 0;i < m;i++){
        b[i] = a[i];
    }
}
int find_min(int*b,int m,int* rank){
    int min = 1000000000;
    int min_rank = 1000000000;
    int min_index = -1;
    for(int i = 0;i < m;i++){
        if(rank[i] < min_rank){
            min_rank = rank[i];
        }
    }
    for(int i = 0;i < m;i++){
        if(b[i] < min && rank[i] == min_rank){
            min = b[i];
            min_index = i;
        }
    }
    // printf("%d %d %d\n",min,min_rank,rank[min_index]);
    return min_index;
}

void print(int**result,int n,int* result_size){
    for(int i = 1;i < n;i++){
        if(result_size[i] == 0){
            return;
        }else{
            printf("%d",result[i][0]);
            for(int j = 1;j < result_size[i];j++){
                printf(" %d",result[i][j]);
            }
            printf("\n");
        }
    }
}
