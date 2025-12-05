# include <stdio.h>
# include <stdlib.h>

void print(int* out,int n){
    printf("%d",out[0]);
    for(int i = 1;i < n;i++){
        printf(" %d", out[i]);
    }
}

int checkSoertType(int* in,int* out,int n){
    // printf("%d %d %d\n",out[0],out[1],out[2]);
    int flag = 0;
    for(int i = 0;i < n;i++){
        if(in[i] != out[i]){
            flag = 1;
        }
    }
    if(flag == 0){
        return 0;
    }
    if(out[0] > out[1] && out[0] > out[2]){
        return 1;
    }
    return 0;
}

void insertionSort(int* in,int* out,int n){
    int flag = 0;
    if(n == 1)
        print(out,n);
    int* temp = (int*)malloc(n * sizeof(int));
    temp[0] = out[0];
    int i;
    for(i = 1; i < n; i++){
        if(out[i] > out[i-1]){
            temp[i] = out[i];
        }else{
            break;
        }
    }
    // printf("%d\n",i);
    int k;
    flag = 0;
    for(k = 0; k < i; k++){
        for(int j = 0;j < i;j++){
            if(out[k] == temp[j]){
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            break;
        }
    }
    // printf("%d\n",k);
    if(k == i){
        int temp_num = out[i];
        int j;
        for(j = i - 1;j >= 0;j--){
            if(out[j] > temp_num){
                out[j + 1] = out[j];
            }else{
                break;
            }
        }
        out[j + 1] = temp_num;
        print(out,n);
    }else{
        print(out,n);
    }
}

void heapSort(int* in,int* out,int n){
    int i;
    int j;
    for(i = 0;i < n;i++){
        if(2 * i + 2 < n - 1 && out[i] > out[2 * i + 2]){
            j = 2 * i + 2;
        }else if(2 * i + 1 < n - 1 && out[i] > out[2 * i + 1]){
            j = 2 * i + 1;
        }else{
            break;
        }
    }
    // printf("%d %d\n",out[j],i);
    int temp = out[j];
    out[j] = out[0];
    out[0] = temp;
    int child = 1;
    i = 0;
    while(child < j){
        if(child + 1 < j && out[child + 1] > out[child]){
            child++;
        }
        if(out[child] > temp){
            out[i] = out[child];
            i = child;
            child = i * 2 + 1;
        }else{
            break;
        }
    }
    out[i] = temp;
    print(out,n);
}

int main(void){
    int n;
    int* arr_input;
    int* arr_output;
    scanf("%d", &n);
    arr_input = (int*)malloc(n * sizeof(int));
    arr_output = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++){
        scanf("%d", &arr_input[i]);
    }
    for(int i = 0; i < n; i++){
        scanf("%d", &arr_output[i]);
    }
    int result = checkSoertType(arr_input, arr_output, n);
    if(result == 0){
        printf("Insertion Sort\n");
        insertionSort(arr_input,arr_output,n);
    }else{
        printf("Heap Sort\n");
        heapSort(arr_input,arr_output,n);
    }
    return 0;
}