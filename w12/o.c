# include <stdio.h>
# include <stdlib.h>
# include <time.h>

int random(){
    return rand()%1000000000;
}
int main(void){
    int n = 100;
    int list[100];
    srand(time(NULL));
    for(int i=0;i<n;i++){
        list[i] = random();
    }
    printf("100\n");
    for(int i=0;i<n;i++){
        printf("%d ", list[i]);
    }
    printf("\n");
    int m = random()%n;
    for(int i=0;i<m;i++){
        int temp = list[i];
        int j = i-1;
        while(j>=0 && list[j]>temp){
            list[j+1] = list[j];
            j--;
        }
        list[j+1] = temp;
    }
    for(int i=0;i<n;i++){
        printf("%d ", list[i]);
    }
    printf("\n");
    printf("%d\n", m);
    int temp = list[m];
    int j = m-1;
    while(j>=0 && list[j]>temp){
        list[j+1] = list[j];
        j--;
    }
    list[j+1] = temp;
    for(int i=0;i<n;i++){
        printf("%d ", list[i]);
    }
    printf("\n");
    return 0;
}