# include<stdio.h>
# include<stdlib.h>

int check_insert(int* hash, int* hash_temp, int* hash_tag, int key, int n);
int find_best(int* hash, int* hash_temp, int* hash_tag, int n);

int main(void){
    int n;
    int* hash;
    int* hash_temp;
    int* hash_tag;
    scanf("%d",&n);
    hash = (int*)malloc(n * sizeof(int));
    hash_temp = (int*)malloc(n * sizeof(int));
    hash_tag = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++){
        scanf("%d",&hash[i]);
        hash_tag[i] = 0;
        hash_temp[i] = -1;
    }
    int len = 0;
    for(int i = 0; i < n; i++){
        int best_pos = find_best(hash, hash_temp, hash_tag, n);
        if(best_pos != -1){
            hash_temp[i] = hash[best_pos];
            hash_tag[best_pos] = 1;
            len++;
        }
    }
    for(int i = 0; i < len; i++){
        printf("%d ",hash_temp[i]);
    }
    printf("\n");
    free(hash);
    free(hash_temp);
    free(hash_tag);
    return 0;
}

int check_insert(int* hash, int* hash_temp, int* hash_tag, int key, int n){
    int pos = key % n;
    int check = -1;
    for(int i = 0; i < n; i++){
        if(hash[pos] == key){
            check = 1;
            break;
        }else if(hash_tag[pos] == 1){
            pos = (pos + 1) % n;
        }else{
            break;
        }
    }
    return check;
}

int find_best(int* hash, int* hash_temp, int* hash_tag, int n){
    int best_pos = -1;
    int min_val = 1000000000;
    for(int i = 0; i < n; i++){
        if(hash_tag[i] == 0){
            int check = check_insert(hash, hash_temp, hash_tag, hash[i], n);
            if(check == 1){
                if(hash[i] < min_val){
                    min_val = hash[i];
                    best_pos = i;
                }
            }
        }
    }
    return best_pos;
}