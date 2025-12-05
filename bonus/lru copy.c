# include<stdio.h>
# include<stdlib.h>

int check_cache(int num ,int* cache,int len);
int check_his(int num ,int* history,int* count ,int k,int len);
int put_his(int num ,int* que ,int* count ,int len ,int n);
int put_cache(int num ,int* que ,int len ,int n);
int pop(int num ,int* que ,int len ,int n);
void print(int* que ,int len);

typedef struct node{
    int value;
    int count;
    struct node* pre;
    struct node* nxt;   
} node ;

typedef struct linked_list {
    node* head;
    node* tail;
    int len;
    int max_len;
} linked_list;

linked_list* createlinkelist(int n);
void* insert_his();
void* insert_cache();
void* find_node();
linked_list* remove();
void printlist(linked_list* list);



int main(void){
    int k,n,m;
    scanf("%d %d %d",&k,&n,&m);

    int* his;
    int* cache;
    int* count;
    int lenh,lenc;
    lenh = 0;
    lenc = 0;
    his = (int*)malloc(k*sizeof(int));
    cache = (int*)malloc(k*sizeof(int));
    count = (int*)malloc(k*sizeof(int));
    
    //Initialize history queue
    int flag;
    scanf("%d",&his[lenh]);
    count[lenh] = 1;
    lenh++;
    int i = 1;
    while(i < n){
        scanf(" %d",&his[lenh]);
        count[lenh] = 1;
        lenh++;
        flag = check_his(his[lenh] ,his ,count ,k ,lenh);
        if(flag){
            lenc = put_cache(his[lenh] ,cache ,lenc ,n);
            lenh = pop(his[lenh] ,his ,lenc ,n);
        }
        i++;
    }
    //Start process 
    int flag_h;
    int temp;
    for (int i = n;i < m;i++){
        scanf(" %d",&temp);
        flag = check_cache(temp ,cache ,lenc);
        if(flag){
            lenc = put_cache(temp ,cache ,lenc ,n);
        }else{
            flag_h = check_his(temp , his ,count ,k ,lenh);
            if(flag_h){
                lenc = put_cache(temp,cache ,lenc ,n);
                lenh = pop(temp ,his ,lenh ,n);
            }else{
                lenh = put_his(temp ,his ,count ,lenh ,n);
            }
        }
    }
    print(his ,lenh);
    printf("\n");
    print(cache ,lenc);
    return 0;
}

int check_cache(int num ,int* cache,int len){
    if (len == 0){
        return 0;
    }
    for(int i = 0;i < len;i++){
        if(cache[i] == num){
            return 1;
        }
    }
    return 0;
}

int check_his(int num ,int* history ,int* count ,int k,int len){
    for(int i = 0;i < len;i++){
        if(history[i] == num && count[i] >= k - 1){
            return 1;
        }
    }
    return 0;
}

int put_his(int num ,int* que ,int* count ,int len ,int n){
    int pos = -1;
    for(int i = 0;i < len;i++){
        if(que[i] == num){
            pos = i;
        }
    }
    int count_t = 1;
    if(pos != -1){
        count_t = count[pos] + 1;
        for(int i = pos;i < len - 1;i++){
            que[i] = que[i + 1];
        }
        len--;
        que[len] = num;
        count[len] = count;
        len++;
    }else{
        if(len == n){
            for(int i = 0;i < len-1;i++){
                que[i] = que[i+1];
                count[i] = count[i+1];
            }
            que[len - 1] = num;
            count[len - 1] = count_t;
        }else if(len < n){
            que[len] = num;
            count[len] = 1;
            len++;
        }
    }
    return len;
}

int put_cache(int num ,int* que ,int len ,int n){
    if(len == 0){
        que[0] = num;
        return 1;
    }
    int pos = -1;
    for(int i = 0;i < len;i++){
        if(que[i] == num){
            pos = i;
            break;
        }
    }
    if(pos == -1){
        if(len == n){
            for(int i = 0;i < len-1;i++){
                que[i] = que[i+1];
            }
            que[len - 1] = num;
        }else if(len < n){
            que[len] = num;
            len++;
        }
    }else{
        for(int i = pos;i < len - 1;i++){
            que[i] = que[i + 1];
        }
        len--;
        que[len] = num;
        len++;
    }
    return len;
}

int pop(int num ,int* que ,int len ,int n){
    int pos = -1;
    for(int i = 0;i < len;i++){
        if(que[i] == num){
            pos = i;
            break;
        }
    }
    if(pos == -1){
        return -1;
    }else{
        for(int i = pos;i < len - 1;i++){
            que[i] = que[i + 1];
        }
        len--;
    }
    return len;
}

void print(int* que ,int len){
    if(len == 0){
        printf("-");
    }else{
        printf("%d",que[0]);
        for(int i = 1;i < len;i++){
            printf(" %d",que[i]);
        }
    }
}