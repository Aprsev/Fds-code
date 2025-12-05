#include<stdio.h>
int main(void){
    int n,h;
    int ballon[100000];
    scanf("%d %d",&n,&h);
    for (int i = 0 ;i < n ;i++){
        scanf("%d",&ballon[i]);
    }
    int max = 0;
    int start = 0;
    for (int i = 0 ;i < n ;i++){
        int s_temp = ballon[i] - h;
        int e_temp = ballon[i];
        int count = 1;
        for (int j = 0 ;j < i ;j++){
            if (ballon[j] >= s_temp && ballon[j] <= e_temp){
                count++;
            }
        }
        if (count > max){
            max = count;
            start = s_temp;
        }

    }
    printf("%d %d",start,max);
    return 0;
}