#include <stdio.h>
#include <stdlib.h>

// 链表节点
typedef struct Node {
    int value;
    int count;  // 记录在 history 中的出现次数
    struct Node* prev;
    struct Node* next;
} Node;

// 双向链表结构
typedef struct {
    Node* head;
    Node* tail;
    int size;
    int capacity;
} LinkedList;

// 初始化链表
LinkedList* init_list(int capacity) {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->capacity = capacity;
    return list;
}

// 创建新节点
Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->count = 1;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

// 在链表头部插入（最新元素在前）
void insert_front(LinkedList* list, Node* node) {
    node->next = list->head;
    node->prev = NULL;
    if (list->head) {
        list->head->prev = node;
    }
    list->head = node;
    if (list->size == 0) {
        list->tail = node;
    }
    list->size++;
}

// 删除链表尾部节点（用于 FIFO 或 LRU 淘汰）
void remove_tail(LinkedList* list) {
    if (list->size == 0) return;
    Node* to_delete = list->tail;
    if (list->size == 1) {
        list->head = list->tail = NULL;
    } else {
        list->tail = to_delete->prev;
        list->tail->next = NULL;
    }
    free(to_delete);
    list->size--;
}

// 查找节点
Node* find_node(LinkedList* list, int value) {
    Node* temp = list->head;
    while (temp) {
        if (temp->value == value) return temp;
        temp = temp->next;
    }
    return NULL;
}

// 删除特定节点（用于删除 history 或调整 cache 位置）
void remove_node(LinkedList* list, Node* node) {
    if (!node) return;
    if (node == list->head) {
        list->head = node->next;
        if (list->head) list->head->prev = NULL;
    } else if (node == list->tail) {
        list->tail = node->prev;
        if (list->tail) list->tail->next = NULL;
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    free(node);
    list->size--;
}

void print_list_reverse(Node* node) {
    if (!node) return;  // 递归终止条件
    print_list_reverse(node->next);
    if (node->next) {
        printf(" %d", node->value);
    } else {
        printf("%d", node->value);  // 第一个输出的元素不加空格
    }
}

void print_list(LinkedList* list) {
    if (!list->head) {
        printf("-");
    } else {
        print_list_reverse(list->head);
    }
}


// 处理历史记录
void process_history(LinkedList* history, LinkedList* cache, int k, int num) {
    Node* node = find_node(history, num);

    if (node) {
        node->count++;
        if (node->count >= k) {
            // 添加到 cache
            Node* cache_node = create_node(num);
            insert_front(cache, cache_node);
            // 如果 cache 超出容量，移除最老的
            if (cache->size > cache->capacity) {
                remove_tail(cache);
            }
            // 从 history 删除
            remove_node(history, node);
        }
    } else {
        if (history->size == history->capacity) {
            remove_tail(history);
        }
        Node* new_node = create_node(num);
        insert_front(history, new_node);
    }
}

// 处理缓存（LRU 机制）
void process_cache(LinkedList* cache, int num) {
    Node* node = find_node(cache, num);
    if (node) {
        remove_node(cache, node);  // 删除原位置
        insert_front(cache, create_node(num));  // 插入到头部
    } else {
        insert_front(cache, create_node(num));
        if (cache->size > cache->capacity) {
            remove_tail(cache);
        }
    }
}

int main() {
    int k, n, m;
    scanf("%d %d %d", &k, &n, &m);

    LinkedList* history = init_list(n);
    LinkedList* cache = init_list(n);

    // 初始化历史队列
    int temp;
    for (int i = 0; i < n; i++) {
        scanf("%d", &temp);
        process_history(history, cache, k, temp);
    }

    // 处理输入数据
    for (int i = n; i < m; i++) {
        scanf("%d", &temp);
        if (find_node(cache, temp)) {
            process_cache(cache, temp);  // 如果在 cache 中，调整 LRU 位置
        } else {
            process_history(history, cache, k, temp);
        }
    }

    // 输出结果
    print_list(history);
    printf("\n");
    print_list(cache);

    return 0;
}
