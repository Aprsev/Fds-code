# include<stdio.h>
# include<stdlib.h>

#define MAX_VAL 20000 


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

node* hash_table[2 * MAX_VAL + 2] = {NULL};

linked_list* createlinkelist(int n);
node* creatnode(int num);
int insert_his(linked_list* list ,node* num ,int k);
void insert_cache(linked_list* list ,node* num);
int find_node(linked_list* list ,node* num ,int flag);
void printlist(linked_list* list);



int main(void){
    int k,n,m;
    scanf("%d %d %d",&k,&n,&m);

    linked_list* his = createlinkelist(n);
    linked_list* cache = createlinkelist(n);

    int temp,flag;
    node* temp_node;
    scanf("%d",&temp);
    temp_node = creatnode(temp);
    flag = insert_his(his ,temp_node ,k);
    for(int i  = 1;i < m;i++){
        scanf(" %d",&temp);
        temp_node = creatnode(temp);
        if(find_node(cache ,temp_node ,1) > 0){
            if(cache->max_len == 1){
                cache->head = temp_node;
                cache->tail = temp_node;
                cache->len++;
                hash_table[temp_node->value + MAX_VAL] = temp_node;
            }else{
                cache->tail->nxt = temp_node;
                temp_node->pre = cache->tail;
                cache->tail = temp_node;
                cache->len++;
            }
        }else{
            flag = insert_his(his ,temp_node ,k);
            if (flag == 1){
                insert_cache(cache ,temp_node);
            }
        }
    }
    printlist(his);
    printf("\n");
    printf("\n");
    printlist(cache);
    return 0;
}

linked_list* createlinkelist(int n){
    linked_list* list = (linked_list*)malloc(sizeof(linked_list));
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
    list->max_len = n;
    return list;
}
node* creatnode(int num){
    node* temp = (node*)malloc(sizeof(node));
    temp->count = 1;
    temp->pre = NULL;
    temp->nxt = NULL;
    temp->value =num;
    return temp;
}
int insert_his(linked_list* list ,node* num ,int k){
    if(list->len == 0){
        list->head = num;
        list->tail = num;
        list->len++;
        hash_table[num->value] = num;
        return 0;
    }
    int count = find_node(list ,num ,0);
    if(list->max_len == 1){
        if(count != k-1){
            list->head = num;
            list->tail = num;
            num->count = count + 1;
            list->len++;
            hash_table[num->value] = num;
            return 0;
        }else{
            list->tail = NULL;
            return 1;
        }
    }
    if (list->len == list->max_len) {
        hash_table[list->head->value] = NULL;
        node* old_head = list->head;
        list->head = list->head->nxt;
        if (list->head){
            list->head->pre = NULL;
        }
        free(old_head);
        list->len--;
    }
    if(count == k - 1){
        return 1;
    }
    list->tail->nxt = num;
    num->pre = list->tail;
    num->count = count + 1; 
    list->tail = num;
    list->len++;
    hash_table[num->value] = num; 
    return 0;
}
void insert_cache(linked_list* list ,node* num){
    if(list->len == 0){
        list->head = num;
        list->tail = num;
        list->len++;
        hash_table[num->value + MAX_VAL] = num;
    }else{
        int flag = find_node(list ,num ,1);
        if(list->max_len == 1 && list->len == list->max_len){
            list->head = num;
            list->tail = num;
            hash_table[num->value + MAX_VAL] = num;
        }else{
            if (list->len == list->max_len) {
                hash_table[list->head->value + MAX_VAL] = NULL;
                node* old_head = list->head;
                list->head = list->head->nxt;
                if (list->head){
                    list->head->pre = NULL;
                }
                free(old_head);
                list->len--;
            }
            list->tail->nxt = num;
            num->pre = list->tail;
            list->tail = num;
            list->len++; 
            hash_table[num->value + MAX_VAL] = num;
        }
    }
}
int find_node(linked_list* list ,node* num ,int flag){
    node* target = hash_table[num->value + MAX_VAL * flag];  
    if (target == NULL){
        return 0;
    }  
    if(target->pre){
        target->pre->nxt = target->nxt;
    }
    if(target->nxt){
        target->nxt->pre = target->pre;
    }
    if(list->head == target){
        list->head = target->nxt;
    }
    if(list->tail == target){
        list->tail = target->pre;
    }  
    list->len--;
    int count = target->count;

    free(target);
    hash_table[num->value + MAX_VAL * flag] = NULL;
    return count;
}
void printlist(linked_list* list){
    if(list->len == 0){
        printf("-");
    }else{
        node* temp = list->head;
        printf("%d",temp->value);
        temp = temp->nxt;
        while(temp != NULL){
            printf(" %d",temp->value);
            temp = temp->nxt;
        }
    }
}