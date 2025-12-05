# include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    int* arr1,*arr2;
    scanf("%d",&n);
    arr1 = (int*)malloc(n*sizeof(int));
    arr2 = (int*)malloc(n*sizeof(int));
    for(int i=0;i<n;i++){
        scanf("%d",&arr1[i]);
    }
    for(int i=0;i<n;i++){
        scanf("%d",&arr2[i]);
    }
    int flag = 0;
    for(int i=0;i<n;i++){
        if(arr1[i]!=arr2[i]){
            flag = 1;
            break;
        }
    }
    if(flag){
        printf("Not Equal\n");
    }
    else{
        printf("Equal\n");
    }
    return 0;
}