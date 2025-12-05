#include <stdio.h>
#include <stdlib.h>

void inorder(int root ,int* nums ,int* tree ,int n ,int* index) {
    if (root >= n){
        return;
    }
    inorder(2 * root + 1 ,nums ,tree ,n ,index);      
    tree[root] = nums[(*index)++];                    
    inorder(2 * root + 2 ,nums ,tree ,n ,index);      
}

int main() {
    int n;
    scanf("%d" ,&n);
    int nums[1000] ,tree[1000];
    for (int i = 0; i < n; ++i) {
        scanf("%d" ,&nums[i]);
    }
    int temp;
    for(int i =0;i < n;i++){
        for(int j =i + 1;j < n;j++){
            if(nums[i] > nums[j]){
                temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
        }
    }

    int index = 0;
    inorder(0 ,nums ,tree ,n ,&index);
    for (int i = 0; i < n; ++i) {
        printf("%d" ,tree[i]);
        if (i != n - 1){
            printf(" ");
        }
    }
    printf("\n");
    return 0;
}
