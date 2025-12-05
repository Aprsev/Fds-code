#include<stdio.h>
#include<stdlib.h>
#include<time.h>
clock_t start,stop;
double duration1,duration2;
int d1, d2;
//Method 1: Brute force enumeration

int* Enum(int S[], int N, int c) {
    int pairs=0;
    for(int i=0;i<N;i++) {
        for(int j=i;j<N;j++) {
            if(S[i]+S[j]==c) {
                pairs++;//first enumerate to initialize the size of the array
            }
        }
    } 
    if(pairs == 0){
        return NULL; //no results
    }
    int *result = (int*)malloc(2*pairs*sizeof(int)+1);
    int cnt = 0;
    for(int i=0;i<N;i++) {
        for(int j=i;j<N;j++) {
            if(S[i]+S[j]==c) {
                result[cnt++]=S[i];
                result[cnt++]=S[j];
            }
        }
    }
    result[cnt++]=-1;
    return result; 
}


//Method 2: Hash Table

int* Hash(int S[],int N, int c){
    int* hash =(int*)calloc(c+1, sizeof(int));
    int rest;
    int pairs;
    for(int i=0;i<N;i++) {
        if(S[i]<=c) { //to avoid negative numbers
            rest = c - S[i]; //ensure rest + S[i] = c
            if (hash[rest]==1) {
                pairs++;
            }
            else
                hash[S[i]]=1;//mark as occurred
        }
    }
    if(pairs == 0){
        return NULL;
    }
    int *result = (int*)malloc(2*pairs*sizeof(int)+1);
    int cnt = 0;
    for(int i=0;i<N;i++) {
        if(S[i]<=c) {
            rest = c - S[i]; //ensure rest + S[i] = c
            if (hash[rest]==1) {
                result[cnt++]=S[i];
                result[cnt++]=c-S[i]; // to record the result
            }
            else
                hash[S[i]]=1;
        }
    }
    result[cnt++]=-1;
    free(hash);
    return result;
}

void Print(int result[]){
    if(result!=NULL){
        int i=0;
        while(result[i]!=-1){
            printf("number 1 = %d , number 2 = %d\n",result[i],result[i+1]);
            i+=2;
        }
    }
    else{
        printf("Not Found!\n");
    }
}

int main() {
    //Generate S set
    srand((unsigned int)time(NULL));//Generate random number seeds

    //Ass1: judge the correctness of two algorithms
    /**
     * for Ass1, testing data for c can be -100,0,1000,2000,10000
     * -100 -> Not Found
     * 0 -> Not Found or both 0 (depending on S)
     * 1000 -> normal output
     * 2000 -> Not Found
     * 10000 -> Not Found
     */
    int N=1000;
    int V=1000;
    int *S=(int *)malloc(N*sizeof(int));//dynamic allocation
    for(int i=0;i<N;i++)
        S[i] = rand()%(V+1);//Generate random numbers in 0-V
    int c = rand()%(2*V+1); //input c
    printf("c=%d\n",c);
    int* result1 = Enum(S,N,c);
    int* result2 = Hash(S,N,c);
    printf("Method 1\n");
    Print(result1);
    printf("Method 2\n");
    Print(result2);
    free(S);
    //Ass2: Analyze the complexities
    int Nlst[]={1000,5000,10000,20000,40000,60000,80000,100000}; //N list in Exercise
    int Vlst[]={1000,5000,10000,20000,40000,60000,80000,100000}; //V list in Exercise
    int k=100; //circle numbers
    int *cn=(int *)malloc(k*sizeof(int));
    for(int i=0;i<k;i++)
        cn[i] = rand()%(2*V+1); //random c for test
    for(int v=0;v<8;v++){//different V
        printf("V=%d\n",Vlst[v]);
        for(int n=0;n<8;n++){
            printf("N=%d\n",Nlst[n]);
            int *S=(int *)malloc(Nlst[n]*sizeof(int));//dynamic allocation
            for(int i=0;i<Nlst[n];i++)
                S[i] = rand()%(Vlst[v]+1);//Generate random numbers in 0-V
            k=15;
            //Method 1: Bruce Enumeration
            start=clock();
            for (int i = 0;i<k;i++){
                int *result = Enum(S,Nlst[n],cn[i]);
                free(result);
            }
            stop=clock();
            d1=stop-start;
            duration1=((double)(stop-start))/CLK_TCK;//calculate the duration for bruce enumeration
            k=5000;
            start = clock();
            for(int i=0;i<k;i++){
                int *result = Hash(S,Nlst[n],cn[i]);
                free(result);
            }
            stop = clock();
            d2=stop-start;
            duration2=((double)(stop-start))/CLK_TCK;//calculate the duration for hash table
            printf("Enumeration: %d, Hash: %d\n",d1,d2);
            printf("Duration: Enumeration: %lf, Hash: %lf\n",duration1,duration2);
            free(S);
        }
    }
    free(cn);
    return 0;
}