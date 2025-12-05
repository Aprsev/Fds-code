#include<stdio.h>
#include<stdlib.h>

int judge(int m,int n,int* array);

int main(void){
    int m,n,k;
    scanf("%d %d %d",&m,&n,&k);
    for (int i = 0;i < k;i++){
        int *array = (int*)malloc(n * sizeof(int));
        scanf("%d",&array[0]);
        for (int j = 1;j < n;j++){
            scanf(" %d",&array[j]);
        }
        int res;
        res = judge(m, n, array);
        if (res == 1){
            printf("Yes\n");
        }else{
            printf("No\n");
        }
    }
    return 0;
}

int judge(int m,int n,int* array){
    if (array[0] > m){
        return 0;
    }
    int* stackt = (int*)malloc((m+1) * sizeof(int));
    int p = 0;
    int i = 0;
    int num = 1;
    stackt[p] = num;
    num++;
    while (i < n){
        if (p >= m){
            return 0;
        }
        if (array[i] > stackt[p]){
            p++;
            stackt[p] = num;
            num++;
        }else if (array[i] == stackt[p]){
            p--;
            i++;
        }else{
            return 0;
        }
        if (p == -1){
            p = 0;
        }
    }
    return 1;
}