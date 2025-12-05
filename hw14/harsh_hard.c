# include <stdio.h>
# include <stdlib.h>

int main(void){
    int n;
    scanf("%d", &n);
    int* hash;
    hash = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++){
        scanf("%d", &hash[i]);
    }
    int* arr = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++){
        if(hash[i] < 0){
            arr[i] = -1;
        }else{
            arr[i] =(i + n -hash[i] % n) % n;
        }
    }
    // for(int i = 0; i < n; i++){
    //     printf("%d ", arr[i]);
    // }
    // printf("\n");
    // for(int i = 0; i < n; i++){
    //     printf("%d ", i);
    // }
    // printf("\n");
    int first = 1;
    for(int j = 0; j < n; j++){
        int flag = 1;
        while(flag){
            int min_pos = -1;
            int min_val = 1000000000;
            for(int i = 0; i < n; i++){
                if(arr[i] == j){
                    if(hash[i] < min_val){
                        min_pos = i;
                        min_val = hash[i];
                    }
                }
            }
            if(min_pos == -1){
                flag = 0;
            }else{
                if(first == 0){
                    printf(" %d", hash[min_pos]);
                }else{
                    printf("%d", hash[min_pos]);
                    first = 0;
                }
                arr[min_pos] = -1;
                for(int i = min_pos + 1; i < n; i++){
                    if(arr[i] > 0 && hash[i] % n <= hash[min_pos] % n){
                        arr[i]--;
                    }
                }
            }
        }
    }
    printf("\n");
    return 0;
}